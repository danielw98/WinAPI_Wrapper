#ifndef _LISTBOX_H_
#define _LISTBOX_H_
#include "widget.h"
#include <wchar.h>

typedef struct wwListbox wwListbox;
typedef void (*wwListboxCallback)(wwListbox *listbox, wwWindowAndRenderer*windowAndRenderer);
struct wwListbox
{
    wwWidget widget;
    wchar_t **items;
    int numItems;
};

wwListbox* wwListbox_Create(wwWindowAndRenderer *windowAndRenderer, int x, int y, int width, int height);
void wwListbox_SetCallback(wwListbox *listbox, wwListboxCallback callback, void *userData);
void wwListbox_SetText(wwListbox *listbox, wchar_t *text);
void wwListbox_SetX(wwListbox *listbox, int x);
void wwListbox_SetY(wwListbox *listbox, int y);
void wwListbox_SetWidth(wwListbox *listbox, int width);
void wwListbox_SetHeight(wwListbox *listbox, int height);
void wwListbox_AddString(wwListbox *listbox, wchar_t *text);
/* returns malloc() pointer, should free() after usage */
// wchar_t* wwListbox_GetText(wwListbox *listbox);
#endif /* _LISTBOX_H_ */