#include "complex.hpp"
#include <iostream>

int main() {
    auto [r, i] = std::complex<int>{1, 2} + 3;
    std::cout << "real: " << r << ", imag: " << i << "\n";
}
