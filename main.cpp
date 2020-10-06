#include <iostream>

#include "./src/allocator.h"

using namespace std;

int main() {
//    std::cout << "Hello, World!" << std::endl;

    int *a = new int();
    MiniSTL::construct(a, 1);
    MiniSTL::destroy(a);
}
