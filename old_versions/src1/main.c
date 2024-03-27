#include "ww.h"

void buttonCallback(void *userData)
{

}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    fp = fopen("error.txt", "w");
    wwWindowAndRenderer *win = wwWindowAndRenderer_Create(hInstance, L"Buttons", L"Buttons Window", 100, 100, 800, 600);
    fprintf(fp, "creating the buttons\n");
    wwButton *button1 = wwButton_Create(win, L"ClickMe1",  20, 50, 80, 25);
    wwButton *button2 = wwButton_Create(win, L"ClickMe2", 120, 50, 80, 25);
    fprintf(fp, "setting the callbacks\n");
    wwButton_SetCallback(button1, buttonCallback, NULL);
    wwButton_SetCallback(button2, buttonCallback, NULL);
    fprintf(fp, "starting main loop\n");
    int retCode = wwMainLoop(win);
    fclose(fp);
    return retCode;
}