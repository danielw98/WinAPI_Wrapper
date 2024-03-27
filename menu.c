#include "menu.h"

extern FILE *fp;
/* Create the Main Menu to which Menus or SubMenus are appended */

static wwMenu* wwMenu_CreateMenu(wchar_t *text, wwMenuType type)
{
    static int id = 0;
    size_t size;
    wwMenu *menu = (wwMenu*) malloc(sizeof(wwMenu));
    menu->hMenu = CreateMenu();
    if(text != NULL){
        size = wcslen(text) + 1;
        menu->text = (wchar_t*) malloc(size * sizeof(wchar_t));
        memcpy(menu->text, text, size * sizeof(wchar_t));
    }
    else
        menu->text = NULL;
    menu->type = type;
    menu->id = id++;
    menu->callback = NULL;
    menu->userData = NULL;
    return menu;
}

static void wwMenu_FreeFunc(void *data)
{
    wwMenu *menu = (wwMenu*) data;
    free(menu->text);
}
/* Call this function only once for a handle to the Main Menu, otherwise it returns NULL */
wwMenu* wwMenu_CreateMainMenu(wwWindowAndRenderer *windowAndRenderer)
{
    static int numCalls = 0;
    if(numCalls != 0)
        return NULL;
    wwMenu *menu = wwMenu_CreateMenu(NULL, WWMENU_MAIN);
    if(windowAndRenderer->menus == NULL)
    {
        windowAndRenderer->menus = wwList_CreateEmpty(sizeof(wwMenu), TRUE, wwMenu_FreeFunc);
        fprintf(fp, "created menus list %p\n", windowAndRenderer->menus);
    }
    fprintf(fp, "creating menu %p\n", menu);
    numCalls++;
    fprintf(fp, "%s %d\n", __FILE__, __LINE__);
    wwList_Append(windowAndRenderer->menus, menu);
    fprintf(fp, "%s %d\n", __FILE__, __LINE__);
    return menu;
}

/* Append an item to the menu or submenu - cannot be WWMENU_MAIN or WWMENU_SUBMENU -
use the proper functions for them */
wwMenu* wwMenu_AppendMenu(wwWindowAndRenderer *windowAndRenderer, wwMenu *menu, wchar_t *text, wwMenuType type)
{
    fprintf(fp, "%s %d\n", __FILE__, __LINE__);
    if(menu == NULL || type == WWMENU_MAIN || type == WWMENU_SUBMENU)
        return NULL;
    wwMenu *menuItem = wwMenu_CreateMenu(text, type);
    fprintf(fp, "%s %d\n", __FILE__, __LINE__);
    AppendMenuW(menu->hMenu, menuItem->type, (UINT_PTR)((unsigned long long) menuItem->id), menuItem->text);
    fprintf(fp, "%s %d\n", __FILE__, __LINE__);
    wwList_Append(windowAndRenderer->menus, menuItem);
    return menuItem;
}
wwMenu* wwMenu_CreateSubMenu(wwWindowAndRenderer *windowAndRenderer, wwMenu *menu, wchar_t *text)
{
    if(menu == NULL)
        return NULL;
    wwMenu *subMenu = wwMenu_CreateMenu(text, WWMENU_SUBMENU);
    AppendMenuW(menu->hMenu, WWMENU_SUBMENU, (UINT_PTR) subMenu->hMenu, text);
    wwList_Append(windowAndRenderer->menus, subMenu);
    return subMenu;
}

void wwMenu_SetCallback(wwMenu *menu, wwMenuCallback callback, void *userData)
{
    menu->callback = callback;
    menu->userData = userData;
}

wwMenu* wwMenu_GetMainMenu(wwWindowAndRenderer *windowAndRenderer)
{
    if(windowAndRenderer == NULL)
        return NULL;
    wwList *menus = windowAndRenderer->menus;
    if(menus == NULL)
        return NULL;
    
    Node *head = menus->head;
    while(head != NULL){
        wwMenu *menu = (wwMenu*) head->data;
        if(menu->type == WWMENU_MAIN)
            return menu;
        head = head->next;
    }
    return NULL;
}