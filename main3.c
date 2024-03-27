/*
    NEW IN THE LIBRARY:
    - user-written event loop instead of calling the library event loop
    this should give the user more control and allow him to structure the program better
    - keyboard and mouse callbacks
    - timer to measure elapsed time 

    TEST PROGRAM IDEA:
    - Update() 
        * change the color of the rectangle every second
    - Render() 
        * clears the screen and draws the rectangle every frame before displaying it 
     - MouseCallback() 
        * when a button is clicked, drag the rect to the position of the mouse
        * when a button is released, reset rect to default position
    - KeyboardCallback()
        * move rect UP/DOWN/LEFT/RIGHT
    - ButtonCallback()
        * resize rect

    NOTES:
    - widgets should be unaffected by the deletion of the screen by default (TODO: maybe 
    let the user delete/setvisible if he wants, something like wwWidget_DestroyOnClear(wwTrue), 
    or each widget should know if it should be destroyed/visible or not)
*/
#include "ww.h"
#include <stdbool.h>


extern FILE *fp; // used for debugging purposes - learn how to printf() to console from WinAPI :D
FILE *fp1;
wwColor color; // could put this in a struct with the rect 
unsigned short buttonId; // could pass this as parameter as well
int counter = 0; // number of frames passed since starting the timer
const int FPS = 30;
const int frameDelay = 1000 / FPS;
void Update(wwWindowAndRenderer *win, void *userData)
{
    if(counter % FPS == 0)
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
        printf("Unknown mouse event\n");
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
            printf("Unknown key pressed %lc\n", (wchar_t) key);
            break;
        }
        break;
    }
    case WWKEYBOARD_KEYRELEASED:{
        switch(key){
        case WWKEY_W:
        case WWKEY_w:
            printf("ww released\n");
            rect->y -= 20;
            break;
        case WWKEY_S:
        case WWKEY_s:
            rect->y += 20;
            break;
        case WWKEY_D:
        case WWKEY_d:
            rect->x += 20;
            break;
        case WWKEY_A:
        case WWKEY_a:
            rect->x -= 20;
            break;
        default:
            printf("Unknown key released %x\n", key);
            break;
        }
        break;
    }
    default:
        printf("Unknown key event\n");
        break;
    }
}
void buttonCallback(wwButton *button, wwWindowAndRenderer *win)
{
    wwRect *rect = (wwRect*) button->widget.userData;
    wwButton_SetText(button, L"It works");
    rect->width  += 20;
    rect->height -= 20;
}
// TODO: create an init function for the library to abstract WinMain(params) and use the default main() entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    
    wwWindowAndRenderer *win = wwWindowAndRenderer_Create(hInstance, L"Buttons Window", 100, 100, 800, 600);
    wwButton *button = wwButton_Create(win, L"MyButton", 100, 100, 100, 50);
    wwRect rect = {.x = 100, .y = 200, .width = 200, .height = 400};
    
    ww_SetMouseCallback(win, MouseCallback, &rect);
    ww_SetKeyboardCallback(win, KeyboardCallback, &rect);
    
    buttonId = wwButton_GetId(button);
    wwButton_SetCallback(button, buttonCallback, &rect);

    // call the init function after setting up stuff but before executing the main loop
    wwWindowAndRenderer_Init(win);
    
    wwTimer timer;
    wwTimer_Init(&timer);
    while(ww_Running(win) == wwTrue)
    {
        wwTimer_Start(&timer);

        Render(win, &rect);
        ww_ProcessEvents(win);
        Update(win, NULL);

        int frameTime = wwTimer_End(&timer); // maybe wwTimer_Stop?
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