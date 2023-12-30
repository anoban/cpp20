#include <concepts>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

namespace cuda {
    template<typename T> requires std::integral<T> || std::floating_point<T>
    __global__ void sum(_In_ const std::vector<T>& vector, _Inout_ T& sum) {
        sum = std::accumulate<T>(vector.cbegin(), vector.cend(), static_cast<T>(0), std::plus);
        return;
    }
} // namespace cuda

static constexpr std::size_t NUMELEMS { 100'000 };

int                          main(void) {
    auto rgenerator { std::random_device {} }; // non-deterministic random number generator
    auto mersenne { std::mt19937_64 { rgenerator() } }; // seeding the mersenne twister, use a seed for deterministic behaviour
    std::vector<int64_t> randoms(NUMELEMS * sizeof(int64_t));
    std::transform(randoms.begin(), randoms.end(), randoms.begin(), mersenne);
}