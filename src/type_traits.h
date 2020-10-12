//
// Created by 徐琛 on 2020/10/12.
//

#ifndef MYMINISTL_TYPE_TRAITS_H
#define MYMINISTL_TYPE_TRAITS_H

namespace MiniSTL{

    template<class T, T v>
    struct m_integral_constant{
        static constexpr T value = v;
    };

    template<bool b>
    using m_bool_constant = m_integral_constant<bool, b>;

    typedef m_bool_constant<true> m_true_type;
    typedef m_bool_constant<false> m_false_type;

}

#endif //MYMINISTL_TYPE_TRAITS_H
