#include "button.h"

extern FILE *fp;

wwButton* wwButton_Create(wwWindowAndRenderer *windowAndRenderer, wchar_t *text, int x, int y, int width, int height)
{
    wwButton *button = (wwButton*) malloc(sizeof(wwButton));
    if(windowAndRenderer->buttons == NULL)
    {
        windowAndRenderer->buttons = wwList_CreateEmpty(sizeof(wwButton), TRUE);
        fprintf(fp, "created buttons list %p\n", windowAndRenderer->buttons);
    }
    fprintf(fp, "creating button %p\n", button);
    wwWidget_Create(&button->widget, text, x, y, width, height);
    wwList_Append(windowAndRenderer->buttons, button);
    return button;
}

void wwButton_SetCallback(wwButton *button, wwButtonCallback callback, void *userData)
{
    wwWidget_SetCallback((wwWidget*) button, (wwWidgetCallback) callback, userData);
}

void wwButton_SetText(wwButton *button, wchar_t *text)
{
    wwWidget_SetText(&button->widget, text);
}
void wwButton_SetX(wwButton *button, int x)
{
    wwWidget_SetX(&button->widget, x);
}
void wwButton_SetY(wwButton *button, int y)
{
    wwWidget_SetY(&button->widget, y);
}
void wwButton_SetWidth(wwButton *button, int width)
{
    wwWidget_SetWidth(&button->widget, width);
}
void wwButton_SetHeight(wwButton *button, int height)
{
    wwWidget_SetHeight(&button->widget, height);
}
wchar_t* wwButton_GetText(wwButton *button)
{
    return wwWidget_GetText(&button->widget);
}
void wwButton_SetColor(wwButton *button, wwColor color)
{
    return;
}
