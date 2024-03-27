#include "renderer.h"
#include "button.h"

void wwRenderer_CreateRectangle(wwWindowAndRenderer *win, wwRect *rect)
{
    static unsigned short id = 0;
    wwRectStruct *rectangle = (wwRectStruct*) malloc(sizeof(wwRectStruct));
   
    if(win->rectangles == NULL)
        win->rectangles = wwList_CreateEmpty(sizeof(wwRectStruct), wwTrue, NULL);
    rectangle->rect.x      = rect->x;
    rectangle->rect.y      = rect->y;
    rectangle->rect.width  = rect->width;
    rectangle->rect.height = rect->height;
    rectangle->visible     = wwTrue;
    rectangle->id          = id++;
    wwList_Append(win->rectangles, rectangle);
}

void wwRenderer_DisplayRectangle(wwWindowAndRenderer *win, wwRect *rect)
{
    if(rect == NULL)
        return;
    RECT windowsRect = {.left = rect->x, .top = rect->y};
    windowsRect.right  = rect->x + rect->width;
    windowsRect.bottom = rect->y + rect->height;
    InvalidateRect(win->hwnd, &windowsRect, FALSE);
    //InvalidateRect(win->hwnd, NULL, TRUE);
}

void wwRenderer_DrawRectangle(wwWindowAndRenderer *win, wwRect *rect, wwColor color)
{
    if(rect == NULL)
        return;
    // wwRectStruct *rectStruct = (wwRectStruct*) rect;
    HBRUSH hbrushColor;
    HDC hdc = win->hdc;
    HPEN hpenOld =  (HPEN) SelectObject(hdc, GetStockObject(DC_PEN));
    HBRUSH hbrushOld = (HBRUSH) SelectObject(hdc, GetStockObject(NULL_BRUSH));
    SetDCPenColor(hdc, RGB(color.red, color.green, color.blue));
    // if(rectStruct->visible == TRUE) 
    // hbrushColor = CreateSolidBrush(RGB(color.red, color.green, color.blue)); // should also work i think
    // else
    //     hbrushColor = CreateSolidBrush(GetBkColor(hdc));
    RECT wRect = {.left = rect->x, .top = rect->y};
    wRect.right  = rect->x + rect->width;
    wRect.bottom = rect->y + rect->height;
    //FillRect(hdc, &windowsRect, hbrushColor); // should also work i think
    Rectangle(hdc, wRect.left, wRect.top, wRect.right, wRect.bottom);
    // restore the old object
    SelectObject(hdc, hpenOld);
    SelectObject(hdc, hbrushOld);
}

wwRect* wwRenderer_GetRectangleById(wwWindowAndRenderer *win, unsigned short id)
{
    wwList *rectangles = win->rectangles;
    if(rectangles == NULL)
        return NULL;
    Node *head = rectangles->head;
    while(head != NULL)
    {
        wwRectStruct *rectStruct = (wwRectStruct*) head->data;
        if(rectStruct->id == id)
            return (wwRect*) rectStruct;
        head = head->next;
    }
    return NULL;
}

void wwRect_SetVisible(wwWindowAndRenderer *win, wwRect *rect, int visible)
{
    if(rect == NULL)
        return;
    wwRectStruct *rectStruct = (wwRectStruct*) rect;
    rectStruct->visible = visible;
    // wwRenderer_DisplayRectangle(win, rect);
}
/* returns -1 if rect doesn't exist */
int wwRect_GetVisible(wwRect *rect)
{
    if(rect == NULL)
        return -1;
    wwRectStruct *rectStruct = (wwRectStruct*) rect;
    return rectStruct->visible;
}

void wwRenderer_Clear(wwWindowAndRenderer *win)
{
    InvalidateRect(win->hwnd, NULL, TRUE);
    // RedrawWindow(win->hwnd, NULL, NULL, RDW_NOCHILDREN);
    BeginPaint(win->hwnd, &win->ps);
}

void wwRenderer_Display(wwWindowAndRenderer *win)
{
    EndPaint(win->hwnd, &win->ps);
}