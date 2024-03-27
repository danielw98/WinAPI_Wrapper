#include "widget.h"
void wwWidget_Create(wwWidget *widget, wchar_t *text, int x, int y, int width, int height)
{
    widget->text     = text;
    widget->x        = x;
    widget->y        = y;
    widget->width    = width;
    widget->height   = height;
    widget->callback = NULL;
    widget->userData = NULL;
}

void wwWidget_SetCallback(wwWidget *widget, wwWidgetCallback callback, void *userData)
{
    widget->callback = callback;
    widget->userData = userData;
}

void wwWidget_SetText(wwWidget *widget, wchar_t *text)
{
    widget->text = text;
    SetWindowTextW(widget->window, text);
}
void wwWidget_SetX(wwWidget *widget, int x)
{
    widget->x = x;
    SetWindowPos(widget->window, 0, widget->x, widget->y, widget->width, widget->height, SWP_NOZORDER | SWP_SHOWWINDOW);
}
void wwWidget_SetY(wwWidget *widget, int y)
{
    widget->y = y;
    SetWindowPos(widget->window, 0, widget->x, widget->y, widget->width, widget->height, SWP_NOZORDER | SWP_SHOWWINDOW);
}
void wwWidget_SetWidth(wwWidget *widget, int width)
{
    widget->width = width;
    SetWindowPos(widget->window, 0, widget->x, widget->y, widget->width, widget->height, SWP_NOZORDER | SWP_SHOWWINDOW);
}
void wwWidget_SetHeight(wwWidget *widget, int height)
{
    widget->height = height;
    SetWindowPos(widget->window, 0, widget->x, widget->y, widget->width, widget->height, SWP_NOZORDER | SWP_SHOWWINDOW);
}

wchar_t* wwWidget_GetText(wwWidget *widget)
{
    int length = GetWindowTextLengthW(widget->window);
    wchar_t *text = (wchar_t*) malloc((length + 1) * sizeof(wchar_t));
    GetWindowTextW(widget->window, text, length);
    return text;
}