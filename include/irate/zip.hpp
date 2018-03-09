#ifndef IRATE_ZIP_HPP_
#define IRATE_ZIP_HPP_

#include <iterator>
#include <tuple>

namespace irate
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
        typename std::conditional_t<std::is_const<Containers>::value,
                                    typename Containers::const_iterator,
                                    typename Containers::iterator>...>;

    template <typename... Iterators>
    explicit zip_iterator(const Iterators... iterators)
        : iterators_(iterators...)
    {}

    auto operator*() const
    {
        return dereference(iterators_, indices{});
    }

    void operator++()
    {
        increment(iterators_, indices{});
    }

    bool operator!=(const zip_iterator& rhs) const
    {
        return all_not_equal(iterators_, rhs.iterators_, indices{});
    }

private:
    iterators_type iterators_;
};

template <typename... Containers>
struct zip
{
    using iterator_type = zip_iterator<Containers...>;

    explicit zip(Containers&... containers)
        : begin_(std::begin(containers)...), end_(std::end(containers)...)
    {}

    iterator_type begin() const
    {
        return begin_;
    }

    iterator_type end() const
    {
        return end_;
    }

private:
    iterator_type begin_;
    iterator_type end_;
};

} // namespace irate

#endif /* IRATE_ZIP_HPP_ */
