#ifndef IRATE_PRODUCT_HPP_
#define IRATE_PRODUCT_HPP_

#include <irate/detail/product.hpp>

#include <iterator>
#include <type_traits>

namespace irate
{

template <typename HeadContainer, typename... RestContainers>
struct product
{
    constexpr explicit product(HeadContainer& head_container,
                               RestContainers&... rest_containers)
        : begin_(head_container, rest_containers...),
          end_(std::end(head_container))
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
    using head_iterator =
        std::conditional_t<std::is_const_v<HeadContainer>,
                           typename HeadContainer::const_iterator,
                           typename HeadContainer::iterator>;

    using product_iterator = detail::
        product_iterator<head_iterator, HeadContainer, RestContainers...>;

    product_iterator begin_;
    head_iterator end_;
};

} // namespace irate

#endif /* IRATE_PRODUCT_HPP_ */
