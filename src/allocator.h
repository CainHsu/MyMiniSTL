//
// Created by 徐琛 on 2020/10/5.
//

#ifndef MYMINISTL_ALLOCATOR_H
#define MYMINISTL_ALLOCATOR_H

// 主要负责开辟指定大小的内存，以及内存的释放

#include <cstddef>

#include "construct.h"

namespace MiniSTL{
    template <class T>
    class allocator{
    private:
    public:
        typedef T            value_type;
        typedef T*           pointer;
        typedef const T*     const_pointer;
        typedef T&           reference;
        typedef const T&     const_reference;
        typedef size_t       size_type;
        typedef ptrdiff_t    difference_type;
    public:
        // 封装new函数，使用operator new开辟类型T大小的内存
        static T* allocate();
        // 封装new函数，使用operator new开辟n个T类型大小的内存
        static T* allocate(size_type n);

        // 封装delete函数， 释放p指针所指的内存
        static void deallocate(pointer p);
        // 封装delete函数， 释放p指针所指的内存
        static void deallocate(pointer p, size_type n);

    };

    // ------------------------------------------------------------------------------------------

    template<class T>
    T* allocator<T>::allocate() {
        T* temp = static_cast<T*>(::operator new((size_t)sizeof(T)));
        if(!temp){ // 防御性编程，后期可以考虑修改为exception处理 <-----------------------------
            std::cerr << "Out of memory" << std::endl;
            exit(1);
        }
        return temp;
    }

    template<class T>
    T *allocator<T>::allocate(allocator::size_type n) {
        if(n == 0) return nullptr;
        T* temp = static_cast<T*>(::operator new((size_t)n * sizeof(T)));
        if(!temp){
            std::cerr << "Out of memory" << std::endl;
            exit(1);
        }
        return temp;
    }

    template<class T>
    void allocator<T>::deallocate(allocator::pointer p) {
        if (p == nullptr) return;
        ::operator delete(p);
    }

    template<class T>
    void allocator<T>::deallocate(allocator::pointer p, allocator::size_type) {
        if(p == nullptr) return;
        ::operator delete(p);
    }



}

#endif //MYMINISTL_ALLOCATOR_H
