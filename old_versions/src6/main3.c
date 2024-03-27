#include "ww.h"
#include <stdbool.h>

extern FILE *fp;

wwColor color; // could put this in a struct with the rect 
const int FPS = 30;
const int frameDelay = 1000 / FPS;

void Update(wwWindowAndRenderer *win, void *userData)
{
    static int numCalls = 0;
    numCalls++;
    if(numCalls % FPS == 0)
    {
        color.red   = rand() % 256;
        color.green = rand() % 256;
        color.blue  = rand() % 256; 
        color.alpha = 255;
    }
}
void Render(wwWindowAndRenderer *win, void *userData)
{
    wwRenderer_Clear(win);
    wwRenderer_DrawRectangle(win, (wwRect*) userData, color);
    wwRenderer_Display(win);
}

void MouseCallback(wwWindowAndRenderer *win, int x, int y, wwMouseEvent event, void *userData)
{
    wwRect *rect = (wwRect*) userData;
    switch(event)
    {
    case WWMOUSE_LBUTTON_PRESSED:
    case WWMOUSE_RBUTTON_PRESSED:
        rect->x = x;
        rect->y = y;
        break;
    case WWMOUSE_LBUTTON_RELEASED:
    case WWMOUSE_RBUTTON_RELEASED:
        rect->x = 200;
        rect->y = 100;
        break;
    default:
        fprintf(fp, "Unknown mouse event\n");
        break;
    }
}

void KeyboardCallback(wwWindowAndRenderer *win, wwKey key, wwKeyboardEvent event, void *userData)
{
    wwRect *rect = (wwRect*) userData;
    switch(event){
    case WWKEYBOARD_KEYPRESSED:{
        switch(key){
        case WWKEY_DOWNARROW:
            rect->y += 20;
            break;
        case WWKEY_UPARROW:
            rect->y -= 20;
            break;
        case WWKEY_LEFTARROW:
            rect->x -= 20;
            break;
        case WWKEY_RIGHTARROW:
            rect->x += 20;
            break;
        default:
            fprintf(fp, "Unknwon key pressed %lc\n", (wchar_t) key);
            break;
        }
        break;
    }
    case WWKEYBOARD_KEYRELEASED:{
        switch(key){
        case WWKEY_DOWNARROW:
            rect->y -= 20;
            break;
        case WWKEY_UPARROW:
            rect->y += 20;
            break;
        case WWKEY_LEFTARROW:
            rect->x += 20;
            break;
        case WWKEY_RIGHTARROW:
            rect->x -= 20;
            break;
        default:
            fprintf(fp, "Unknwon key released %x\n", key);
            break;
        }
        break;
    }
    default:
        fprintf(fp, "Unknown key event\n");
        break;
    }
}
void buttonCallback(wwButton *button, wwWindowAndRenderer *win)
{
    wwRect *rect = (wwRect*) button->widget.userData;
    rect->width  += 20;
    rect->height -= 20;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    wwWindowAndRenderer *win = wwWindowAndRenderer_Create(hInstance, L"Buttons Window", 100, 100, 800, 600);
    wwRect rect = {.x = 100, .y = 200, .width = 200, .height = 400};
    ww_SetMouseCallback(win, MouseCallback, &rect);
    ww_SetKeyboardCallback(win, KeyboardCallback, &rect);
    wwTimer timer;
    wwTimer_Init(&timer);
    int counter = 0;
    wwButton *button = wwButton_Create(win, L"MyButton", 100, 100, 100, 50);
    wwButton_SetCallback(button, buttonCallback, NULL);
    while(ww_Running(win) == wwTrue)
    {
        wwTimer_Start(&timer);
        Render(win, &rect);
        ww_ProcessEvents(win);
        Update(win, NULL);
        int frameTime = wwTimer_End(&timer);
        if(frameTime < frameDelay)
            wwTimer_Delay(frameDelay - frameTime);
        counter++;
    }
    wwWindowAndRenderer_Destroy(win);
    return 0;
}


// left mouse click - move left
// left mouse release - change shape
// right mouse click - move right
// right mouse release - change shape
// scroll up - move up
// scroll down - move down
// scroll click - change color
// scroll release - change back color


// try keys 0, -, +, A, a, SPACE, ARROWS