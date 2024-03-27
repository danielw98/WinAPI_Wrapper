#include "label.h"
extern FILE *fp;
wwLabel* wwLabel_Create(wwWindowAndRenderer *windowAndRenderer, wchar_t *labelText, int x, int y, int width, int height)
{
    wwLabel *label = (wwLabel*) malloc(sizeof(wwLabel));
    if(windowAndRenderer->labels == NULL)
    {
        windowAndRenderer->labels = wwList_CreateEmpty(sizeof(wwLabel), TRUE);
        fprintf(fp, "created labels list %p\n", windowAndRenderer->labels);
    }
    fprintf(fp, "creating label %p\n", label);
    wwWidget_Create(&label->widget, labelText, x, y, width, height);
    wwList_Append(windowAndRenderer->labels, label);
    return label;
}

void wwLabel_SetCallback(wwLabel *label, wwLabelCallback callback, void *userData)
{
    wwWidget_SetCallback((wwWidget*) label, (wwWidgetCallback) callback, userData);
}

void wwLabel_SetText(wwLabel *label, wchar_t *text)
{
    wwWidget_SetText(&label->widget, text);
}
void wwLabel_SetX(wwLabel *label, int x)
{
    wwWidget_SetX(&label->widget, x);
}
void wwLabel_SetY(wwLabel *label, int y)
{
    wwWidget_SetY(&label->widget, y);
}
void wwLabel_SetWidth(wwLabel *label, int width)
{
    wwWidget_SetWidth(&label->widget, width);
}
void wwLabel_SetHeight(wwLabel *label, int height)
{
    wwWidget_SetHeight(&label->widget, height);
}

wchar_t* wwLabel_GetText(wwLabel *label)
{
    return wwWidget_GetText(&label->widget);
}