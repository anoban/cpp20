#include <array>
#include <cstdio>
#include <string>
#include <vector>

struct record {
        std::array<uint32_t, 10> numbers {};
        std::size_t              rows {};
        wchar_t                  name[100] {};

        constexpr record() = default;
        constexpr record(const std::array<uint32_t, 10>& _numbers, const std::size_t _rows, const std::wstring& _name) :
            numbers { _numbers }, rows { _rows }, name { std::move(_name) } { }
};

int main(void) {
    constexpr wchar_t                  me[] { L"Anoban" };
    constexpr std::array<uint32_t, 10> tens { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
    constexpr record                   myrec { tens, 321, me };
}