#define UNICODE
#define _UNICODE

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    POINT cursorPos;
    GetCursorPos(&cursorPos);
    HMONITOR hMonitor = MonitorFromPoint(cursorPos, MONITOR_DEFAULTTONEAREST);

    // Get the monitor's information
    MONITORINFO monitorInfo;
    monitorInfo.cbSize = sizeof(MONITORINFO);
    GetMonitorInfo(hMonitor, &monitorInfo);

    int width = monitorInfo.rcWork.right - monitorInfo.rcWork.left;
    int height = monitorInfo.rcWork.bottom - monitorInfo.rcWork.top;

    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Exemple de formulaire WinAPI",
        WS_OVERLAPPEDWINDOW | WS_MAXIMIZE, 
        monitorInfo.rcWork.left, monitorInfo.rcWork.top, width, height,
        NULL,
        NULL,
        hInstance,
        NULL);

    if (hwnd == NULL)
    {
        return 0;
    }

    HWND hLabel = CreateWindowW(
        L"STATIC",
        L"Ceci est un label",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        50, 50, 200, 20,
        hwnd,
        NULL,
        hInstance,
        NULL);

    HWND hButton = CreateWindowW(
        L"BUTTON",
        L"Cliquez ici",
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        50, 100, 100, 30,
        hwnd,
        (HMENU)1,
        hInstance,
        NULL);

    if (hLabel == NULL || hButton == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {};

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_COMMAND:
    {
        if (LOWORD(wParam) == 1)
        {
            MessageBoxW(hwnd, L"Le bouton a été cliqué !", L"Information", MB_OK);
            return 0;
        }
        break;
    }

    case WM_ERASEBKGND:
        return 1;

    case WM_SIZE:
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        RECT clientRect;
        GetClientRect(hwnd, &clientRect);
        FillRect(hdc, &clientRect, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hwnd, &ps);
        return 0;
    }

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}
