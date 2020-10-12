//
// Created by 徐琛 on 2020/10/6.
//

#ifndef MYMINISTL_ITERATOR_H
#define MYMINISTL_ITERATOR_H

#include <cstddef>

#include "type_traits.h"

namespace MiniSTL{

    // 五种作为标记的型别，对应五种迭代操作
    struct input_iterator_tag{}; // 单向只读
    struct output_iterator_tag{}; // 单向只写
    struct forward_iterator_tag : public input_iterator_tag{}; // 单向读写
    struct bidirectional_iterator_tag : public forward_iterator_tag{}; // 双向读写
    struct random_access_iterator_tag : public bidirectional_iterator_tag{}; // 下标读写

    // 避免挂一漏万
    template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
    struct iterator{
        typedef Category   iterator_category;
        typedef T          value_type;
        typedef Distance   difference_type;
        typedef Pointer    pointer;
        typedef Reference  reference;
    };

    // 用于判断输入类型中是否有iterator_category的声明
    template<class T>
    struct has_iterator_cat{
    private:
        struct two {
            char a;
            char b;
        };
        template<class U> static two test(...);
        template<class U> static char test(typename U::iterator_catrgory* = 0);
    public:
        // 若有iterator_category，则test<T>(0)返回char，否则为tow
        static const bool value = sizeof(test<T>(0)) == sizeof(char);
    };

    template<class Iterator, bool>
    struct iterator_traits_impl{};

    template<class Iterator>
    struct iterator_traits_impl<Iterator, true>{
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type        value_type;
        typedef typename Iterator::pointer           pointer;
        typedef typename Iterator::reference         reference;
        typedef typename Iterator::difference_type   difference_type;
    };

    template<class Iterator, bool>
    struct iterator_traits_helper{};

    template<class Iterator> // is_convertible 判断第一个参数是否可以转化为第二个参数的类型，如子类转化为基类
    struct iterator_traits_helper<Iterator, true> : public iterator_traits_impl<Iterator,
            std::is_convertible<typename Iterator::iterator_category, input_iterator_tag>::value ||
            std::is_convertible<typename Iterator::iterator_category, output_iterator_tag>::value>{};

    template<class Iterator>
    struct iterator_traits :
            public iterator_traits_helper<Iterator, has_iterator_cat<Iterator>::value>{};

    template<class T>
    struct iterator_traits<T*>{
        typedef random_access_iterator_tag           iterator_category;
        typedef T                                    value_type;
        typedef T*                                   pointer;
        typedef T&                                   reference;
        typedef ptrdiff_t                            difference_type;
    };

    template<class T>
    struct iterator_traits<const T*>{
        typedef random_access_iterator_tag           iterator_category;
        typedef T                                    value_type;
        typedef const T*                             pointer;
        typedef const T&                             reference;
        typedef ptrdiff_t                            difference_type;
    };

    template<class T, class U, bool = has_iterator_cat<iterator_traits<T>>::value>
    struct has_iterator_cat_of :
            public m_bool_constant<std::is_convertible<
            typename iterator_traits<T>::iterator_category, U>::value>{};

    template<class T, class U>
    struct has_iterator_cat_of<T, U, false> : public m_false_type {};

    template<class Iter>
    struct is_input_iterator : public has_iterator_cat_of<Iter, input_iterator_tag>{};
    template<class Iter>
    struct is_output_iterator : public has_iterator_cat_of<Iter, output_iterator_tag>{};
    template<class Iter>
    struct is_forward_iterator : public has_iterator_cat_of<Iter, forward_iterator_tag>{};
    template<class Iter>
    struct is_bidirectional_iterator : public has_iterator_cat_of<Iter, bidirectional_iterator_tag>{};
    template<class Iter>
    struct is_random_access_iterator : public has_iterator_cat_of<Iter, random_access_iterator_tag>{};

    template<class Iterator>
    struct is_iterator : public m_bool_constant<is_input_iterator<Iterator>::value ||
            is_output_iterator<Iterator>::value>{};

    template<class Iterator>
    typename iterator_traits<Iterator>::iterator_category
    iterator_category(const Iterator&){
        typedef typename iterator_traits<Iterator>::iterator_category Category;
        return Category();
    }

    template<class Iterator>
    typename iterator_traits<Iterator>::difference_type*
    distance_type(const Iterator&){
        return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
    }

    template<class Iterator>
    typename iterator_traits<Iterator>::value_type*
    value_type(const Iterator&){
        return static_cast<typename iterator_traits<Iterator>::value_type>(0);
    }

    // 计算迭代器间的距离

    template<class InputIterator>
    typename iterator_traits<InputIterator>::difference_type
    distance_diapatch(InputIterator first, InputIterator last, input_iterator_tag){
        typename iterator_traits<InputIterator>::difference_type n = 0;
        while(first != last){
            ++first;
            ++n;
        }
        return n;
    }










}

#endif //MYMINISTL_ITERATOR_H
