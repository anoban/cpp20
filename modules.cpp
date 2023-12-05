#include <iostream>
#include <vector>

template<typename T> long double constexpr sum(const std::vector<T>& container) noexcept {
    long double tmp {};
    for (const auto& elem : container) tmp += elem;
    return tmp;
}

int main(void) {
    std::vector<float> numbers { 4.354, 6.54, 6.45, 3.754, 2.76, 24, 0.235, 46, 74.6742 };
    const auto         s { sum<float>(numbers) };
    std::cout << s << std::endl;
    return 0;
}