#ifndef IRATE_ENUMERATE_HPP_
#define IRATE_ENUMERATE_HPP_

#include <iterator>
#include <tuple>
#include <type_traits>

namespace irate
{

namespace detail
{

template <typename ContainerIterator, typename Index>
struct enumerate_iterator
{
    constexpr enumerate_iterator(const ContainerIterator iterator,
                                 const Index index)
        : iterator_(iterator), index_(index){};

    constexpr auto operator*()
    {
        return std::tie(index_, *iterator_);
    }

    constexpr void operator++()
    {
        std::advance(iterator_, 1);
        ++index_;
    }

    constexpr bool operator!=(const ContainerIterator& rhs) const
    {
        return iterator_ != rhs;
    }

private:
    ContainerIterator iterator_;
    Index index_;
};

} // namespace detail

template <typename Container, typename Index = int>
struct enumerate
{
    using container_iterator =
        std::conditional_t<std::is_const_v<Container>,
                           typename Container::const_iterator,
                           typename Container::iterator>;

    using enumerate_iterator =
        detail::enumerate_iterator<container_iterator, Index>;

    constexpr explicit enumerate(Container& container, const Index start = 0)
        : begin_(std::begin(container), start), end_(std::end(container))
    {}

    constexpr enumerate_iterator begin() const
    {
        return begin_;
    }

    constexpr container_iterator end() const
    {
        return end_;
    }

private:
    enumerate_iterator begin_;
    container_iterator end_;
};

} // namespace irate

#endif /* IRATE_ENUMERATE_HPP_ */
