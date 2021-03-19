#include <iostream>

#include "unique_c_ptr.hpp"

template <auto fn>
struct Deleter
{
    constexpr void operator()(void* arg) const {
        // One may still need this type of deleter when argument casting is required
        return fn(arg);
    }
};

template <typename T, auto fn = std::free>
using unique_c_ptr2 = std::unique_ptr<T, Deleter<fn>>;

template <auto fn = std::free, typename T>
inline auto make_unique_c_ptr2(T* t)
{
    return unique_c_ptr2<T, fn>{t};
}

int main()
{
    constexpr auto size = sizeof (std::unique_ptr<int>{(int*)malloc(1)});
    static_assert(sizeof(make_unique_c_ptr((int*)malloc(1))) == size);
    static_assert(sizeof(make_unique_c_ptr<custom_deleter>((int*)malloc(1))) == size);
    static_assert(sizeof(make_unique_c_ptr2((int*)malloc(1))) == size);
    static_assert(sizeof(make_unique_c_ptr2<custom_deleter>((int*)malloc(1))) == size);

    std::cout << "sizeof unique_ptr<int>: " << sizeof (std::unique_ptr<int>{(int*)malloc(1)}) << std::endl;
    std::cout << "sizeof unique_ptr<int, decltype(&std::free)>: " << sizeof (std::unique_ptr<int, decltype(&std::free)>{(int*)malloc(1), std::free}) << std::endl;
    std::cout << "sizeof unique_c_ptr<int, std::free>: " << sizeof(make_unique_c_ptr((int*)malloc(1))) << std::endl;
    std::cout << "sizeof unique_c_ptr<int, custom_deleter>: " << sizeof(make_unique_c_ptr<custom_deleter>((int*)malloc(1))) << std::endl;
    std::cout << "sizeof unique_c_ptr2<int, std::free>: " << sizeof(make_unique_c_ptr2((int*)malloc(1))) << std::endl;
    std::cout << "sizeof unique_c_ptr2<int, custom_deleter>: " << sizeof(make_unique_c_ptr2<custom_deleter>((int*)malloc(1))) << std::endl;
    return 0;
}
