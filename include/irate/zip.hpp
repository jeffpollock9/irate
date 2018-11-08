#ifndef IRATE_ZIP_HPP_
#define IRATE_ZIP_HPP_

#include <iterator>
#include <tuple>

namespace irate
{

namespace detail
{

template <typename Iterators, std::size_t... Indices>
void increment(Iterators& iterators, const std::index_sequence<Indices...>)
{
    (++std::get<Indices>(iterators), ...);
}

template <typename Iterators, std::size_t... Indices>
auto dereference(const Iterators& iterators,
                 const std::index_sequence<Indices...>)
{
    return std::tie(*std::get<Indices>(iterators)...);
}

template <typename Iterators, std::size_t... Indices>
bool all_not_equal(const Iterators& lhs,
                   const Iterators& rhs,
                   const std::index_sequence<Indices...>)
{
    return ((std::get<Indices>(lhs) != std::get<Indices>(rhs)) && ...);
}

template <typename... Containers>
struct zip_iterator
{
    using indices = std::index_sequence_for<Containers...>;

    using iterators_type = std::tuple<
        typename std::conditional_t<std::is_const_v<Containers>,
                                    typename Containers::const_iterator,
                                    typename Containers::iterator>...>;

    template <typename... Iterators>
    constexpr explicit zip_iterator(const Iterators... iterators)
        : iterators_(iterators...)
    {}

    constexpr auto operator*() const
    {
        return dereference(iterators_, indices{});
    }

    constexpr void operator++()
    {
        increment(iterators_, indices{});
    }

    constexpr bool operator!=(const zip_iterator& rhs) const
    {
        return all_not_equal(iterators_, rhs.iterators_, indices{});
    }

private:
    iterators_type iterators_;
};

} // namespace detail

template <typename... Containers>
struct zip
{
    using zip_iterator = detail::zip_iterator<Containers...>;

    constexpr explicit zip(Containers&... containers)
        : begin_(std::begin(containers)...), end_(std::end(containers)...)
    {}

    constexpr zip_iterator begin() const
    {
        return begin_;
    }

    constexpr zip_iterator end() const
    {
        return end_;
    }

private:
    zip_iterator begin_;
    zip_iterator end_;
};

} // namespace irate

#endif /* IRATE_ZIP_HPP_ */
