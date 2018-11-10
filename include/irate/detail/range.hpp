#ifndef IRATE_DETAIL_RANGE_HPP_
#define IRATE_DETAIL_RANGE_HPP_

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

} // namespace irate

#endif /* IRATE_DETAIL_RANGE_HPP_ */
