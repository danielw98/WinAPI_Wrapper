#include "checkbox.h"

extern FILE *fp;

wwCheckbox* wwCheckbox_Create(wwWindowAndRenderer *windowAndRenderer, wchar_t *text, int x, int y, int width, int height)
{
    wwCheckbox *checkbox = (wwCheckbox*) malloc(sizeof(wwCheckbox));
    if(windowAndRenderer->checkboxes == NULL)
    {
        windowAndRenderer->checkboxes = wwList_CreateEmpty(sizeof(wwCheckbox), TRUE);
        fprintf(fp, "created checkbox list %p\n", windowAndRenderer->checkboxes);
    }
    fprintf(fp, "creating checkbox %p\n", checkbox);
    wwWidget_Create(&checkbox->widget, text, x, y, width, height);
    wwList_Append(windowAndRenderer->checkboxes, checkbox);
    
    return checkbox;
}
void wwCheckbox_SetCallback(wwCheckbox *checkbox, wwCheckboxCallback callback, void *userData)
{
    wwWidget_SetCallback((wwWidget*) checkbox, (wwWidgetCallback) callback, userData);
}
int wwCheckbox_IsChecked(wwCheckbox *checkBox, wwWindowAndRenderer *windowAndRenderer)
{
    return IsDlgButtonChecked(windowAndRenderer->hwnd, checkBox->widget.id);
}

void wwCheckbox_SetChecked(wwCheckbox *checkBox, wwWindowAndRenderer *windowAndRenderer, int checked)
{
    if(checked == 0)
        CheckDlgButton(windowAndRenderer->hwnd, checkBox->widget.id, BST_UNCHECKED);
    else
        CheckDlgButton(windowAndRenderer->hwnd, checkBox->widget.id, BST_CHECKED);
}


void wwCheckbox_SetText(wwCheckbox *checkbox, wchar_t *text)
{
    wwWidget_SetText(&checkbox->widget, text);
}
void wwCheckbox_SetX(wwCheckbox *checkbox, int x)
{
    wwWidget_SetX(&checkbox->widget, x);
}
void wwCheckbox_SetY(wwCheckbox *checkbox, int y)
{
    wwWidget_SetY(&checkbox->widget, y);
}
void wwCheckbox_SetWidth(wwCheckbox *checkbox, int width)
{
    wwWidget_SetWidth(&checkbox->widget, width);
}
void wwCheckbox_SetHeight(wwCheckbox *checkbox, int height)
{
    wwWidget_SetHeight(&checkbox->widget, height);
}

wchar_t* wwCheckbox_GetText(wwCheckbox *checkbox)
{
    return wwWidget_GetText(&checkbox->widget);
}