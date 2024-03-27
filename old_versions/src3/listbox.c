#include "listbox.h"
extern FILE *fp;
wwListbox* wwListbox_Create(wwWindowAndRenderer *windowAndRenderer, int x, int y, int width, int height)
{
    wwListbox *listbox = (wwListbox*) malloc(sizeof(wwListbox));
    if(windowAndRenderer->listboxes == NULL)
    {
        windowAndRenderer->listboxes = wwList_CreateEmpty(sizeof(wwListbox), TRUE);
        fprintf(fp, "created listbox list %p\n", windowAndRenderer->listboxes);
    }
    fprintf(fp, "creating listbox %p\n", listbox);
    wwWidget_Create(&listbox->widget, NULL, x, y, width, height);
    listbox->numItems = 0;
    listbox->items = NULL;
    wwList_Append(windowAndRenderer->listboxes, listbox);
    return listbox;
}

void wwListbox_SetCallback(wwListbox *listbox, wwListboxCallback callback, void *userData)
{
    wwWidget_SetCallback((wwWidget*) listbox, (wwWidgetCallback) callback, userData);
}
// void wwListbox_SetText(wwListbox *listbox, wchar_t *text);
void wwListbox_SetX(wwListbox *listbox, int x)
{
    wwWidget_SetX(&listbox->widget, x);
}
void wwListbox_SetY(wwListbox *listbox, int y)
{
    wwWidget_SetY(&listbox->widget, y);
}
void wwListbox_SetWidth(wwListbox *listbox, int width)
{
    wwWidget_SetWidth(&listbox->widget, width);
}
void wwListbox_SetHeight(wwListbox *listbox, int height)
{
    wwWidget_SetHeight(&listbox->widget, height);
}

void wwListbox_AddString(wwListbox *listbox, wchar_t *text)
{
    listbox->numItems++;
    wchar_t **old_items = listbox->items;
    listbox->items = (wchar_t**) malloc (listbox->numItems * sizeof(wchar_t*));
    
    for(int i = 0; i < listbox->numItems-1; i++)
        listbox->items[i] = old_items[i];
    listbox->items[listbox->numItems-1] = (wchar_t*) malloc(wcslen(text)*sizeof(wchar_t) + sizeof(wchar_t));
    wcscpy(listbox->items[listbox->numItems-1], text);
    if(old_items != NULL)
        free(old_items);
}