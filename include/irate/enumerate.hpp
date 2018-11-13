#ifndef IRATE_ENUMERATE_HPP_
#define IRATE_ENUMERATE_HPP_

#include <irate/detail/enumerate.hpp>

#include <iterator>
#include <type_traits>

namespace irate
{

template <typename Container,
          typename Index = typename Container::difference_type>
struct enumerate
{
    constexpr explicit enumerate(Container& container, const Index start = 0)
        : begin_(std::begin(container), start), end_(std::end(container))
    {}

    constexpr auto begin() const
    {
        return begin_;
    }

    constexpr auto end() const
    {
        return end_;
    }

private:
    using container_iterator =
        std::conditional_t<std::is_const_v<Container>,
                           typename Container::const_iterator,
                           typename Container::iterator>;

    using enumerate_iterator =
        detail::enumerate_iterator<std::is_const_v<Container>,
                                   container_iterator,
                                   Index>;

    enumerate_iterator begin_;
    container_iterator end_;
};

} // namespace irate

#endif /* IRATE_ENUMERATE_HPP_ */
