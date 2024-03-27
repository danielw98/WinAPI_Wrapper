#ifndef _LABEL_H_
#define _LABEL_H_
#include "widget.h"
typedef struct wwLabel wwLabel;
typedef void (*wwLabelCallback)(wwLabel *label, wwWindowAndRenderer *windowAndRenderer);
struct wwLabel
{
    wwWidget widget;
};

wwLabel* wwLabel_Create(wwWindowAndRenderer *windowAndRenderer, wchar_t *labelText, int x, int y, int width, int height);
void wwLabel_SetCallback(wwLabel *label, wwLabelCallback callback, void *userData);
void wwLabel_SetText(wwLabel *label, wchar_t *text);
void wwLabel_SetX(wwLabel *label, int x);
void wwLabel_SetY(wwLabel *label, int y);
void wwLabel_SetWidth(wwLabel *label, int width);
void wwLabel_SetHeight(wwLabel *label, int height);
/* returns malloc() pointer, should free() after usage */
wchar_t* wwLabel_GetText(wwLabel *label);
#endif /* _LABEL_H_ */