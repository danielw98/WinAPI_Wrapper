#include "ww.h"

/*
    TODO:
- create a generic Widget struct
- create a generic callback function
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
    wwLabel *label = wwWindow_GetLabelById(win, data->num-1);
    wwCheckbox *checkbox = wwWindow_GetCheckboxById(win, data->num-1);
    wwTextbox *textbox = wwWindow_GetTextboxById(win, data->num-1);
    wwListbox *listbox = wwWindow_GetListboxById(win, data->num-1);
    wwWindow_SetTitle(win, data->str);
    wwButton_SetText(button, data->str);
    //wwLabel_SetText(label, data->str);
    wwCheckbox_SetText(checkbox, data->str);
    wwTextbox_SetText(textbox, data->str);
    //wwListbox_SetCurrentSelectionText(listbox, data->str);
    //wwListbox_DeleteCurrentSelection(listbox);
    wchar_t *text = wwListbox_GetCurrentSelectionText(listbox);
    int id = wwListbox_GetCurrentSelectionId(listbox);
    //wwLabel_SetText(label, text);
    wwListbox_AddStringAtPosition(listbox, data->str, 0);
    wwListbox_AddStringAtPosition(listbox, text, -1);
    wwListbox_AddStringAtPosition(listbox, text, 100);
    id = wwListbox_GetCurrentSelectionId(listbox);
    wwListbox_AddStringAtPosition(listbox, L"Really Large Text That Shouldn't Fit", id+1);
    free(text);
}
void buttonCallback2(wwButton *button, wwWindowAndRenderer *win)
{
    UserData *userData = (UserData*) button->widget.userData;
    wwListbox *listbox = wwWindow_GetListboxById(win, userData->num-1);
    wwListbox_DeleteCurrentSelection(listbox);
}
void labelCallback(wwLabel *label, wwWindowAndRenderer *win)
{
    fprintf(fp, "label callback\n");
    UserData *data = (UserData*) label->widget.userData;
    wwWindow_SetTitle(win, data->str);
    wwLabel_SetText(label, data->str);
}

void checkboxCallback(wwCheckbox *checkbox, wwWindowAndRenderer *win)
{
    fprintf(fp, "checkboxCallback\n");
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
    fprintf(fp, "textbox callback\n");
    UserData *data = (UserData*) textbox->widget.userData;
    wwWindow_SetTitle(win, data->str);
    //wwTextbox_SetText(textbox, data); // FIXME: broken function
}

void listboxCallback(wwListbox *listbox, wwWindowAndRenderer *win)
{
    fprintf(fp, "listbox callback\n");
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    wwWindowAndRenderer *win = wwWindowAndRenderer_Create(hInstance, L"Buttons", L"Buttons Window", 100, 100, 800, 600);

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
    
    wwButton *button3 = wwButton_Create(win, L"Delete1",  20, 360, 80, 25);
    wwButton *button4 = wwButton_Create(win, L"Delete2", 190, 360, 80, 25);
    UserData buttonData3 = {.str = L"Button3", .num = 1};
    UserData buttonData4 = {.str = L"Button4", .num = 2};
    wwButton_SetCallback(button3, buttonCallback2, &buttonData3);
    wwButton_SetCallback(button4, buttonCallback2, &buttonData4);
    return wwMainLoop(win);
}