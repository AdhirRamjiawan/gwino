#include "win32.h"


// almost like a template for this window
const char wndClassName[] = "windowClass";

struct GwinoMenuItem *gwinoMenuItems;

// =========================================================================
//
//              GOLANG METHODS
//
// =========================================================================

int GwinoRunMain()
{
    int retCode = WinMain(NULL, NULL, NULL, 1);
    return retCode;
}

void GwinoCleanUp()
{
    // NEED TO ADD ALL FREE FOR MALLOC ETC HERE AND CALL IT SOMEWHERE
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

void GwinoInitMenuItems()
{
    gwinoMenuItems = (struct GwinoMenuItem *) malloc(sizeof(struct GwinoMenuItem));
    gwinoMenuItems->Head = gwinoMenuItems;
}

void GwinoAppendMenuItem(char *text)
{
    gwinoMenuItems->Next = (struct GwinoMenuItem *) malloc(sizeof(struct GwinoMenuItem));
    
    gwinoMenuItems->Next->Head = gwinoMenuItems->Head;
    gwinoMenuItems->Next->Text = (char *)malloc(sizeof(char) * strlen(text));
    strcpy(gwinoMenuItems->Next->Text, text);
    
    gwinoMenuItems = gwinoMenuItems->Next;
}


// =========================================================================
//
//              WIN32 METHODS
//
// =========================================================================

#define ID_FILE_EXIT 9001

void SetupMenu(HWND hwnd)
{
    HMENU hMenu, hSubMenu;
    HICON hIcon;

    hMenu = CreateMenu();
    hSubMenu = CreatePopupMenu();
    //AppendMenu(hSubMenu, MF_STRING, ID_FILE_EXIT, "E&xit");
    //AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");

    gwinoMenuItems = gwinoMenuItems->Head->Next;

    while (gwinoMenuItems != NULL)
    {  
        HMENU hSubMenu = CreatePopupMenu();

        AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, gwinoMenuItems->Text);
        gwinoMenuItems = gwinoMenuItems->Next;
    }

    SetMenu(hwnd, hMenu);

    hIcon = LoadImage(NULL, "file.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
    if(hIcon)
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    else
        MessageBox(hwnd, "Could not load large icon!", "Error", MB_OK | MB_ICONERROR);
        
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_LBUTTONDOWN: 
            //MessageBox(NULL, "msg", "title", MB_OK);
            MouseDownEventHandler();
        break;
        case WM_CREATE:
            SetupMenu(hwnd);
        break;
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
    }

    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    //return Msg.wParam;

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
    LPSTR lpCmdLine, int nCmdShow)
{
    libWin32MainCallback();
    return 0;
}