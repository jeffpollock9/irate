#ifndef IRATE_DETAIL_DEREFERENCE_HPP_
#define IRATE_DETAIL_DEREFERENCE_HPP_

#include <tuple>
#include <utility>

namespace irate
{

namespace detail
{

template <typename Iterators, std::size_t... Indices>
auto dereference(const Iterators& iterators,
                 const std::index_sequence<Indices...>)
{
    return std::tie(*std::get<Indices>(iterators)...);
}

} // namespace detail

} // namespace irate

#endif /* IRATE_DETAIL_DEREFERENCE_HPP_ */
