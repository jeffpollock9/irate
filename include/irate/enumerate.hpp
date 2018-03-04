#ifndef IRATE_ENUMERATE_HPP_
#define IRATE_ENUMERATE_HPP_

#include <iterator>
#include <type_traits>
#include <utility>

namespace irate
{

template <typename Container, typename Index>
struct enumerate_iterator
{
    using iterator_type = typename Container::const_iterator;

    using value_type = typename std::iterator_traits<iterator_type>::value_type;
    using index_type = Index;

    enumerate_iterator(const iterator_type iterator, const index_type index)
        : iterator_(iterator), index_(index){};

    std::pair<const index_type, const value_type&> operator*() const
    {
        return {index_, *iterator_};
    }

    void operator++()
    {
        std::advance(iterator_, 1);
        ++index_;
    }

    bool operator!=(const enumerate_iterator& rhs) const
    {
        return iterator_ != rhs.iterator_;
    }

private:
    iterator_type iterator_;
    index_type index_;
};

template <typename Container, typename Index = int>
struct enumerate
{
    using iterator_type = enumerate_iterator<Container, Index>;

    explicit enumerate(Container& container, const Index start = 0)
        : begin_(std::begin(container), start), end_(std::end(container), -1)
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

#endif /* IRATE_ENUMERATE_HPP_ */
