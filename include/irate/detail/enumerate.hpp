#ifndef IRATE_DETAIL_ENUMERATE_HPP_
#define IRATE_DETAIL_ENUMERATE_HPP_

#include <tuple>

namespace irate
{

namespace detail
{

template <typename Iterator, typename Index>
struct enumerate_iterator
{
    constexpr enumerate_iterator(const Iterator iterator, const Index index)
        : iterator_(iterator), index_(index){};

    constexpr auto operator*()
    {
        return std::tie(index_, *iterator_);
    }

    constexpr void operator++()
    {
        ++iterator_;
        ++index_;
    }

    constexpr bool operator!=(const Iterator& rhs) const
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
