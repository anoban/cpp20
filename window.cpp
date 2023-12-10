#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_MEAN
#include <string>

#include <Windows.h>
#pragma comment(lib, "wingdi.lib")

namespace Win32 {

    class Window {
        private:
            WNDCLASSEXW __window {};
            HWND        __hWnd {};
            HINSTANCE   __hInstance {};

        public:
            Window(
                _In_ const HINSTANCE& hInstance,
                _In_ const HWND&      hParentWindow,
                _In_ const std::wstring& window_class,
                _In_ const std::wstring& window_title,
                _In_ const WNDPROC&      EventHandler
            ) noexcept {
                __hWnd = ::CreateWindowExW(
                    WS_EX_CLIENTEDGE | WS_EX_WINDOWEDGE | WS_EX_STATICEDGE | WS_EX_APPWINDOW | WS_EX_DLGMODALFRAME,
                    window_class.c_str(),
                    window_title.c_str(),
                    WS_SYSMENU | WS_THICKFRAME | WS_TILED | WS_VISIBLE | WS_SIZEBOX | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    470,
                    240,
                    hParentWindow,
                    nullptr,
                    hInstance,
                    nullptr
                );

                __window.cbSize        = sizeof(WNDCLASSEX);
                __window.style         = CS_HREDRAW | CS_VREDRAW;
                __window.lpfnWndProc   = EventHandler;
                __window.cbClsExtra    = 0;
                __window.cbWndExtra    = 0;
                __window.hInstance     = hInstance;
                __window.hIcon         = ::LoadIconW(nullptr, IDI_WINLOGO);
                __window.hCursor       = ::LoadCursorW(nullptr, IDC_ARROW);
                __window.hbrBackground = ::CreateSolidBrush(COLOR_WINDOW);
                __window.lpszMenuName  = window_title.c_str();
                __window.lpszClassName = window_class.c_str();
                __window.hIconSm       = LoadIconW(nullptr, IDI_APPLICATION);

                ::RegisterClassExW(&__window);
            }

            ~Window() {};

            static bool EventHandler() { }

    }; // class Window

} // namespace Win32

int APIENTRY wWinMain(
    _In_ HINSTANCE hInstance, _In_opt_ [[maybe_unused]] HINSTANCE hPrevInstance, _In_ [[maybe_unused]] LPWSTR lpCmdLine, _In_ int nCmdShow
) {
    auto window { Win32::Window(hInstance, nullptr, L"Window", L"Hello", ) };
    MSG  msg {};

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0)) {
        if (!::TranslateAcceleratorW(msg.hwnd, hAccelTable, &msg)) {
            ::TranslateMessage(&msg);
            ::DispatchMessageW(&msg);
        }
    }

    return (int) msg.wParam;
}