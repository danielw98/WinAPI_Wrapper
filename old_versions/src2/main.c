#include "ww.h"

/*
    TODO:
- create a generic Widget struct
- create a generic callback function
*/

void buttonCallback(wwButton *button, wwWindowAndRenderer *win)
{
    wchar_t *data = button->userData;
    wwWindow_SetTitle(win, data);
    wwButton_SetText(button, data);
    wwButton_SetX(button, button->x+5);
}

void labelCallback(wwLabel *label, wwWindowAndRenderer *win)
{
    wchar_t *data = label->userData;
    wwWindow_SetTitle(win, data);
    wwLabel_SetText(label, data);
    wwLabel_SetX(label, label->x+5);
}

void checkboxCallback(wwCheckbox *checkbox, wwWindowAndRenderer *win)
{
    wchar_t *data = checkbox->userData;
    if(wwCheckbox_IsChecked(checkbox, win))
    {
        wwWindow_SetTitle(win, L"Unchecked");
        wwCheckbox_SetChecked(checkbox, win, 0);
    }
    else
    {
        wwWindow_SetTitle(win, data);
        wwCheckbox_SetChecked(checkbox, win, 1);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    
    wwWindowAndRenderer *win = wwWindowAndRenderer_Create(hInstance, L"Buttons", L"Buttons Window", 100, 100, 800, 600);

    wwButton *button1 = wwButton_Create(win, L"ClickMe1",  20, 50, 80, 25);
    wwButton *button2 = wwButton_Create(win, L"ClickMe2", 120, 50, 80, 25);
    wchar_t strBtn1[16] = L"Button1";
    wchar_t strBtn2[16] = L"Button2";
    wwButton_SetCallback(button1, buttonCallback, strBtn1);
    wwButton_SetCallback(button2, buttonCallback, strBtn2);
 
    wwLabel *label1 = wwLabel_Create(win, L"label1",  20, 100, 80, 25);
    wwLabel *label2 = wwLabel_Create(win, L"label2", 120, 100, 80, 25);
    wchar_t strLbl1[16] = L"Label1";
    wchar_t strLbl2[16] = L"Label2";
    wwLabel_SetCallback(label1, labelCallback, strLbl1);
    wwLabel_SetCallback(label2, labelCallback, strLbl2);

    wwCheckbox *checkbox1 = wwCheckbox_Create(win, L"checkbox1",  20, 150, 80, 25);
    wwCheckbox *checkbox2 = wwCheckbox_Create(win, L"checkbox2", 120, 150, 80, 25);
    wchar_t strChb1[16] = L"CheckBox1";
    wchar_t strChb2[16] = L"CheckBox2";
    wwCheckbox_SetCallback(checkbox1, checkboxCallback, strChb1);
    wwCheckbox_SetCallback(checkbox2, checkboxCallback, strChb2);
    return wwMainLoop(win);
}