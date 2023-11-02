#include <concepts>
#include <cstdint>
#include <cstdio>
#include <format>
#include <string>

namespace pair {

    template<typename T> requires std::integral<T> || std::floating_point<T> class pair {
        private:
            T first {};
            T second {};

        public:
            pair() = default;
            constexpr pair(_In_ const T a, _In_ const T b) noexcept : first { a }, second { b } { }
            constexpr pair(_In_ const T& a, _In_ const T& b) noexcept : first { a }, second { b } { }

            static std::wstring to_wstr(void) noexcept {
                return std::format(std::is_integral<T>::value ? L"({:010d}, {:010d})" : L"({:.10f}, {:.10f})", 0, 0);
            }
    };
} // namespace pair
