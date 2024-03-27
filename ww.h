#ifndef _WW_H_
#define _WW_H_
#define UNICODE
#define _UNICODE
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <stdio.h>
#include "wrstruct.h"
#include "timer.h"
#include "widget.h"
#include "list.h"
#include "button.h"
#include "label.h"
#include "checkbox.h"
#include "textbox.h"
#include "listbox.h"
#include "window.h"
#include "renderer.h"
#include "wwRect.h"
#include "menu.h"
#include "keyboard.h"
#include "mouse.h"
FILE *fp;
wwWindowAndRenderer* wwWindowAndRenderer_Create(HINSTANCE hInstance, wchar_t *windowName, int x, int y, int width, int height);
wwWidget* wwWindow_GetWidgetById(wwList *list, unsigned short id);
wwButton* wwWindow_GetButtonById(wwWindowAndRenderer *windowAndRenderer, unsigned short id);
wwLabel* wwWindow_GetLabelById(wwWindowAndRenderer *windowAndRenderer, unsigned short id);
wwCheckbox* wwWindow_GetCheckboxById(wwWindowAndRenderer *windowAndRenderer, unsigned short id);
wwTextbox* wwWindow_GetTextboxById(wwWindowAndRenderer *windowAndRenderer, unsigned short id);
wwListbox* wwWindow_GetListboxById(wwWindowAndRenderer *windowAndRenderer, unsigned short id);
void wwWindowAndRenderer_Destroy(wwWindowAndRenderer *windowAndRenderer);
/* call this after setting up the widgets */
void wwWindowAndRenderer_Init(wwWindowAndRenderer *windowAndRenderer);
/* should I keep this for backwards compatibilty or just change the old main files? 
probably change the old main files */
int wwMainLoop(wwWindowAndRenderer *windowAndRenderer);
void ww_GetMouseState(int *mouseX, int *mouseY);
/* wrapper function over the Windows Message loop system that allows control back to the user after return 
instead of forcing a ww_RunProgram() or similar function call, which gives the user less flexibility */
void ww_ProcessEvents(wwWindowAndRenderer *windowAndRenderer);
wwBool ww_Running(wwWindowAndRenderer *windowAndRenderer);
/* get the current time in milliseconds - it only makes sense when called in succession to see the delta time */
int ww_GetTime(void);
/* delay the CPU for delay milliseconds */
void ww_Delay(int delay);
#endif /* _WW_H_ */