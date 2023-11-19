#include <concepts>
#include <cstdint>

template<typename T> requires std::integral<T> || std::floating_point<T>
[[nodiscard]] static inline T constexpr sum(_In_ const T val_0, _In_ const T val_1) noexcept {
    return val_0 + val_1;
}

template<> [[nodiscard]] double sum<double>(_In_ const double val_0, _In_ const double val_1) noexcept { return val_0 + val_1; }

int                             main(void) {
    auto s { sum(0.54654, 6.645454) };
    return 0;
}