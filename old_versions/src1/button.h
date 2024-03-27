#ifndef _BUTTON_H_
#define _BUTTON_H_
#include <windows.h>
#include <stdlib.h>
#include "wrstruct.h"
#include "ww.h"
typedef void (*wwButtonCallback)(void*);
typedef struct wwButton
{
    wchar_t *name;
    int x;
    int y;
    int width;
    int height;
    WORD id;
    wwButtonCallback callback;
    void *userData;
}wwButton;

wwButton* wwButton_Create(wwWindowAndRenderer *windowAndRenderer, wchar_t *name, int x, int y, int width, int height);
void wwButton_SetCallback(wwButton *button, wwButtonCallback callback, void *userData);

#endif /* _BUTTON_H_ */