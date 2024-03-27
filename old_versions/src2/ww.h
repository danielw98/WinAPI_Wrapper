#ifndef _WW_H_
#define _WW_H_
#define UNICODE
#define _UNICODEs
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "wrstruct.h"
#include "list.h"
#include "button.h"
#include "window.h"
#include "label.h"
#include "checkbox.h"
FILE *fp;
wwWindowAndRenderer* wwWindowAndRenderer_Create(HINSTANCE hInstance, wchar_t *className, wchar_t *windowName, int x, int y, int width, int height);
int wwMainLoop(wwWindowAndRenderer *windowAndRenderer);
#endif /* _WW_H_ */