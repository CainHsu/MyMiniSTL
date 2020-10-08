//
// Created by 徐琛 on 2020/10/6.
//

#ifndef MYMINISTL_CONSTRUCT_H
#define MYMINISTL_CONSTRUCT_H

#include <new>

namespace MiniSTL{
    // 调用T()的构造函数完成构造操作，将生成的对象放置在p所指的内存中
    // 当p为null时无法使用 <------------------------------------------------------
    template<class T>
    inline void construct(T* p){
        ::new ((void*)p) T(); // placement new，用法：调用T的构造函数，将构造好的内容放进p所指的内存中
    }

    // 使用T1(value)构造函数，在T1所指内存构造出T1(value)对象
    template<class T1, class T2>
    inline void construct(T1 *p, const T2 &value){
        ::new ((void*)p) T1(value);
    }

    // 调用析构函数析构参数对象
    // 是基本数据结构时不进行任何操作，是自定义数据结构时调用自身的析构函数
    template<class T>
    inline void destroyOneObj(T*, std::true_type){}
    template<class T>
    inline void destroyOneObj(T* p, std::false_type){
        if(p) {
            p->~T();
        }
    }

    // 封装destroyOneObj，判断此数据是否为基本数据结构
    template<class T>
    inline void destroy(T* p){
        destroyOneObj(p, std::is_trivially_destructible<T>{});
    }

    // 接收迭代器的版本，调用destory判断此数据结构是否为基本数据结构
    template<class iter>
    inline void destroyObjs(iter begin, iter end, std::false_type){
        for (; begin < end; ++begin) {
            destory(&*begin);
        }
    }


    template<class iter>
    inline void destory(iter begin, iter end){
        destroyObjs(begin, end, std::is_trivially_destructible<
                typename iterator_traits<iter>::value_type>{});
    }
}

#endif //MYMINISTL_CONSTRUCT_H
