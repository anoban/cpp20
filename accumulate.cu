#include <algorithm>
#include <concepts>
#include <cstdlib>
#include <vector>

#include <thrust/device_vector.h>
#include <thrust/host_vector.h>

template<typename T> requires std::integral<T> || std::floating_point<T> __global__ void SumKernel(
    _In_ const thrust::device_vector<T>& in_vector_0,
    _In_ const thrust::device_vector<T>& in_vector_1,
    _Inout_ thrust::device_vector<T>& out_vector
) {
    const auto tId { threadIdx.x };
    out_vector[tId] = in_vector_0[tId] + in_vector_1[tId];
    return;
}

template<typename T> requires std::is_integral<T>::value || std::is_floating_point<T>::value
static inline thrust::host_vector<T> KernelManager(
    _In_ const std::vector<T>& in_vector_0, _In_ const std::vector<T>& in_vector_1, _Inout_ const std::vector<T>& out_vector
) noexcept {
    if (in_vector_0.size() != in_vector_1.size()) {
        _putws(L"Both input vectors must be os the same size!");
        return thrust::host_vector<T> {};
    }
    thrust::device_vector<T> dev_0 { in_vector_0.begin(), in_vector_0.end() };
    thrust::device_vector<T> dev_1 { in_vector_1.begin(), in_vector_1.end() };
    thrust::device_vector<T> dev_res { out_vector.begin(), out_vector.end() };

    SumKernel<T><<<1, in_vector_0.size()>>>(dev_0, dev_1, dev_res);
    cudaDeviceSynchronize();
    return thrust::host_vector<T> { dev_res };
}

int main(void) {
    ::srand(time(nullptr));

    std::vector<int64_t> randoms_0(300);
    std::vector<int64_t> randoms_1(300);
    std::for_each(randoms_0.begin(), randoms_0.end(), [](int64_t& r_0) { r_0 = ::rand(); });
    std::for_each(randoms_1.begin(), randoms_1.end(), [](int64_t& r_1) { r_1 = ::rand(); });

    std::vector<int64_t> sums(300);
    for (std::size_t i {}; i < 300; ++i) sums.at(i) = randoms_0.at(i) + randoms_1.at(i);

    auto device_results { KernelManager<int64_t>(randoms_0, randoms_1, sums) };

    _putws(L"  Host sum       ||  Device sum      \n");
    for (std::size_t i {}; i < 300; ++i) wprintf_s(L"%10lld    %10lld\n", sums.at(i), device_results[i]);
    return EXIT_SUCCESS;
}