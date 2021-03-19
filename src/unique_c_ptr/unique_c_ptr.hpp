#include <cstdlib>
#include <memory>
#include <type_traits>

// Tricky use of std::integral_constant
// It works because std::integral_constant defines a single, non-explicit
// cast operator to fn's type. When the destructor of std::unique_ptr calls
// get_deleter() and tries to invoke the result, an implicit conversion takes
// place and fn(ptr) is invoked.
// Credits:
// https://stackoverflow.com/questions/19053351/how-do-i-use-a-custom-deleter-with-a-stdunique-ptr-member/51274008#51274008
// https://stackoverflow.com/questions/46530173/template-parameter-that-can-accept-function-pointer-or-functor/46530492#46530492
template <auto fn>
using deleter = std::integral_constant<std::decay_t<decltype(fn)>, fn>;

template <typename T, auto fn = std::free>
using unique_c_ptr = std::unique_ptr<T, deleter<fn>>;

template <auto fn = std::free, typename T>
inline auto make_unique_c_ptr(T* t)
{
    return unique_c_ptr<T, fn>{t};
}

inline void custom_deleter(void* d)
{
    std::free(d);
}
