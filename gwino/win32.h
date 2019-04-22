#ifndef __LIBWIN32__
#define __LIBWIN32__

#include <windows.h>
#include <stdlib.h>

struct GwinoMenuItem
{
    char *Text;
    struct GwinoMenuItem *Children;
    struct GwinoMenuItem *Next;
    struct GwinoMenuItem *Head;
};

void    GwinoAppendMenuItem(char *text);
void    GwinoInitMenuItems();
int     GwinoRunMain();
void    GwinoMsgBox(const char *msg, const char *title);
void    GwinoWindow(const char *title, int width, int height);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
#endif