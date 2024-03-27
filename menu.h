#ifndef _MENU_H_
#define _MENU_H_
#include "wrstruct.h"
#include <windows.h>
#include <stdio.h>

typedef enum wwMenuType
{
    WWMENU_STRING = MF_STRING,
    WWMENU_SUBMENU = MF_POPUP,
    WWMENU_SEPARATOR = MF_SEPARATOR,
    WWMENU_MAIN
}wwMenuType;
typedef struct wwMenu wwMenu;
typedef void (*wwMenuCallback)(wwMenu *menu, wwWindowAndRenderer *wwWindowAndRenderer);
struct wwMenu
{
    wchar_t *text;
    wwMenuCallback callback;
    void *userData;
    wwMenuType type;
    HMENU hMenu;
    int id;
};

wwMenu* wwMenu_CreateMainMenu(wwWindowAndRenderer *windowAndRenderer);
wwMenu* wwMenu_AppendMenu(wwWindowAndRenderer *windowAndRenderer, wwMenu *menu, wchar_t *text, wwMenuType type);
wwMenu* wwMenu_CreateSubMenu(wwWindowAndRenderer *windowAndRenderer, wwMenu *menu, wchar_t *text);
wwMenu* wwMenu_GetMainMenu(wwWindowAndRenderer *windowAndRenderer);
void wwMenu_SetCallback(wwMenu *menu, wwMenuCallback callback, void *userData);
// add shortcut keys
#endif /* _MENU_H_ */