#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "wrstruct.h"
#include "wwrect.h"
#include <windows.h>

wwRect* wwRenderer_GetRectangleById(wwWindowAndRenderer *win, unsigned short id);
void wwRenderer_CreateRectangle(wwWindowAndRenderer *win, wwRect *rect);
void wwRenderer_DrawRectangle(wwWindowAndRenderer *win, wwRect *rect);
void wwRenderer_DisplayRectangle(wwWindowAndRenderer *win, wwRect *rect);
void wwRect_SetVisible(wwWindowAndRenderer *win, wwRect *rect, int visible);
int wwRect_GetVisible(wwRect *rect);
#endif /* _RENDERER_H_ */