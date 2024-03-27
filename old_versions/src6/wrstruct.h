#ifndef _WRSTRUCT_H_
#define _WRSTRUCT_H_
#include <windows.h>
#include <stdint.h>
#include "list.h"

typedef int wwBool;
#define wwFalse 0
#define wwTrue  1

typedef struct wwWindowAndRenderer wwWindowAndRenderer;

typedef enum wwKeyboardEvent
{
    WWKEYBOARD_NONE = -1,
    WWKEYBOARD_KEYPRESSED  = WM_KEYDOWN,
    WWKEYBOARD_KEYRELEASED = WM_KEYUP
}wwKeyboardEvent;

typedef enum wwKey
{
    WWKEY_NONE = -1,
    WWKEY_A = 'A',
    WWKEY_B, WWKEY_C, WWKEY_D, WWKEY_E,
    WWKEY_F, WWKEY_G, WWKEY_H, WWKEY_I,
    WWKEY_J, WWKEY_K, WWKEY_L, WWKEY_M,
    WWKEY_N, WWKEY_O, WWKEY_P, WWKEY_Q,
    WWKEY_R, WWKEY_S, WWKEY_T, WWKEY_U,
    WWKEY_V, WWKEY_W, WWKEY_X, WWKEY_Y,
    WWKEY_Z,
    WWKEY_a = 'a',
    WWKEY_b, WWKEY_c, WWKEY_d, WWKEY_e,
    WWKEY_f, WWKEY_g, WWKEY_h, WWKEY_i,
    WWKEY_j, WWKEY_k, WWKEY_l, WWKEY_m,
    WWKEY_n, WWKEY_o, WWKEY_p, WWKEY_q,
    WWKEY_r, WWKEY_s, WWKEY_t, WWKEY_u,
    WWKEY_v, WWKEY_w, WWKEY_x, WWKEY_y,
    WWKEY_z,
    WWKEY_0 = '0',
    WWKEY_1, WWKEY_2, WWKEY_3,
    WWKEY_4, WWKEY_5, WWKEY_6,
    WWKEY_7, WWKEY_8, WWKEY_9,
    WWKEY_UPARROW    = VK_UP,
    WWKEY_DOWNARROW  = VK_DOWN,
    WWKEY_LEFTARROW  = VK_LEFT,
    WWKEY_RIGHTARROW = VK_RIGHT,
    WWKEY_PLUS,
    WWKEY_MINUS
}wwKey;
typedef void (*wwKeyboardCallback)(wwWindowAndRenderer *win, wwKey key, wwKeyboardEvent event, void *userData);

typedef enum wwMouseEvent
{
    WWMOUSE_NONE = -1,
    WWMOUSE_LBUTTON_PRESSED  = WM_LBUTTONDOWN,
    WWMOUSE_LBUTTON_RELEASED = WM_LBUTTONUP,
    WWMOUSE_RBUTTON_PRESSED  = WM_RBUTTONDOWN,
    WWMOUSE_RBUTTON_RELEASED = WM_RBUTTONUP,
    WWMOUSE_SCROLL_PRESSED   = WM_MBUTTONDOWN,
    WWMOUSE_SCROLL_RELEASED  = WM_MBUTTONUP,
    WWMOUSE_SCROLL_UP,
    WWMOUSE_SCROLL_DOWN
} wwMouseEvent;
typedef void (*wwMouseCallback)(wwWindowAndRenderer *win, int x, int y, wwMouseEvent event, void *userData);



#include "keyboard.h"
#include "mouse.h"

typedef struct wwPixel
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
}wwPixel;

typedef struct wwRenderer
{
    int width;
    int height;
    wwPixel **pixels;
}wwRenderer;

typedef struct wwTexture
{
    int width;
    int height;
    wwPixel **pixels;
}wwTexture;

struct wwWindowAndRenderer
{
    // Windows specific
    MSG msg;
    WNDCLASSW wc;
    HWND hwnd;
    HDC hdc;
    PAINTSTRUCT ps; 
    // Window info
    wchar_t *windowName;
    int x;
    int y;
    int width;
    int height;
    // Program status
    wwBool running;
    // The canvas to which it is drawn
    wwRenderer *renderer;
    // Widgets
    wwList *buttons;
    wwList *labels;
    wwList *checkboxes;
    wwList *textboxes;
    wwList *listboxes;
    wwList *rectangles;
    wwList *menus;
    // Callbacks
    wwMouseCallback mouseCallback;
    wwKeyboardCallback keyboardCallback;
    // Events
    wwMouseEvent mouseEvent;
    wwKeyboardEvent keyboardEvent;
    // User Data
    void *mouseUserData;
    void *keyboardUserData;
    // misc
    wwKey key;
};
#endif /* _WRSTRUCT_H_ */