#include "mouse.h"
void ww_SetMouseCallback(wwWindowAndRenderer *win, wwMouseCallback callback, void *userData)
{
    win->mouseCallback = callback;
    win->mouseUserData = userData;
}