#ifndef _CHECKBOX_H_
#define _CHECKBOX_H_
#include "wrstruct.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct wwCheckbox wwCheckbox;
typedef void (*wwCheckboxCallback)(wwCheckbox *checkbox, wwWindowAndRenderer *windowAndRenderer);
struct wwCheckbox
{
    HWND window;
    wchar_t *text;
    int x;
    int y;
    int width;
    int height;
    int id;
    wwCheckboxCallback callback;
    void *userData;
};

wwCheckbox* wwCheckbox_Create(wwWindowAndRenderer *windowAndRenderer, wchar_t *text, int x, int y, int width, int height);
void wwCheckbox_SetCallback(wwCheckbox *checkBox, wwCheckboxCallback callback, void *userData);
int wwCheckbox_IsChecked(wwCheckbox *checkBox, wwWindowAndRenderer *windowAndRenderer);
void wwCheckbox_SetChecked(wwCheckbox *checkBox, wwWindowAndRenderer *windowAndRenderer, int checked);
#endif /* _CHECKBOX_H_ */