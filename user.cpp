#include <cmath>
#include <concepts>
#include <ctime>
#include <iostream>
#include <vector>

namespace statistics {

    template<typename T> struct container {
            long double mean {}, std {};

            container(_In_ const std::vector<T>& vector, _In_ const bool is_sample = false) noexcept {
                static_assert(std::is_arithmetic<T>::value);
                for (auto it = vector.begin(); it != vector.cend(); ++it) mean += *it;
                mean /= vector.size();

                for (auto it = vector.begin(); it != vector.cend(); ++it) std += powl(*it - mean, 2.0L);
                std = is_sample ? sqrtl(std / vector.size()) : sqrtl(std / vector.size() - 1);
            }

            ~container() = default;

            std::pair<long double, long double> yield(void) const noexcept { return std::pair<long double, long double> { mean, std }; }
    };

} // namespace statistics

int main(void) {
    srand(time(nullptr));
    std::vector<std::size_t> numbers {};
    for (size_t i = 0; i < 10'000; ++i) numbers.push_back(rand());

    const auto stats { statistics::container(numbers) };
    const auto result { stats.yield() };

    std::wcout << L"Mean: " << result.first << L" Standard deviation: " << result.second << std::endl;
    return EXIT_SUCCESS;
}