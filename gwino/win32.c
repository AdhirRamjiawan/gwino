#include "win32.h"

int GowinRunMain()
{
    int retCode = WinMain(NULL, NULL,NULL, 1);
    return retCode;
}

void GowinMsgBox(const char *msg, const char *title)
{
    MessageBox(NULL, msg, title, MB_OK);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
    LPSTR lpCmdLine, int nCmdShow)
{
    libWin32MainCallback();
    return 0;
}