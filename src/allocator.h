//
// Created by 徐琛 on 2020/10/5.
//

#ifndef MYMINISTL_ALLOCATOR_H
#define MYMINISTL_ALLOCATOR_H

#include <cstddef>

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
        static T* allocate();
        static T* allocate(size_type n);
        static void deallocate(pointer p);
        static void deallocate(pointer p, size_type n);
    };

    template<class T>
    T* allocator<T>::allocate() {
        return static_cast<T*>(::operator new(sizeof(T)));
    }

    template<class T>
    T *allocator<T>::allocate(allocator::size_type n) {
        if(n == 0) return nullptr;
        return static_cast<allocator::pointer>(::operator new(n*sizeof(T)));
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
