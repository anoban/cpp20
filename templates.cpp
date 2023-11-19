#include <concepts>
#include <cstdio>

template<typename T> requires std::is_floating_point<T>::value constexpr size_t func(_In_ const T& value) noexcept {
    const auto err { first_phase_lookup_error() };       // err if first_phase_lookup_error is undeclared
    const auto err_ { instantiation_time_error(value) }; // err if instantiation_time_error(const T& value) is undeclared

    static_assert(sizeof(size_t) < 4, "First phase lookup error");
    static_assert(sizeof(T) < 6, "Second phase lookup error");
    return 100 + value;
}

int main(void) {
    const auto inp { 897.34647L };
    auto       result { func(inp) };
    return 0;
}