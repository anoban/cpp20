#include <concepts>
#include <cstdio>

// What is sq(12.090) in C++?
// Say hello to syntactic ambiguity!

#define sq(n) ((n) * (n))

#ifndef __ALLOW_FUNC_LIKE_MACROS
    #undef sq
#endif

double constexpr sq(double n) { return n * n; }

template<typename T> concept scalar_type = std::floating_point<T> || std::integral<T>;

template<typename T> requires scalar_type<T> constexpr T sq(const T& n) { return n * n; }

class sq {
    private:
        double _s {};

    public:
        constexpr sq(const double val) noexcept : _s { val * val } { }
};

class sq_t {
    public:
        using value_type = long double;
        value_type constexpr operator()(long double x) const { return x * x; }
};

int main(void) {
    constexpr auto                                                                    value { sq(12.7856872f) };
    constexpr auto                                                                    value_ { sq(54.356456454) };

    constexpr auto                                                                    value__ { sq<int64_t>(75) };
    constexpr auto                                                                    value___ { sq(75) };

    constexpr class /* class is redundant but mandatory here to avoid ambiguity */ sq square {
            34.53645
    };

    constexpr sq_t result { sq_t(7.6542654) };
    return 0;
}
