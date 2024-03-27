#include "keyboard.h"

void ww_SetKeyboardCallback(wwWindowAndRenderer *win, wwKeyboardCallback callback, void *userData)
{
    win->keyboardCallback = callback;
    win->keyboardUserData = userData;
}