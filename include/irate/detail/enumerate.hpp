#ifndef IRATE_DETAIL_ENUMERATE_HPP_
#define IRATE_DETAIL_ENUMERATE_HPP_

#include <iterator>
#include <tuple>
#include <type_traits>

namespace irate
{

namespace detail
{

template <bool is_const, typename Iterator, typename Index>
struct enumerate_iterator
{
    using iterator_value_type =
        typename std::iterator_traits<Iterator>::value_type;

    using value_type = std::conditional_t<is_const,
                                          const iterator_value_type&,
                                          iterator_value_type&>;

    constexpr enumerate_iterator(const Iterator iterator, const Index index)
        : iterator_(iterator), index_(index){};

    constexpr std::pair<Index, value_type> operator*() const
    {
        return {index_, *iterator_};
    }

    constexpr void operator++()
    {
        ++iterator_;
        ++index_;
    }

    constexpr bool operator!=(const Iterator rhs) const
    {
        return iterator_ != rhs;
    }

private:
    Iterator iterator_;
    Index index_;
};

} // namespace detail

} // namespace irate

#endif /* IRATE_DETAIL_ENUMERATE_HPP_ */
