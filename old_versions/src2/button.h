#ifndef _BUTTON_H_
#define _BUTTON_H_
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "wrstruct.h"
typedef struct wwButton wwButton;
typedef void (*wwButtonCallback)(wwButton *button, wwWindowAndRenderer*windowAndRenderer);
struct wwButton
{
    HWND window;
    wchar_t *name;
    int x;
    int y;
    int width;
    int height;
    int id;
    wwButtonCallback callback;
    void *userData;
};

wwButton* wwButton_Create(wwWindowAndRenderer *windowAndRenderer, wchar_t *name, int x, int y, int width, int height);
void wwButton_SetCallback(wwButton *button, wwButtonCallback callback, void *userData);
void wwButton_SetText(wwButton *button, wchar_t *text);
void wwButton_SetX(wwButton *button, int x);
void wwButton_SetY(wwButton *button, int y);
void wwButton_SetWidth(wwButton *button, int width);
void wwButton_SetHeight(wwButton *button, int height);
#endif /* _BUTTON_H_ */