#ifndef IRATE_ENUMERATE_HPP_
#define IRATE_ENUMERATE_HPP_

#include <iterator>
#include <type_traits>
#include <utility>

namespace irate
{

template <typename Container, typename IndexType>
struct enumerate_iterator
{
    static constexpr bool is_const = std::is_const_v<Container>;

    using iterator_type =
        typename std::conditional_t<is_const,
                                    typename Container::const_iterator,
                                    typename Container::iterator>;

    using value_type = typename std::iterator_traits<iterator_type>::value_type;
    using index_type = IndexType;

    using enumeration_value_type =
        std::conditional_t<is_const, const value_type&, value_type&>;

    using enumeration_type =
        std::pair<const index_type, enumeration_value_type>;

    explicit enumerate_iterator(const iterator_type iterator)
        : iterator_(iterator){};

    enumeration_type operator*()
    {
        return {index_, *iterator_};
    }

    void operator++()
    {
        std::advance(iterator_, 1);
        ++index_;
    }

    bool operator!=(const enumerate_iterator& rhs)
    {
        return iterator_ != rhs.iterator_;
    }

private:
    iterator_type iterator_{};
    index_type index_{};
};

template <typename Container, typename IndexType = int>
struct enumerate
{
    using iterator_type = enumerate_iterator<Container, IndexType>;

    explicit enumerate(Container& container)
        : begin_(std::begin(container)), end_(std::end(container))
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
