#include <iostream>

#include "./src/allocator.h"
#include "./src/util.h"
#include <vector>
#include <any>

using namespace std;

//template<class container, typename Index>
//auto test(container&& c, Index index) ->decltype(c[index]) {
//    return std::forward<container>(c)[index];
//}

decltype(auto) f2(){
    int y;
    return (y);
}

//template<class T>
//void f(typename std::remove_reference<T>::type& args) noexcept {
//    std::cout << is_same<int&, decltype(args)>::value << std::endl;
//}


#pragma warning(push)

template<typename T1, typename T2>
void print(T1 &a, T2 &b){
    // cout << "t";
    cout << a << "\t" << b << endl;
}

template<typename T1, typename... T2>
void test(T1 a, T2&&... args){
//    print(a, args...);
    initializer_list<any>{(print(a, args), 0)...};
}



int main() {
    // cout << std::is_convertible<double, char>::value;
    vector<bool> a{true};
    auto temp = a[0];
    cout << sizeof(temp) << endl;
    cout << a[0] << endl;
}
