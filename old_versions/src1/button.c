#include "button.h"

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