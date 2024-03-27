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
    unsigned int longest;
};

wwListbox* wwListbox_Create(wwWindowAndRenderer *windowAndRenderer, int x, int y, int width, int height);
void wwListbox_SetCallback(wwListbox *listbox, wwListboxCallback callback, void *userData);
void wwListbox_SetX(wwListbox *listbox, int x);
void wwListbox_SetY(wwListbox *listbox, int y);
void wwListbox_SetWidth(wwListbox *listbox, int width);
void wwListbox_SetHeight(wwListbox *listbox, int height);
void wwListbox_AddString(wwListbox *listbox, wchar_t *text);
void wwListbox_SetCurrentSelectionText(wwListbox *listbox, wchar_t *text);
void wwListbox_DeleteCurrentSelection(wwListbox *listbox);
/* returns NULL when there is no selected item, otherwise returns a malloced string that the user should free */
wchar_t* wwListbox_GetCurrentSelectionText(wwListbox *listbox);
/* returns -1 when there is no selected item */
int wwListbox_GetCurrentSelectionId(wwListbox *listbox);
/* fails quietly when the position is < 0 or > numItems or if text is NULL; if position is numItems, it is equivalent to wwListbox_AddString */
void wwListbox_AddStringAtPosition(wwListbox *listbox, wchar_t *text, int position);
#endif /* _LISTBOX_H_ */