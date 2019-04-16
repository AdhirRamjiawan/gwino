#include "win32.h"

const char wndClassName[] = "windowClass";

// =========================================================================
//
//              GOLANG METHODS
//
// =========================================================================

int GwinoRunMain()
{
    int retCode = WinMain(NULL, NULL,NULL, 1);
    return retCode;
}

void GwinoMsgBox(const char *msg, const char *title)
{
    MessageBox(NULL, msg, title, MB_OK);
}

void GwinoWindow(const char *title, int width, int height)
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    InitWindow(hInstance, title, width, height);
}

// =========================================================================
//
//              WIN32 METHODS
//
// =========================================================================


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


void InitWNDCLASSEX(WNDCLASSEX *wc, HINSTANCE hInstance)
{
    wc->cbSize        = sizeof(WNDCLASSEX);
    wc->style         = 0;
    wc->lpfnWndProc   = WndProc;
    wc->cbClsExtra    = 0;
    wc->cbWndExtra    = 0;
    wc->hInstance     = hInstance;
    wc->hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc->hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc->hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc->lpszMenuName  = NULL;
    wc->lpszClassName = wndClassName;
    wc->hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
}

void InitWindow(HINSTANCE hInstance, const char *title, int width, int height)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    InitWNDCLASSEX(&wc, hInstance);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Reg Error!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        wndClassName,
        title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    // Step 3: The Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
    LPSTR lpCmdLine, int nCmdShow)
{
    libWin32MainCallback();
    return 0;
}