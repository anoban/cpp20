#define WIN32_LEAN_AND_MEAN
#include <string>

#include <Windows.h>

namespace Win32 {
    class Window {
        private:
            WNDCLASSEXW __window {};
            HWND        __hWnd {};
            HINSTANCE   __hInstance {};

        public:
            Window(
                _In_ const HWND& hwndParentWindow, _In_ const std::wstring& window_class, _In_ const std::wstring& window_title
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
                    nullptr,
                    nullptr,
                    hwndParentWindow,
                    nullptr
                );

                __window.cbSize        = sizeof(WNDCLASSEX);
                __window.style         = CS_HREDRAW | CS_VREDRAW;
                __window.lpfnWndProc   = WindowHandler;
                __window.cbClsExtra    = 0;
                __window.cbWndExtra    = 0;
                __window.hInstance     = hInstance;
                __window.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_COLORPICKER));
                __window.hCursor       = LoadCursor(nullptr, IDC_ARROW);
                __window.hbrBackground = ::CreateSolidBrush(COLOR_WINDOW);
                __window.lpszMenuName  = MAKEINTRESOURCEW(IDC_COLORPICKER);
                __window.lpszClassName = szWindowClass;
                __window.hIconSm       = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

                ::RegisterClassExW(&__window);
            }
            ~Window() {};
    };
} // namespace Win32

int APIENTRY wWinMain(
    _In_ HINSTANCE hInstance, _In_opt_ [[maybe_unused]] HINSTANCE hPrevInstance, _In_ [[maybe_unused]] LPWSTR lpCmdLine, _In_ int nCmdShow
) {
    // TODO: Place code here.

    // Initialize global strings
    ::LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    ::LoadStringW(hInstance, IDC_COLORPICKER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!::InitInstance(hInstance, nCmdShow)) return FALSE;

    HACCEL hAccelTable = ::LoadAcceleratorsW(hInstance, MAKEINTRESOURCEW(IDC_COLORPICKER));

    MSG    msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0)) {
        if (!::TranslateAcceleratorW(msg.hwnd, hAccelTable, &msg)) {
            ::TranslateMessage(&msg);
            ::DispatchMessageW(&msg);
        }
    }

    return (int) msg.wParam;
}