#ifndef _WRSTRUCT_H_
#define _WRSTRUCT_H_
#include <windows.h>
#include "list.h"


typedef struct wwPixel
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
}wwPixel, wwColor;

typedef struct wwRenderer
{
    int width;
    int height;
    wwPixel **pixels;
}wwRenderer;

typedef struct wwTexture
{
    int width;
    int height;
    wwPixel **pixels;
}wwTexture;

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
    wwList *rectangles;
    wwList *menus;
}wwWindowAndRenderer;
#endif /* _WRSTRUCT_H_ */