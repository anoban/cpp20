#include <concepts>
#include <cstdio>

template<typename T> requires std::integral<T> || std::floating_point<T> [[nodiscard]] T constexpr max(const T val_0, const T val_1) {
    return val_0 >= val_1 ? val_0 : val_1;
}

int main(void) {
    uint64_t    one { 1 }, ten { 10 };
    double      pi { 3.144 }, smth { 0.6745 };
    const long* longptr { nullptr };
    auto        ptrone { &one };
    auto        ptrten { &ten };

    ::max(ten, one);
    ::max(pi, smth);
    ::max(
        smth, longptr
    ); // doesn't satisfy our concepts, inputs need to be of the same type and cannot be anything other than integers or floats

    ::max(ptrone, ptrten); // identical types but still errs as the types are not acceptable according to our concepts

    return 0;
}