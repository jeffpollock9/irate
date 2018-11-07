#ifndef IRATE_RANGE_HPP_
#define IRATE_RANGE_HPP_

namespace irate
{

namespace detail
{

template <typename Integer>
struct range_iterator
{
    constexpr explicit range_iterator(const Integer value, const Integer step)
        : value_(value), step_(step)
    {}

    constexpr Integer operator*() const
    {
        return value_;
    }

    constexpr void operator++()
    {
        value_ += step_;
    }

    constexpr bool operator!=(const Integer rhs) const
    {
        return value_ < rhs;
    }

private:
    Integer value_;
    Integer step_;
};

} // namespace detail

template <typename Integer = int>
struct range
{
    using range_iterator = detail::range_iterator<Integer>;

    constexpr explicit range(const Integer end) : begin_(0, 1), end_(end)
    {}

    constexpr range(const Integer begin,
                    const Integer end,
                    const Integer step = 1)
        : begin_(begin, step), end_(end)
    {}

    constexpr range_iterator begin() const
    {
        return begin_;
    }

    constexpr Integer end() const
    {
        return end_;
    }

private:
    range_iterator begin_;
    Integer end_;
};

} // namespace irate

#endif /* IRATE_RANGE_HPP_ */
