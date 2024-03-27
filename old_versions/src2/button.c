#include "button.h"

extern FILE *fp;

wwButton* wwButton_Create(wwWindowAndRenderer *windowAndRenderer, wchar_t *name, int x, int y, int width, int height)
{
    wwButton *button = (wwButton*) malloc(sizeof(wwButton));
    if(windowAndRenderer->buttons == NULL)
    {
        windowAndRenderer->buttons = wwList_CreateEmpty(sizeof(wwButton), TRUE);
        fprintf(fp, "created buttons list %p\n", windowAndRenderer->buttons);
    }
    fprintf(fp, "creating button %p\n", button);
    button->x = x;
    button->y = y;
    button->width = width;
    button->height = height;
    button->name = name;
    wwList_Append(windowAndRenderer->buttons, button);
    
    return button;
}

void wwButton_SetCallback(wwButton *button, wwButtonCallback callback, void *userData)
{
    button->callback = callback;
    button->userData = userData;
}

void wwButton_SetText(wwButton *button, wchar_t *text)
{
    button->name = text;
}
void wwButton_SetX(wwButton *button, int x)
{
    button->x = x;
    SetWindowPos(button->window, 0, button->x, button->y, button->width, button->height, SWP_NOZORDER | SWP_SHOWWINDOW);
}
void wwButton_SetY(wwButton *button, int y)
{
    button->y = y;
    SetWindowPos(button->window, 0, button->x, button->y, button->width, button->height, SWP_NOZORDER | SWP_SHOWWINDOW);
}
void wwButton_SetWidth(wwButton *button, int width)
{
    button->width = width;
    SetWindowPos(button->window, 0, button->x, button->y, button->width, button->height, SWP_NOZORDER | SWP_SHOWWINDOW);
}
void wwButton_SetHeight(wwButton *button, int height)
{
    button->height = height;
    SetWindowPos(button->window, 0, button->x, button->y, button->width, button->height, SWP_NOZORDER | SWP_SHOWWINDOW);
}