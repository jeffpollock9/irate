#ifndef IRATE_RANGE_HPP_
#define IRATE_RANGE_HPP_

#include <irate/detail/range.hpp>

namespace irate
{

template <typename Integer = int>
struct range
{
    constexpr explicit range(const Integer end) : begin_(0, 1), end_(end)
    {}

    constexpr range(const Integer begin,
                    const Integer end,
                    const Integer step = 1)
        : begin_(begin, step), end_(end)
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
    using range_iterator = detail::range_iterator<Integer>;

    range_iterator begin_;
    Integer end_;
};

} // namespace irate

#endif /* IRATE_RANGE_HPP_ */
