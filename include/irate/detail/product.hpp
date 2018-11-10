#ifndef IRATE_DETAIL_PRODUCT_HPP_
#define IRATE_DETAIL_PRODUCT_HPP_

#include <iterator>
#include <tuple>
#include <type_traits>
#include <utility>

namespace irate
{

namespace detail
{

template <typename HeadIterator, typename... Containers>
struct product_iterator
{
    constexpr explicit product_iterator(Containers&... containers)
        : iterators_(std::begin(containers)...),
          iterators_begin_(iterators_),
          iterators_end_(std::end(containers)...)
    {}

    constexpr auto operator*() const
    {
        return dereference(iterators_, indices{});
    }

    constexpr void operator++()
    {
        constexpr std::size_t tail_index = sizeof...(Containers) - 1;

        increment<tail_index>();
    }

    constexpr bool operator!=(const HeadIterator& rhs) const
    {
        return std::get<0>(iterators_) != rhs;
    }

private:
    using indices = std::index_sequence_for<Containers...>;

    using iterators_type = std::tuple<
        typename std::conditional_t<std::is_const_v<Containers>,
                                    typename Containers::const_iterator,
                                    typename Containers::iterator>...>;

    iterators_type iterators_;
    iterators_type iterators_begin_;
    iterators_type iterators_end_;

    template <std::size_t Index>
    constexpr void increment()
    {
        ++std::get<Index>(iterators_);

        if (std::get<Index>(iterators_) != std::get<Index>(iterators_end_))
        {
            return;
        }

        if constexpr (Index > 0)
        {
            std::get<Index>(iterators_) = std::get<Index>(iterators_begin_);
            increment<Index - 1>();
        }
    }
};

} // namespace detail

} // namespace irate

#endif /* IRATE_DETAIL_PRODUCT_HPP_ */
