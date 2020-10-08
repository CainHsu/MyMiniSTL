//
// Created by 徐琛 on 2020/10/7.
//

#ifndef MYMINISTL_UTIL_H
#define MYMINISTL_UTIL_H

#include <cstddef>
#include <iostream>

namespace MiniSTL{
    // move
    // 先使用remove_reference去掉参数的引用性再使用static_cast强制类型转换
    template<class T>
    typename std::remove_reference<T>::type&& move(T&& arg) noexcept{
        // 由于remove_reference在std中有重载的左值与右值版本，因此此处包含完美转发
        return static_cast<typename std::remove_reference<T>::type&&>(std::forward<T>(arg));
    }

    // forward
    // 根据完美转发的使用场景：在模板函数中使用右值引用参数调用其他函数时会被转换为左值。
    // 因此左值参数函数的重载则将此值转换为右值，右值参数函数的重载保持不变
    template<class T>
    T&& forward(typename std::remove_reference<T>::type& arg) noexcept{
        return static_cast<T&&>(arg);
    }

    template<class T>
    T&& forward(typename std::remove_reference<T>::type&& arg) noexcept{
        // 当传入参数为左值引用时报错，因此调用时T不能为左值引用
        static_assert(!std::is_lvalue_reference<T>::value, "bad forward");
        return static_cast<T&&>(arg);
    }

}

#endif //MYMINISTL_UTIL_H
