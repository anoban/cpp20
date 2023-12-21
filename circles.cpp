#define _USE_MATH_DEFINES
#define NOMINMAX
#include <cmath>
#include <cstdint>
#include <string>

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_MEAN
#include <Windows.h>
#pragma comment(lib, "Gdi32.lib")
#pragma comment(lib, "User32.lib")

static constexpr std::size_t NMARKERS { 5'000 };
constexpr long double        PI { M_PI };

LRESULT WindowEventHandler(_In_ HWND hWindow, _In_ UINT uMessage, _In_ WPARAM wParameter, _In_ LPARAM lParameter) noexcept {
    static std::size_t x_windowcoord {}, y_windowcoord {};
    HDC                hDeviceContext {};
    PAINTSTRUCT        painter {};
    POINT              upperhalf[NMARKERS] {};
    POINT              lowerhalf[NMARKERS] {};

    switch (uMessage) {
        case WM_SIZE :
            {
                x_windowcoord = LOWORD(lParameter);
                y_windowcoord = HIWORD(lParameter);
                return 0;
            }
        case WM_PAINT :
            {
                hDeviceContext = BeginPaint(hWindow, &painter);

                MoveToEx(hDeviceContext, 0, y_windowcoord / 2, nullptr);
                LineTo(hDeviceContext, x_windowcoord, y_windowcoord / 2);

                const long double xd = x_windowcoord / NMARKERS;
                const long double yd = y_windowcoord / NMARKERS / 2;

                for (std::size_t i {}; i < NMARKERS; ++i) {
                    upperhalf[i].x = x_windowcoord + xd;
                    upperhalf[i].y = y_windowcoord + yd;
                }

                for (std::size_t i {}; i < NMARKERS; ++i) {
                    lowerhalf[i].x = x_windowcoord + xd;
                    lowerhalf[i].y = y_windowcoord - yd;
                }

                Polyline(hDeviceContext, upperhalf, NMARKERS);
                Polyline(hDeviceContext, lowerhalf, NMARKERS);
                return 0;
            }
        case WM_DESTROY :
            {
                PostQuitMessage(0);
                return 0;
            }
        case WM_CLOSE :
            {
                DestroyWindow(hWindow);
                return 0;
            }
    }
    // default window proc definition
    return DefWindowProcW(hWindow, uMessage, wParameter, lParameter);
}

class Window {
    private:
        HINSTANCE hInstance {};
        HWND      hWindow {};

    public:
        Window(void) noexcept : hInstance { GetModuleHandleW(nullptr) } {
            WNDCLASSEXW windowClass {};

            windowClass.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
            windowClass.cbSize        = sizeof(WNDCLASSEXW);
            windowClass.lpszClassName = L"Window";
            windowClass.hInstance     = hInstance;
            windowClass.hIcon         = LoadIconW(nullptr, IDI_WINLOGO);
            windowClass.hCursor       = LoadIconW(nullptr, IDC_ARROW);
            windowClass.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
            windowClass.lpszMenuName  = nullptr;
            windowClass.cbClsExtra    = 0;
            windowClass.cbWndExtra    = 0;
            windowClass.lpfnWndProc   = WindowEventHandler;

            if (!RegisterClassExW(&windowClass))
                MessageBoxExW(
                    hWindow,
                    L"RegisterClassExW failed!",
                    nullptr,
                    MB_OK | MB_ICONERROR | MB_APPLMODAL,
                    MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL)
                );

            hWindow = CreateWindowExW(
                WS_EX_OVERLAPPEDWINDOW | WS_EX_STATICEDGE | WS_EX_WINDOWEDGE,
                L"Window",
                L"Spectre",
                WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                nullptr,
                nullptr,
                hInstance,
                nullptr
            );
            ShowWindow(hWindow, SW_SHOW);
            UpdateWindow(hWindow);
        }

        Window(const Window&)            = delete;

        Window& operator=(const Window&) = delete;

        ~Window(void) noexcept { UnregisterClassW(L"Window", hInstance); }

        bool HandleEvents(void) const noexcept {
            MSG mWindowEvent {};
            while (PeekMessageW(&mWindowEvent, hWindow, 0, 0, PM_REMOVE)) {
                TranslateMessage(&mWindowEvent);
                DispatchMessageW(&mWindowEvent);
            }
            return (mWindowEvent.message == WM_QUIT) ? false : true;
        }
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    auto window { Window {} };
    while (window.HandleEvents()) Sleep(10);
    MessageBoxExW(nullptr, L"Window closed!", nullptr, MB_OK | MB_ICONERROR, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL));
    return EXIT_SUCCESS;
}