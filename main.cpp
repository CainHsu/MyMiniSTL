#include <iostream>

#include "./src/allocator.h"

using namespace std;

int main() {
//    std::cout << "Hello, World!" << std::endl;

    int* ptr = MiniSTL::allocator<int>::allocate(1);

    cout << sizeof(ptr) << endl;

    cout << ptr;

    MiniSTL::allocator<int>::deallocate(ptr, 2);

    return 0;
}
