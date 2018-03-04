#ifndef IRATE_RANGE_HPP_
#define IRATE_RANGE_HPP_

namespace irate
{

template <typename Integer>
struct range_iterator
{
    range_iterator(const Integer value, const Integer step)
        : value_(value), step_(step)
    {}

    Integer operator*() const
    {
        return value_;
    }

    void operator++()
    {
        value_ += step_;
    }

    bool operator!=(const range_iterator& rhs) const
    {
        return value_ < rhs.value_;
    }

private:
    Integer value_;
    Integer step_;
};

template <typename Integer = int>
struct range
{
    using iterator_type = range_iterator<Integer>;

    explicit range(const Integer end) : begin_(0, 1), end_(end, 1)
    {}

    range(const Integer begin, const Integer end, const Integer step = 1)
        : begin_(begin, step), end_(end, step)
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

#endif /* IRATE_RANGE_HPP_ */
