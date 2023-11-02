#include "statmethods.hpp"

int main(void) {
    auto p { pair::pair<uint64_t>::to_wstr() };
    ::_putws(p.c_str());

    const auto q { pair::pair<long double>::to_wstr() };
    ::_putws(q.c_str());

    return EXIT_SUCCESS;
}