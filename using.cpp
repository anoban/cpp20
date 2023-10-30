#include <cstdio>

using uint64_t = unsigned long long;  // with the using directive the new alias goes in the LHS
typedef const wchar_t* const LPCWSTR; // with typedefs the new alias goes in the RHS

typedef char*                String;  // character pointer or a character array
typedef String const         CString; // constant pointer to, a character or a character array
// equivalent to typedef char* const CString;

using WString  = wchar_t*;      // pointer to wide character (short) or wide character array
using CWString = WString const; // constant pointer to, wide character or a wide character array
// equivalent to using CWString = wchar_t* const;

// Here comes the trouble.

typedef short*          u16String;  // an array of shorts / pointer to a short.
typedef const u16String u16CString; // we'd (reasonably so) expect this to be a pointer to a constant short or an array of constant shorts
// the above is NOT equivalent to typedef const short* u16CString;
// this would make it a pointer to a constant shorts array.

// BUT u16CString is actually a constant pointer to a short / shorts array.
// what happened here cannot be explained by a simple textual substitution.

using _u16CString = const u16String;

// typedefs and using directives create type alises NOT new types.

// SO HOW DO WE CREATE AN ALIAS FOR AN ARRAY OF CONSTANT wchar_ts?
typedef const wchar_t* _CWString;
using __CWString = const wchar_t*;

int main(void) {
    LPCWSTR        name { L"ANOBAN" };
    const uint64_t age { 27 };
    ::_putws(name);
    ::wprintf_s(L"Aged %llu years\n", age);

    // let's test this
    u16CString  laptop { L"Dell" }; // a wide string literal is of type const wchar_t* (const short*)
    // yet we get an error saying that u16CString is short* const

    _u16CString uslaptop { L"Alienware" };                 // we run into the same problem with the using directive too

    _CWString   cnstStr { L"Typedeffed constant string" }; // works
    __CWString  _cnstStr { L"Constant string" };           // Works too :)

    return 0;
}