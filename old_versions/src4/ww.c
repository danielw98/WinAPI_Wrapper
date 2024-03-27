#include "ww.h"
#include "utils.h"
/* globals local to this file */
static wwWindowAndRenderer *instance;
/* globals used in other files but not in the main program */
int g_wwListbox_isInit = FALSE;


/* GENERIC WIDGET */
wwWidget* wwWindow_GetWidgetById(wwList *list, unsigned short id)
{
    if(list == NULL)
        return NULL;
    Node *head = list->head;
    while(head != NULL)
    {
        wwWidget *widget = (wwWidget*) head->data;
        if(widget->widgetId == id)
            return widget;
        head = head->next;
    }
    return NULL;
}
/* END OF GENERIC WIDGET */
/* BUTTONS */
static void HandleButtonsCreation(wwWindowAndRenderer *windowAndRenderer, LPARAM lParam)
{
    if(windowAndRenderer->buttons == NULL)
        return;
    wwList *buttons = windowAndRenderer->buttons;

    fprintf(fp, "buttons list = %p\n", windowAndRenderer->buttons);

    Node *node = buttons->head;
    unsigned long id = 0;

    while (node != NULL)
    {
        wwWidget *button = (wwWidget *)node->data;
        button->id = id;
        button->widgetId = id - 0;
        fprintf(fp, "creating button %p (x = %d y = %d)\n", button, button->x, button->y);
        button->window = CreateWindowExW(0, L"Button", button->text, WS_VISIBLE | WS_CHILD,
                                         button->x, button->y, button->width, button->height,
                                         windowAndRenderer->hwnd, (HMENU)id, windowAndRenderer->wc.hInstance, NULL);
        node = node->next;
        id++;
    }
    fprintf(fp, "NULL node reached\n");
}

static void HandleButtonsCommand(wwWindowAndRenderer *windowAndRenderer, WORD buttonId)
{
    if(windowAndRenderer->buttons == NULL)
        return;
    Node *node = windowAndRenderer->buttons->head;
    while (node != NULL)
    {
        wwButton *button = (wwButton *)node->data;
        if (buttonId == button->widget.id)
        {
            wwButtonCallback buttonCallback = (wwButtonCallback)button->widget.callback;
            if (buttonCallback != NULL)
                buttonCallback(button, windowAndRenderer);
            return;
        }
        node = node->next;
    }
}

wwButton* wwWindow_GetButtonById(wwWindowAndRenderer *windowAndRenderer, unsigned short id)
{
    return (wwButton*) wwWindow_GetWidgetById(windowAndRenderer->buttons, id);
}
/* END OF BUTTONS */

/* LABELS */
static void HandleLabelsCreation(wwWindowAndRenderer *windowAndRenderer, LPARAM lParam)
{
    if(windowAndRenderer->labels == NULL)
        return;
    wwList *labels = windowAndRenderer->labels;
    Node *node = labels->head;
    unsigned long id = 1000;
    fprintf(fp, "labels list = %p\n", windowAndRenderer->labels);
    while (node != NULL)
    {
        wwWidget *label = (wwWidget *)node->data;
        label->id = id;
        label->widgetId = id - 1000;
        fprintf(fp, "creating label %p (x = %d y = %d)\n", label, label->x, label->y);
        label->window = CreateWindowExW(0, L"Static", label->text, WS_VISIBLE | WS_CHILD,
                                        label->x, label->y, label->width, label->height,
                                        windowAndRenderer->hwnd, (HMENU)id, windowAndRenderer->wc.hInstance, NULL);
        node = node->next;
        id++;
    }
    fprintf(fp, "NULL node reached\n");
}

static void HandleLabelsCommand(wwWindowAndRenderer *windowAndRenderer, WORD labelId)
{
    if(windowAndRenderer->labels == NULL)
        return;
    Node *node = windowAndRenderer->labels->head;
    while (node != NULL)
    {
        wwLabel *label = (wwLabel *)node->data;
        if (labelId == label->widget.id)
        {
            wwLabelCallback labelCallback = (wwLabelCallback)label->widget.callback;
            if (labelCallback != NULL)
                labelCallback(label, windowAndRenderer);
            return;
        }
        node = node->next;
    }
}

wwLabel* wwWindow_GetLabelById(wwWindowAndRenderer *windowAndRenderer, unsigned short id)
{
    return (wwLabel*) wwWindow_GetWidgetById(windowAndRenderer->labels, id);
}
/* END OF LABELS */

/* CHECKBOXES */
static void HandleCheckboxesCreation(wwWindowAndRenderer *windowAndRenderer, LPARAM lParam)
{
    if(windowAndRenderer->checkboxes == NULL)
        return;
    wwList *checkboxes = windowAndRenderer->checkboxes;
    Node *node = checkboxes->head;
    unsigned long id = 2000;
    fprintf(fp, "checkboxes list = %p\n", windowAndRenderer->checkboxes);
    while (node != NULL)
    {
        wwWidget *checkbox = (wwWidget *)node->data;
        checkbox->id = id;
        checkbox->widgetId = id - 2000;
        fprintf(fp, "creating checkbox %p (x = %d y = %d)\n", checkbox, checkbox->x, checkbox->y);
        checkbox->window = CreateWindowExW(0, L"Button", checkbox->text, WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
                                           checkbox->x, checkbox->y, checkbox->width, checkbox->height,
                                           windowAndRenderer->hwnd, (HMENU)id, windowAndRenderer->wc.hInstance, NULL);
        node = node->next;
        id++;
    }
    fprintf(fp, "NULL node reached\n");
}

static void HandleCheckboxesCommand(wwWindowAndRenderer *windowAndRenderer, WORD checkboxId)
{
    if(windowAndRenderer->checkboxes == NULL)
        return;
    Node *node = windowAndRenderer->checkboxes->head;
    while (node != NULL)
    {
        wwCheckbox *checkbox = (wwCheckbox *)node->data;
        if (checkboxId == checkbox->widget.id)
        {
            wwCheckboxCallback checkboxCallback = (wwCheckboxCallback)checkbox->widget.callback;
            if (checkboxCallback != NULL)
                checkboxCallback(checkbox, windowAndRenderer);
            return;
        }
        node = node->next;
    }
}

wwCheckbox* wwWindow_GetCheckboxById(wwWindowAndRenderer *windowAndRenderer, unsigned short id)
{
    return (wwCheckbox*) wwWindow_GetWidgetById(windowAndRenderer->checkboxes, id);
}
/* END OF CHECKBOXES */

/* TEXTBOXES */
static void HandleTextboxesCreation(wwWindowAndRenderer *windowAndRenderer, LPARAM lParam)
{
    if(windowAndRenderer->textboxes == NULL)
        return;
    wwList *textboxes = windowAndRenderer->textboxes;
    Node *node = textboxes->head;
    unsigned short id = 3000;
    fprintf(fp, "textboxes list = %p\n", windowAndRenderer->textboxes);
    while (node != NULL)
    {
        wwWidget *textbox = (wwWidget *)node->data;
        textbox->id = id;
        textbox->widgetId = id - 3000;
        fprintf(fp, "creating textbox %p (x = %d y = %d)\n", textbox, textbox->x, textbox->y);
        textbox->window = CreateWindowExW(0, L"Edit", textbox->text, WS_VISIBLE | WS_CHILD | WS_BORDER,
                                          textbox->x, textbox->y, textbox->width, textbox->height,
                                          windowAndRenderer->hwnd, (HMENU)id, windowAndRenderer->wc.hInstance, NULL);
        node = node->next;
        id++;
    }
    fprintf(fp, "NULL node reached\n");
}

static void HandleTextboxesCommand(wwWindowAndRenderer *windowAndRenderer, WORD textboxId)
{
    if(windowAndRenderer->textboxes == NULL)
        return;
    Node *node = windowAndRenderer->textboxes->head;
    while (node != NULL)
    {
        wwTextbox *textbox = (wwTextbox*)node->data;
        if (textboxId == textbox->widget.id)
        {
            wwTextboxCallback textboxCallback = (wwTextboxCallback)textbox->widget.callback;
            if (textboxCallback != NULL)
                textboxCallback(textbox, windowAndRenderer);
            return;
        }
        node = node->next;
    }
}
wwTextbox* wwWindow_GetTextboxById(wwWindowAndRenderer *windowAndRenderer, unsigned short id)
{
    return (wwTextbox*) wwWindow_GetWidgetById(windowAndRenderer->textboxes, id);
}
/* END OF TEXTBOXES */

/* LISTBOXES */
static void HandleListboxesCreation(wwWindowAndRenderer *windowAndRenderer, LPARAM lParam)
{
    if(windowAndRenderer->listboxes == NULL)
        return;
    wwList *listboxes = windowAndRenderer->listboxes;
    Node *node = listboxes->head;
    unsigned long id = 4000;
    fprintf(fp, "listboxes list = %p\n", windowAndRenderer->listboxes);
    unsigned int longest;
    while (node != NULL)
    {
        wwWidget *listbox = (wwWidget *)node->data;
        wwListbox *listbox_type = (wwListbox *)listbox;
        longest = 0;
        listbox->id = id;
        listbox->widgetId = id - 4000;
        listbox->window = CreateWindowExW(0, L"listbox", NULL, WS_VISIBLE | WS_CHILD | LBS_NOTIFY | LBS_DISABLENOSCROLL | WS_HSCROLL | WS_VSCROLL ,
                                          listbox->x, listbox->y, listbox->width, listbox->height,
                                          windowAndRenderer->hwnd, (HMENU)id, windowAndRenderer->wc.hInstance, NULL);
        for (int i = 0; i < listbox_type->numItems; i++)
        {
            SendMessageW(listbox->window, LB_ADDSTRING, 0, (LPARAM)listbox_type->items[i]);
            unsigned int currentLength = ww_CalcLBItemWidth(listbox->window, listbox_type->items[i]);
            if(currentLength > longest)
                longest = currentLength;
        }
        SendMessageW(listbox->window, LB_SETHORIZONTALEXTENT, (WPARAM) longest, 0);
        listbox_type->longest = longest;
        node = node->next;
        id++;
    }
    
    fprintf(fp, "NULL node reached\n");
    g_wwListbox_isInit = TRUE;
}

static void HandleListboxesCommand(wwWindowAndRenderer *windowAndRenderer, WPARAM wParam, LPARAM lParam)
{
    // if(windowAndRenderer->listboxes == NULL)
    //     return;
    Node *node = windowAndRenderer->listboxes->head;
    while (node != NULL)
    {
        unsigned short listboxId = LOWORD(wParam);
        wwListbox *listbox = (wwListbox*) node->data;
        if (listboxId == listbox->widget.id)
        {
            wwListboxCallback listboxCallback = (wwListboxCallback)listbox->widget.callback;
            if (listboxCallback != NULL)
                listboxCallback(listbox, windowAndRenderer);
            return;
        }
        node = node->next;
    }
}

static void FreeListboxesStrings(wwList *listboxes)
{
    if(listboxes == NULL)
        return;
    Node *node = listboxes->head;
    while (node != NULL)
    {
        wwListbox *listbox = (wwListbox*) node->data;
        for (int i = 0; i < listbox->numItems; i++)
            free(listbox->items[i]);
        if(listbox->items != NULL)
            free(listbox->items);
        node = node->next;
    }
}
wwListbox* wwWindow_GetListboxById(wwWindowAndRenderer *windowAndRenderer, unsigned short id)
{
    return (wwListbox*) wwWindow_GetWidgetById(windowAndRenderer->listboxes, id);
}
/* END OF LISTBOXES */
static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        instance->hwnd = hwnd;
        HandleButtonsCreation(instance, lParam);
        HandleLabelsCreation(instance, lParam);
        HandleCheckboxesCreation(instance, lParam);
        HandleTextboxesCreation(instance, lParam);
        HandleListboxesCreation(instance, lParam);
        break;
    }
    case WM_COMMAND:
    {
        WORD lowordWParam = LOWORD(wParam);
        if (lowordWParam < 1000)
            HandleButtonsCommand(instance, lowordWParam);
        else if (lowordWParam < 2000)
            HandleLabelsCommand(instance, lowordWParam);
        else if (lowordWParam < 3000)
            HandleCheckboxesCommand(instance, lowordWParam);
        else if (lowordWParam < 4000)
            HandleTextboxesCommand(instance, lowordWParam);
        else if (lowordWParam < 5000)
            HandleListboxesCommand(instance, wParam, lParam);
        break;
    }
    case WM_DESTROY:
    { 
        PostQuitMessage(0);
        break;
    }
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

wwWindowAndRenderer *wwWindowAndRenderer_Create(HINSTANCE hInstance, wchar_t *className, wchar_t *windowName, int x, int y, int width, int height)
{
    wwWindowAndRenderer *windowAndRenderer = (wwWindowAndRenderer *)malloc(sizeof(wwWindowAndRenderer));
    MSG msg;
    WNDCLASSW wc = {0};
    wc.lpszClassName = className;
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    RegisterClassW(&wc);
    windowAndRenderer->msg = msg;
    windowAndRenderer->wc = wc;
    windowAndRenderer->x = x;
    windowAndRenderer->y = y;
    windowAndRenderer->width = width;
    windowAndRenderer->height = height;
    windowAndRenderer->windowName = windowName;
    // lists of pointers to functions that take care of creating the controls
    windowAndRenderer->buttons = NULL;
    windowAndRenderer->labels = NULL;
    windowAndRenderer->checkboxes = NULL;
    windowAndRenderer->textboxes = NULL;
    windowAndRenderer->listboxes = NULL;
    instance = windowAndRenderer;
    fp = fopen("error.txt", "w");
    return windowAndRenderer;
}

void wwWindowSetTitle(wwWindowAndRenderer *windowAndRenderer, const wchar_t *title)
{
    SetWindowTextW(windowAndRenderer->hwnd, title);
}
int wwMainLoop(wwWindowAndRenderer *windowAndRenderer)
{
    windowAndRenderer->hwnd = CreateWindowExW(
        0, windowAndRenderer->wc.lpszClassName, windowAndRenderer->windowName, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        windowAndRenderer->x, windowAndRenderer->y, windowAndRenderer->width, windowAndRenderer->height,
        0, 0, windowAndRenderer->wc.hInstance, NULL);
    while (GetMessageW(&windowAndRenderer->msg, NULL, 0, 0))
    {
        TranslateMessage(&windowAndRenderer->msg);
        DispatchMessageW(&windowAndRenderer->msg);
    }
    wwList_Delete(instance->buttons);
    wwList_Delete(instance->labels);
    wwList_Delete(instance->checkboxes);
    wwList_Delete(instance->textboxes);
    FreeListboxesStrings(instance->listboxes);
    wwList_Delete(instance->listboxes);
    fclose(fp);
    return (int)windowAndRenderer->msg.wParam;
}