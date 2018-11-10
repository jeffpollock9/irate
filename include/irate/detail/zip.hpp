#ifndef IRATE_DETAIL_ZIP_
#define IRATE_DETAIL_ZIP_

#include <tuple>
#include <type_traits>
#include <utility>

namespace irate
{

namespace detail
{

template <typename... Containers>
struct zip_iterator
{
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
        increment(indices{});
    }

    constexpr bool operator!=(const zip_iterator& rhs) const
    {
        return all_not_equal(rhs.iterators_, indices{});
    }

private:
    using indices = std::index_sequence_for<Containers...>;

    using iterators_type = std::tuple<
        typename std::conditional_t<std::is_const_v<Containers>,
                                    typename Containers::const_iterator,
                                    typename Containers::iterator>...>;

    iterators_type iterators_;

    template <std::size_t... Indices>
    constexpr bool all_not_equal(const iterators_type& rhs,
                                 const std::index_sequence<Indices...>) const
    {
        return ((std::get<Indices>(iterators_) != std::get<Indices>(rhs)) &&
                ...);
    }

    template <std::size_t... Indices>
    constexpr void increment(const std::index_sequence<Indices...>)
    {
        (++std::get<Indices>(iterators_), ...);
    }
};

} // namespace detail

} // namespace irate

#endif /* IRATE_DETAIL_ZIP_ */
