#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <ranges>

#include <thrust/device_vector.h>
#include <thrust/functional.h>
#include <thrust/host_vector.h>

int main(void) {
    srand(time(nullptr));

    [[maybe_unused]] int32_t dummy {};

    auto                     host_vec { thrust::host_vector<int32_t> {} };
    host_vec.reserve(10'000 * sizeof(int32_t));
    for (const int32_t& _ : std::ranges::views::iota(0, 9'000)) host_vec.push_back(rand());

    thrust::device_vector<decltype(dummy)> dev_vec { host_vec };
    auto                                   dev_sum { thrust::reduce(dev_vec.cbegin(), dev_vec.cend(), 0, thrust::plus<int32_t> {}) };
    auto                                   host_sum { thrust::reduce(host_vec.cbegin(), host_vec.cend()) };
    ::wprintf_s(L"Sum of host vector is %10d and Sum of device vector is %10d\n", host_sum, dev_sum);

    return EXIT_SUCCESS;
}