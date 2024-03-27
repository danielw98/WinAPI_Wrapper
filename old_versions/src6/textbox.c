#include "textbox.h"
extern FILE *fp;
wwTextbox* wwTextbox_Create(wwWindowAndRenderer *windowAndRenderer, wchar_t *text, int x, int y, int width, int height)
{
    wwTextbox *textbox = (wwTextbox*) malloc(sizeof(wwTextbox));
    if(windowAndRenderer->textboxes == NULL)
    {
        windowAndRenderer->textboxes = wwList_CreateEmpty(sizeof(wwTextbox), TRUE, wwWidget_FreeFunc);
        fprintf(fp, "created textbox list %p\n", windowAndRenderer->buttons);
    }
    fprintf(fp, "creating textbox %p\n", textbox);
    wwWidget_Create(&textbox->widget, text, x, y, width, height);
    wwList_Append(windowAndRenderer->textboxes, textbox);
    
    return textbox;
}
void wwTextbox_SetCallback(wwTextbox *textBox, wwTextboxCallback callback, void *userData)
{
    wwWidget_SetCallback((wwWidget*) textBox, (wwWidgetCallback) callback, userData);
}
void wwTextbox_SetText(wwTextbox *textBox, wchar_t *text)
{
    wwWidget_SetText(&textBox->widget, text);
}
void wwTextbox_SetX(wwTextbox *textBox, int x)
{
    wwWidget_SetX(&textBox->widget, x);
}
void wwTextbox_SetY(wwTextbox *textBox, int y)
{
    wwWidget_SetY(&textBox->widget, y);
}
void wwTextbox_SetWidth(wwTextbox *textBox, int width)
{
    wwWidget_SetWidth(&textBox->widget, width);
}
void wwTextbox_SetHeight(wwTextbox *textBox, int height)
{
    wwWidget_SetHeight(&textBox->widget, height);
}
wchar_t* wwTextbox_GetText(wwTextbox *textBox)
{
    return wwWidget_GetText(&textBox->widget);
}