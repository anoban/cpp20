#include <concepts>
#include <cstdio>

#ifdef __ALLOWMACROS
    #define sq(n) ((n) * (n))
#endif

double                                                           sq(double n) { return n * n; }

template<typename T> requires std::floating_point<T> constexpr T sq(const T n) {
    ::_putws(L"template<typename T> requires std::floating_point<T> constexpr T sq(const T n)");
    return n * n;
}

int main(void) {
    auto       value { sq(12.7856872f) };
    const auto square { sq(54.356456454) };
    return 0;
}
