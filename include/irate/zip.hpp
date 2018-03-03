#ifndef ZIP_HPP_
#define ZIP_HPP_

#include <iterator>
#include <tuple>

namespace irate
{

template <std::size_t begin, std::size_t end, typename Iterators>
void increment(Iterators& iterators)
{
    if constexpr (begin < end)
    {
        ++std::get<begin>(iterators);
        increment<begin + 1, end>(iterators);
    }
}

template <typename Iterators, std::size_t... Indices>
auto dereference(const Iterators& iterators,
                 const std::index_sequence<Indices...>)
{
    return std::tie(*std::get<Indices>(iterators)...);
}

template <std::size_t begin, std::size_t end, typename Iterators>
bool all_not_equal(const Iterators& lhs, const Iterators& rhs)
{
    if constexpr (begin < end)
    {
        return std::get<begin>(lhs) != std::get<begin>(rhs)
            ? all_not_equal<begin + 1, end>(lhs, rhs)
            : false;
    }
    return true;
}

template <typename... Containers>
struct zip_iterator
{
    static constexpr std::size_t size = sizeof...(Containers);

    using iterator_type = std::tuple<typename Containers::const_iterator...>;

    using zip_type = std::tuple<typename Containers::value_type...>;

    explicit zip_iterator(
        const typename Containers::const_iterator... iterators)
        : iterators_(iterators...)
    {}

    zip_type operator*() const
    {
        return dereference(iterators_, std::make_index_sequence<size>{});
    }

    void operator++()
    {
        increment<0, size>(iterators_);
    }

    bool operator!=(const zip_iterator& rhs) const
    {
        return all_not_equal<0, size>(iterators_, rhs.iterators_);
    }

private:
    iterator_type iterators_;
};

template <typename... Containers>
struct zip
{
    using iterator_type = zip_iterator<Containers...>;

    zip(const Containers&... containers)
        : begin_(std::begin(containers)...), end_(std::end(containers)...)
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

#endif /* ZIP_HPP_ */
