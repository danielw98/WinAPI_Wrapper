#ifndef _CHECKBOX_H_
#define _CHECKBOX_H_
#include "widget.h"

typedef struct wwCheckbox wwCheckbox;
typedef void (*wwCheckboxCallback)(wwCheckbox *checkbox, wwWindowAndRenderer *windowAndRenderer);
struct wwCheckbox
{
    wwWidget widget;
};

wwCheckbox* wwCheckbox_Create(wwWindowAndRenderer *windowAndRenderer, wchar_t *text, int x, int y, int width, int height);
void wwCheckbox_SetCallback(wwCheckbox *checkBox, wwCheckboxCallback callback, void *userData);
int wwCheckbox_IsChecked(wwCheckbox *checkBox, wwWindowAndRenderer *windowAndRenderer);
void wwCheckbox_SetChecked(wwCheckbox *checkBox, wwWindowAndRenderer *windowAndRenderer, int checked);
void wwCheckbox_SetText(wwCheckbox *checkbox, wchar_t *text);
void wwCheckbox_SetX(wwCheckbox *checkbox, int x);
void wwCheckbox_SetY(wwCheckbox *checkbox, int y);
void wwCheckbox_SetWidth(wwCheckbox *checkbox, int width);
void wwCheckbox_SetHeight(wwCheckbox *checkbox, int height);
/* returns malloc() pointer, should free() after usage */
wchar_t* wwCheckbox_GetText(wwCheckbox *checkbox);
#endif /* _CHECKBOX_H_ */