#pragma once

#include <ien/type_traits.hpp>

namespace ien
{
    template<typename T, typename = ien::tt::enable_if_is_integral_or_float<T>>
    struct rect
    {
        T x = static_cast<T>(0);
        T y = static_cast<T>(0);
        T w = static_cast<T>(0);
        T h = static_cast<T>(0);

        constexpr rect() { }
        
        constexpr rect(T vx, T vy, T vw, T vh) 
            : x(vx)
            , y(vy)
            , w(vw)
            , h(vh)
        { }

        constexpr T area()
        {
            return w * h;
        }
    };
}