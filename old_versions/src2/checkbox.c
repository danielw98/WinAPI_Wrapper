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
    checkbox->x = x;
    checkbox->y = y;
    checkbox->width = width;
    checkbox->height = height;
    checkbox->text = text;
    wwList_Append(windowAndRenderer->checkboxes, checkbox);
    
    return checkbox;
}
void wwCheckbox_SetCallback(wwCheckbox *checkBox, wwCheckboxCallback callback, void *userData)
{
    checkBox->callback = callback;
    checkBox->userData = userData;
}

int wwCheckbox_IsChecked(wwCheckbox *checkBox, wwWindowAndRenderer *windowAndRenderer)
{
    return IsDlgButtonChecked(windowAndRenderer->hwnd, checkBox->id);
}

void wwCheckbox_SetChecked(wwCheckbox *checkBox, wwWindowAndRenderer *windowAndRenderer, int checked)
{
    if(checked == 0)
        CheckDlgButton(windowAndRenderer->hwnd, checkBox->id, BST_UNCHECKED);
    else
        CheckDlgButton(windowAndRenderer->hwnd, checkBox->id, BST_CHECKED);

}