#ifndef ZIP_HPP_
#define ZIP_HPP_

namespace irate
{

struct zip
{
    template <typename... Containers>
    zip(Containers... containers)
    {
        static_assert(false, "write me!");
    }
};

} // namespace irate

#endif /* ZIP_HPP_ */
