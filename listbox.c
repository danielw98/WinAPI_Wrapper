#include "listbox.h"
#include "utils.h"
extern FILE *fp;
extern int g_wwListbox_isInit;
static void wwListbox_FreeFunc(void *data);
wwListbox* wwListbox_Create(wwWindowAndRenderer *windowAndRenderer, int x, int y, int width, int height)
{
    wwListbox *listbox = (wwListbox*) malloc(sizeof(wwListbox));
    if(windowAndRenderer->listboxes == NULL)
    {
        windowAndRenderer->listboxes = wwList_CreateEmpty(sizeof(wwListbox), TRUE, wwListbox_FreeFunc);
    }
    wwWidget_Create(&listbox->widget, NULL, x, y, width, height);
    listbox->numItems = 0;
    listbox->items = NULL;
    listbox->longest = 0;
    wwList_Append(windowAndRenderer->listboxes, listbox);
    return listbox;
}

void wwListbox_SetCallback(wwListbox *listbox, wwListboxCallback callback, void *userData)
{
    if(listbox == NULL)
        return;
    wwWidget_SetCallback((wwWidget*) listbox, (wwWidgetCallback) callback, userData);
}
// void wwListbox_SetText(wwListbox *listbox, wchar_t *text);
void wwListbox_SetX(wwListbox *listbox, int x)
{
    if(listbox == NULL)
        return;
    wwWidget_SetX(&listbox->widget, x);
}
void wwListbox_SetY(wwListbox *listbox, int y)
{
    if(listbox == NULL)
        return;
    wwWidget_SetY(&listbox->widget, y);
}
void wwListbox_SetWidth(wwListbox *listbox, int width)
{
    if(listbox == NULL)
        return;
    wwWidget_SetWidth(&listbox->widget, width);
}
void wwListbox_SetHeight(wwListbox *listbox, int height)
{
    if(listbox == NULL)
        return;
    wwWidget_SetHeight(&listbox->widget, height);
}

void wwListbox_AddString(wwListbox *listbox, wchar_t *text)
{
    if(listbox == NULL || text == NULL)
        return;
    listbox->numItems++;
    wchar_t **old_items = listbox->items;
    listbox->items = (wchar_t**) malloc (listbox->numItems * sizeof(wchar_t*));
    
    for(int i = 0; i < listbox->numItems-1; i++)
        listbox->items[i] = old_items[i];
    free(old_items);
    listbox->items[listbox->numItems-1] = (wchar_t*) malloc(wcslen(text)*sizeof(wchar_t) + sizeof(wchar_t));
    wcscpy(listbox->items[listbox->numItems-1], text);
    if(g_wwListbox_isInit == TRUE)
    {
        SendMessageW(listbox->widget.window, LB_ADDSTRING, 0, (LPARAM)listbox->items[listbox->numItems-1]);
        unsigned int currentLength = ww_CalcLBItemWidth(listbox->widget.window, listbox->items[listbox->numItems-1]);
        if(currentLength > listbox->longest){
            // element was added, is the new longest
            listbox->longest = currentLength;
            SendMessageW(listbox->widget.window, LB_SETHORIZONTALEXTENT, (WPARAM) listbox->longest, 0);
        }
    }
}

void wwListbox_SetCurrentSelectionText(wwListbox *listbox, wchar_t *text)
{
    if(listbox == NULL)
        return;
    int sel = (int) SendMessageW(listbox->widget.window, LB_GETCURSEL, 0, 0);
    if(sel == LB_ERR)
        return;
    SendMessageW(listbox->widget.window, LB_DELETESTRING, (WPARAM) sel, 0);
    unsigned int previousLength = wcslen(listbox->items[sel]);
    free(listbox->items[sel]);
    listbox->items[sel] = (wchar_t*) malloc((wcslen(text)+1) * sizeof(wchar_t));
    wcscpy(listbox->items[sel], text);
    SendMessageW(listbox->widget.window, LB_INSERTSTRING, (WPARAM) sel, (LPARAM) listbox->items[sel]);

    
    unsigned int currentLength = ww_CalcLBItemWidth(listbox->widget.window, listbox->items[sel]);
    if(currentLength > listbox->longest)
    {
        // element was changed, is the new longest
        listbox->longest = currentLength;
        SendMessageW(listbox->widget.window, LB_SETHORIZONTALEXTENT, (WPARAM) listbox->longest, 0);
    }
    
    else if(previousLength == listbox->longest)
    {   
        // element was changed, was the longest but now it isn't anymore, compute the new longest
        unsigned int longest = 0;
        for(int i = 0; i < listbox->numItems; i++){
            unsigned int currentLength = ww_CalcLBItemWidth(listbox->widget.window, listbox->items[i]);
            if(currentLength > longest)
                longest = currentLength;
        }
        listbox->longest = longest;
        SendMessageW(listbox->widget.window, LB_SETHORIZONTALEXTENT, (WPARAM) listbox->longest, 0);
    }
}

/* free this as it is a malloced pointer */
wchar_t* wwListbox_GetCurrentSelectionText(wwListbox *listbox)
{
    if(listbox == NULL)
        return NULL;
    int sel = (int) SendMessageW(listbox->widget.window, LB_GETCURSEL, 0, 0);
    if(sel == LB_ERR)
        return NULL;
    size_t textLength = (size_t) SendMessageW(listbox->widget.window, LB_GETTEXTLEN, (WPARAM) sel, 0);
    wchar_t *text = (wchar_t*) malloc((textLength+1) * sizeof(wchar_t));
    SendMessageW(listbox->widget.window, LB_GETTEXT, (WPARAM) sel, (LPARAM) text);
    return text;
}

int wwListbox_GetCurrentSelectionId(wwListbox *listbox)
{
    if(listbox == NULL)
        return -1;
    return (int) SendMessageW(listbox->widget.window, LB_GETCURSEL, 0, 0);
}
void wwListbox_DeleteCurrentSelection(wwListbox *listbox)
{
    if(listbox == NULL)
        return;
    int sel = (int) SendMessageW(listbox->widget.window, LB_GETCURSEL, 0, 0);
    if(sel == LB_ERR)
        return;
    SendMessageW(listbox->widget.window, LB_DELETESTRING, (WPARAM) sel, 0);
    free(listbox->items[sel]);

    for(int i = sel+1; i < listbox->numItems; i++)
        listbox->items[i-1] = listbox->items[i];
    listbox->numItems--;

    // element was deleted - make sure the width of the listbox is good
    unsigned int longest = 0;
    for(int i = 0; i < listbox->numItems; i++)
    {
        unsigned int currentLength = ww_CalcLBItemWidth(listbox->widget.window, listbox->items[i]);
        if(currentLength > longest)
            longest = currentLength;
    }
    if(longest < listbox->longest)
    {
        listbox->longest = longest;
        SendMessageW(listbox->widget.window, LB_SETHORIZONTALEXTENT, (WPARAM) listbox->longest, 0);
    }
}

void wwListbox_AddStringAtPosition(wwListbox *listbox, wchar_t *text, int position)
{
    if(listbox == NULL || text == NULL)
        return;
    if(position > listbox->numItems || position < 0)
        return;
    if(position == listbox->numItems){
        wwListbox_AddString(listbox, text);
        return;
    }
    listbox->numItems++;
    wchar_t **old_items = listbox->items;
    listbox->items = (wchar_t**) malloc (listbox->numItems * sizeof(wchar_t*));
    
    // until the position the items are unchanged
    for(int i = 0; i < position; i++)
        listbox->items[i] = old_items[i];
    // shift items one unit to the right 
    for(int i = position+1; i < listbox->numItems; i++)
        listbox->items[i] = old_items[i-1];
    free(old_items);
    // add string at the position
    listbox->items[position] = (wchar_t*) malloc(wcslen(text)*sizeof(wchar_t) + sizeof(wchar_t));
    wcscpy(listbox->items[position], text);
    if(g_wwListbox_isInit == TRUE)
        SendMessageW(listbox->widget.window, LB_INSERTSTRING, (WPARAM) position, (LPARAM)listbox->items[position]);

    unsigned int currentLength = ww_CalcLBItemWidth(listbox->widget.window, listbox->items[position]);
    if(currentLength > listbox->longest)
    {
        listbox->longest = currentLength;
        SendMessageW(listbox->widget.window, LB_SETHORIZONTALEXTENT, (WPARAM) listbox->longest, 0);
    }
}

static void wwListbox_FreeFunc(void *data)
{
    wwWidget_FreeFunc(data);
    wwListbox *listbox = (wwListbox*) data;
    for (int i = 0; i < listbox->numItems; i++)
        free(listbox->items[i]);
    free(listbox->items);
}