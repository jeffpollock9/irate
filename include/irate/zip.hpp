#ifndef IRATE_ZIP_HPP_
#define IRATE_ZIP_HPP_

#include <irate/detail/dereference.hpp>
#include <irate/detail/zip.hpp>

#include <iterator>

namespace irate
{

template <typename... Containers>
struct zip
{
    constexpr explicit zip(Containers&... containers)
        : begin_(std::begin(containers)...), end_(std::end(containers)...)
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
    using zip_iterator = detail::zip_iterator<Containers...>;

    zip_iterator begin_;
    zip_iterator end_;
};

} // namespace irate

#endif /* IRATE_ZIP_HPP_ */
