#ifndef _WIDGET_H_
#define _WIDGET_H_
#include "wrstruct.h"
#include "color.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct wwWidget wwWidget;
typedef void (*wwWidgetCallback)(wwWidget *widget, wwWindowAndRenderer *windowAndRenderer);
struct wwWidget
{
    HWND window;
    wchar_t *text;
    int x;
    int y;
    int width;
    int height;
    unsigned short id;
    unsigned short widgetId;
    wwWidgetCallback callback;
    void *userData;
};
void wwWidget_Create(wwWidget *widget, wchar_t *text, int x, int y, int width, int height);
void wwWidget_SetCallback(wwWidget *widget, wwWidgetCallback callback, void *userData);
void wwWidget_SetText(wwWidget *widget, wchar_t *text);
void wwWidget_SetX(wwWidget *widget, int x);
void wwWidget_SetY(wwWidget *widget, int y);
void wwWidget_SetWidth(wwWidget *widget, int width);
void wwWidget_SetHeight(wwWidget *widget, int height);
/* returns malloc() pointer, should free() after usage */
wchar_t* wwWidget_GetText(wwWidget *widget);
#endif /* _WIDGET_H_ */