#include <cstdio>
#include <string>

/* non nesting comments /* another one yeah? Well umm! NO! */

const long double      value {}; // see! This ain't considered a comment!

std::wstring constexpr operator""_W(_In_ const wchar_t* const wchars, std::size_t length) { return ::std::wstring(wchars); }

int                    main(void) {
    const auto name { L"Anoban"_W };
    ::_putws(name.c_str());

    ::std::string laptop { "DELL" };
    return 0;
}