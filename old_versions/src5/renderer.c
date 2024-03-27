#include "renderer.h"

void wwRenderer_CreateRectangle(wwWindowAndRenderer *win, wwRect *rect)
{
    static unsigned short id = 0;
    wwRectStruct *rectangle = (wwRectStruct*) malloc(sizeof(wwRectStruct));
   
    if(win->rectangles == NULL)
        win->rectangles = wwList_CreateEmpty(sizeof(wwRectStruct), TRUE, NULL);
    rectangle->rect.x      = rect->x;
    rectangle->rect.y      = rect->y;
    rectangle->rect.width  = rect->width;
    rectangle->rect.height = rect->height;
    rectangle->visible     = TRUE;
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
void wwRenderer_DrawRectangle(wwWindowAndRenderer *win, wwRect *rect)
{
    if(rect == NULL)
        return;
    wwRectStruct *rectStruct = (wwRectStruct*) rect;
    HBRUSH color;
    HDC hdc = GetDC(win->hwnd);
    if(rectStruct->visible == TRUE) 
        color = CreateSolidBrush(RGB(0, 0, 255));
    else
        color = CreateSolidBrush(GetBkColor(hdc));
    RECT windowsRect = {.left = rect->x, .top = rect->y};
    windowsRect.right  = rect->x + rect->width;
    windowsRect.bottom = rect->y + rect->height;
    FillRect(hdc, &windowsRect, color);
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
    wwRenderer_DisplayRectangle(win, rect);
}
/* returns -1 if rect doesn't exist */
int wwRect_GetVisible(wwRect *rect)
{
    if(rect == NULL)
        return -1;
    wwRectStruct *rectStruct = (wwRectStruct*) rect;
    return rectStruct->visible;
}