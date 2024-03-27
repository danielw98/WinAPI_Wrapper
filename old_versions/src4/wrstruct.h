#ifndef _WRSTRUCT_H_
#define _WRSTRUCT_H_
#include <windows.h>
#include "list.h"
typedef struct wwWindowAndRenderer
{
    MSG msg;
    WNDCLASSW wc;
    HWND hwnd;
    wchar_t *windowName;
    int x;
    int y;
    int width;
    int height;
    wwList *buttons;
    wwList *labels;
    wwList *checkboxes;
    wwList *textboxes;
    wwList *listboxes;
}wwWindowAndRenderer;
#endif /* _WRSTRUCT_H_ */