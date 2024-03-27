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
    label->x = x;
    label->y = y;
    label->width = width;
    label->height = height;
    label->text = labelText;
    wwList_Append(windowAndRenderer->labels, label);
    return label;
}

void wwLabel_SetCallback(wwLabel *label, wwLabelCallback callback, void *userData)
{
    label->callback = callback;
    label->userData = userData;
}

void wwLabel_SetText(wwLabel *label, wchar_t *text)
{
    label->text = text;
    SetWindowTextW(label->window, label->text);
}

void wwLabel_SetX(wwLabel *label, int x)
{
    label->x = x;
    SetWindowPos(label->window, 0, label->x, label->y, label->width, label->height, SWP_NOZORDER | SWP_SHOWWINDOW);
}
void wwLabel_SetY(wwLabel *label, int y)
{
    label->y = y;
    SetWindowPos(label->window, 0, label->x, label->y, label->width, label->height, SWP_NOZORDER | SWP_SHOWWINDOW);
}
void wwLabel_SetWidth(wwLabel *label, int width)
{
    label->width = width;
    SetWindowPos(label->window, 0, label->x, label->y, label->width, label->height, SWP_NOZORDER | SWP_SHOWWINDOW);
}
void wwLabel_SetHeight(wwLabel *label, int height)
{
    label->height = height;
    SetWindowPos(label->window, 0, label->x, label->y, label->width, label->height, SWP_NOZORDER | SWP_SHOWWINDOW);
}