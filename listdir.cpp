#ifdef _WIN32
    #define _AMD64_ // architecture
    #define WIN32_LEAN_AND_MEAN
    #define WIN32_EXTRA_MEAN
#endif

#include <string>
#include <vector>

#include <errhandlingapi.h>
#include <fileapi.h>
#include <handleapi.h>
#include <sal.h>
#include <stdio.h>
#include <strsafe.h>

#pragma comment(lib, "User32.lib")

[[nodiscard]] static inline std::vector<std::wstring> listdir(
    _In_ const std::wstring& dirname, _In_opt_ const bool recurse = false
) noexcept {
    WIN32_FIND_DATA           fdFindData {};
    LARGE_INTEGER             filesize {};
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
            _tprintf(TEXT("  %s   <DIR>\n"), ffd.cFileName);
            ;
        } else {
            filesize.LowPart  = ffd.nFileSizeLow;
            filesize.HighPart = ffd.nFileSizeHigh;
            _tprintf(TEXT("  %s   %ld bytes\n"), ffd.cFileName, filesize.QuadPart);
        }
    } while (::FindNextFileW(hFind, &fdFindData));

    dwError = ::GetLastError();
    if (dwError != ERROR_NO_MORE_FILES) DisplayErrorBox(TEXT("FindFirstFile"));

    FindClose(hFind);
}

int wmain(_In_ const int32_t argc, _In_opt_count_(argc) wchar_t* argv[]) {
    // If the directory is not specified as a command-line argument,
    // print usage.

    if (argc < 2 || argc > 3) {
        // -R for recurse
        ::fwprintf_s(stderr, L"\nUsage: %s <directory name> [-R]\n", argv[0]);
        return -1;
    }

    const auto argvwstr { std::wstring { argv[1] } };

    return EXIT_SUCCESS;
}
