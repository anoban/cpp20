#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #define WIN32_EXTRA_MEAN
#endif

#include <string>
#include <vector>

#include <Windows.h>

[[nodiscard]] static inline std::vector<std::wstring> listdir(
    _In_ const std::wstring& dirname, _In_opt_ const bool recurse = false
) noexcept {
    WIN32_FIND_DATAW          fdFindData {};
    HANDLE                    hFind { INVALID_HANDLE_VALUE };
    DWORD                     dwError {};
    std::vector<std::wstring> list {};

    // Check that the input path plus 3 is not longer than MAX_PATH.
    // Three characters are for the "\*" plus NULL appended below.

    if (dirname.length() > (MAX_PATH - 3)) {
        ::fputws(L"\nDirectory path is too long.", stderr);
        return list;
    }

    ::wprintf_s(L"\nTarget directory is %s\n\n", dirname.c_str());

    // Prepare string for use with FindFile functions.  First, copy the
    // string to a buffer, then append '\*' to the directory name.

    auto directory { dirname };
    directory += L"\\*";

    // Find the first file in the directory.
    hFind      = ::FindFirstFileW(directory.c_str(), &fdFindData);

    if (INVALID_HANDLE_VALUE == hFind) return list;

    // collect all the files in the directory

    do {
        if (fdFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            // ::wprintf_s(L"%s   <DIR>\n", fdFindData.cFileName);
            ;
            ;
        } else {
            ::wprintf_s(L"%s\b\b%s\n", directory.c_str(), fdFindData.cFileName);
            list.emplace_back(fdFindData.cFileName);
        }
    } while (::FindNextFileW(hFind, &fdFindData));

    dwError = ::GetLastError();
    if (dwError != ERROR_NO_MORE_FILES) {
        LPWSTR lpwszFmtMessageBuffer {};
        ::FormatMessageW(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM /* locally allocate memory */,
            nullptr,
            dwError,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            lpwszFmtMessageBuffer,
            0,
            nullptr
        );
        ::wprintf_s(L"Error %s in FindFirstFileW\n", lpwszFmtMessageBuffer);
        ::LocalFree(lpwszFmtMessageBuffer);
    }
    ::FindClose(hFind);
    return list;
}

int wmain(_In_ const int32_t argc, _In_opt_count_(argc) wchar_t* argv[]) {
    // If the directory is not specified as a command-line argument,
    // print usage.

    if (argc < 2 || argc > 3) {
        // -R for recurse
        ::fwprintf_s(stderr, L"\nUsage: %s <directory name> [-R]\n", argv[0]);
        return -1;
    } else if ((argc == 3) && !wcscmp(argv[2], L"-R")) {
        ::fwprintf_s(stderr, L"The second optional argument can only be -R, for recursive search\n", argv[0]);
        return -2;
    }

    const auto dir { std::wstring { argv[1] } };
    const auto files { listdir(dir, false) };
    for (const auto& fname : files) ::_putws(fname.c_str());

    return EXIT_SUCCESS;
}
