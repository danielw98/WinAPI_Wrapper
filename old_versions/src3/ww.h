#ifndef _WW_H_
#define _WW_H_
#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "wrstruct.h"
#include "widget.h"
#include "list.h"
#include "button.h"
#include "label.h"
#include "checkbox.h"
#include "textbox.h"
#include "listbox.h"
#include "window.h"
FILE *fp;
wwWindowAndRenderer* wwWindowAndRenderer_Create(HINSTANCE hInstance, wchar_t *className, wchar_t *windowName, int x, int y, int width, int height);
wwLabel* wwWindow_GetLabelById(wwWindowAndRenderer *windowAndRenderer, unsigned short id);
int wwMainLoop(wwWindowAndRenderer *windowAndRenderer);
#endif /* _WW_H_ */