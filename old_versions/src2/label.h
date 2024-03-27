#ifndef _LABEL_H_
#define _LABEL_H_
#include "wrstruct.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
typedef struct wwLabel wwLabel;
typedef void (*wwLabelCallback)(wwLabel *label, wwWindowAndRenderer *windowAndRenderer);
struct wwLabel
{
    HWND window;
    wchar_t *text;
    int x;
    int y;
    int width;
    int height;
    int id;
    wwLabelCallback callback;
    void *userData;
};

wwLabel* wwLabel_Create(wwWindowAndRenderer *windowAndRenderer, wchar_t *labelText, int x, int y, int width, int height);
void wwLabel_SetCallback(wwLabel *label, wwLabelCallback callback, void *userData);
void wwLabel_SetText(wwLabel *label, wchar_t *text);
void wwLabel_SetX(wwLabel *label, int x);
void wwLabel_SetY(wwLabel *label, int y);
void wwLabel_SetWidth(wwLabel *label, int width);
void wwLabel_SetHeight(wwLabel *label, int height);
#endif /* _LABEL_H_ */