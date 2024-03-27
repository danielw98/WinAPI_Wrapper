#ifndef _TEXTBOX_H_
#define _TEXTBOX_H_
#include "widget.h"
typedef struct wwTextbox wwTextbox;
typedef void (*wwTextboxCallback)(wwTextbox *textBox, wwWindowAndRenderer*windowAndRenderer);
struct wwTextbox
{
    wwWidget widget;
};

wwTextbox* wwTextbox_Create(wwWindowAndRenderer *windowAndRenderer, wchar_t *name, int x, int y, int width, int height);
void wwTextbox_SetCallback(wwTextbox *textBox, wwTextboxCallback callback, void *userData);
void wwTextbox_SetText(wwTextbox *textBox, wchar_t *text);
void wwTextbox_SetX(wwTextbox *textBox, int x);
void wwTextbox_SetY(wwTextbox *textBox, int y);
void wwTextbox_SetWidth(wwTextbox *textBox, int width);
void wwTextbox_SetHeight(wwTextbox *textBox, int height);
/* returns malloc() pointer, should free() after usage */
wchar_t* wwTextbox_GetText(wwTextbox *textBox);
//void wwTextbox_SetColor(wwTextbox *textBox, wwColor color);
#endif /* _TEXTBOX_H_ */