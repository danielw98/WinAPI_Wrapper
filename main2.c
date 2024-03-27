#include "ww.h"

/*
TODO:
- create a generic Widget struct
- create a generic callback function
- create an enum of all widgets and pass it as a parameter to the callback
so there can be only 1 callback for all the widgets - actually I can figure
this out from the magic bytes of the widget, but the enum still would be 
nice to exist for some reason yet unknown.
*/

typedef struct UserData
{
    wchar_t str[16];
    int num;
}UserData;
void buttonCallback(wwButton *button, wwWindowAndRenderer *win)
{
    fprintf(fp, "button callback\n");
    UserData *data = (UserData*) button->widget.userData;
    wwWindow_SetTitle(win, data->str);
    wwButton_SetText(button, data->str);
    wwButton_SetX(button, button->widget.x+5);
}

void labelCallback(wwLabel *label, wwWindowAndRenderer *win)
{
    fprintf(fp, "label callback\n");
    UserData *data = (UserData*) label->widget.userData;
    wwWindow_SetTitle(win, data->str);
    wwLabel_SetText(label, data->str);
    wwLabel_SetX(label, label->widget.x+5);
}

void checkboxCallback(wwCheckbox *checkbox, wwWindowAndRenderer *win)
{
    printf("checkboxCallback\n");
    UserData *data = (UserData*) checkbox->widget.userData;
    if(wwCheckbox_IsChecked(checkbox, win))
    {
        wwWindow_SetTitle(win, L"Unchecked");
        wwCheckbox_SetChecked(checkbox, win, 0);
        wwCheckbox_SetX(checkbox, checkbox->widget.x+5);
        wwCheckbox_SetText(checkbox, L"Unclicked");
    }
    else
    {
        wwWindow_SetTitle(win, data->str);
        wwCheckbox_SetChecked(checkbox, win, 1);
        wwCheckbox_SetX(checkbox, checkbox->widget.x-5);
        wwCheckbox_SetText(checkbox, L"Clicked");
    }
}

void textboxCallback(wwTextbox *textbox, wwWindowAndRenderer *win)
{
    printf("textbox callback\n");
    UserData *data = (UserData*) textbox->widget.userData;
    wwWindow_SetTitle(win, data->str);
    //wwTextbox_SetText(textbox, data); // FIXME: broken function
    wwTextbox_SetX(textbox, textbox->widget.x + 5);
}

void listboxCallback(wwListbox *listbox, wwWindowAndRenderer *win)
{
    printf("listbox callback\n");
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    wwWindowAndRenderer *win = wwWindowAndRenderer_Create(hInstance, L"Buttons Window", 100, 100, 800, 600);

    wwButton *button1 = wwButton_Create(win, L"ClickMe1",  20, 50, 80, 25);
    wwButton *button2 = wwButton_Create(win, L"ClickMe2", 120, 50, 80, 25);
    UserData buttonData1 = {.str = L"Button1", .num = 1};
    UserData buttonData2 = {.str = L"Button2", .num = 2};
    wwButton_SetCallback(button1, buttonCallback, &buttonData1);
    wwButton_SetCallback(button2, buttonCallback, &buttonData2);
 
    wwLabel *label1 = wwLabel_Create(win, L"label1",  20, 100, 80, 25);
    wwLabel *label2 = wwLabel_Create(win, L"label2", 120, 100, 80, 25);
    UserData labelData1 = {.str = L"Label1", .num = 1};
    UserData labelData2 = {.str = L"Label2", .num = 2};
    wwLabel_SetCallback(label1, labelCallback, &labelData1);
    wwLabel_SetCallback(label2, labelCallback, &labelData2);

    wwCheckbox *checkbox1 = wwCheckbox_Create(win, L"checkbox1",  20, 150, 80, 25);
    wwCheckbox *checkbox2 = wwCheckbox_Create(win, L"checkbox2", 120, 150, 80, 25);
    UserData checkboxData1 = {.str = L"CheckBox1", .num = 1};
    UserData checkboxData2 = {.str = L"CheckBox2", .num = 2};
    wwCheckbox_SetCallback(checkbox1, checkboxCallback, &checkboxData1);
    wwCheckbox_SetCallback(checkbox2, checkboxCallback, &checkboxData2);

    wwTextbox *textbox1 = wwTextbox_Create(win, L"textbox1",  20, 200, 80, 25);
    wwTextbox *textbox2 = wwTextbox_Create(win, L"textbox2", 120, 200, 80, 25);
    UserData textboxData1 = {.str = L"TextBox1", .num = 1};
    UserData textboxData2 = {.str = L"TextBox2", .num = 2};
    wchar_t strTxb1[16] = L"TextBox1";
    wchar_t strTxb2[16] = L"TextBox2";
    wwTextbox_SetCallback(textbox1, textboxCallback, &textboxData1);
    wwTextbox_SetCallback(textbox2, textboxCallback, &textboxData2);

    wwListbox *listbox1 = wwListbox_Create(win,  20, 250, 150, 100);
    wwListbox *listbox2 = wwListbox_Create(win, 190, 250, 150, 100);
    wwListbox_AddString(listbox1, L"ListBox1Text1");
    wwListbox_AddString(listbox1, L"ListBox1Text2");
    wwListbox_AddString(listbox2, L"ListBox2Text1");
    wwListbox_AddString(listbox2, L"ListBox2Text2");
    wwListbox_SetCallback(listbox1, listboxCallback, NULL);
    wwListbox_SetCallback(listbox2, listboxCallback, NULL);
    
    // call the init function after setting up stuff but before executing the main loop
    wwWindowAndRenderer_Init(win);

    wwTimer timer;
    const int FPS = 30;
    const int frameDelay = 1000 / FPS;
    wwTimer_Init(&timer);
    while(ww_Running(win) == wwTrue)
    {
        // Render(win, NULL);
        wwTimer_Start(&timer);
        ww_ProcessEvents(win); // call this every frame - should the library call it ?
        // Update(win, NULL);
        int frameTime = wwTimer_End(&timer); // maybe wwTimer_Stop?
        if(frameTime < frameDelay)
            wwTimer_Delay(frameDelay - frameTime);
    }
    wwWindowAndRenderer_Destroy(win);
    return 0;
}