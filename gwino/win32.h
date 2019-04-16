#ifndef __LIBWIN32__
#define __LIBWIN32__

#include <windows.h>

int     GowinRunMain();
void    GowinMsgBox(const char *msg, const char *title);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
    LPSTR lpCmdLine, int nCmdShow);
#endif