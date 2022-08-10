#include <complex>
#include <tuple>

namespace std {

template <typename T>
class tuple_size<complex<T>> {
   public:
    static constexpr size_t value = 2;
};

template <size_t I, typename T>
auto get(const complex<T>& c) {
    if constexpr (I == 0) return c.real();
    else return c.imag();
}

template <size_t I, typename T>
class tuple_element<I, complex<T>> {
   public:
    using type = decltype(get<I>(declval<complex<T>>()));
};

}  // namespace std
