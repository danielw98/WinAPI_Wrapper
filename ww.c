#include "ww.h"
#include "utils.h"
/* globals local to this file */
static wwWindowAndRenderer *instance;
/* globals used in other files but not in the main program */

/* keep track whether the listbox was initialized or not - used in listbox.c for saving the internal array of strings */
int g_wwListbox_isInit = FALSE;

/* Function prototypes */
static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

wwWindowAndRenderer *wwWindowAndRenderer_Create(HINSTANCE hInstance, wchar_t *windowName, int x, int y, int width, int height)
{   
    // don't take hInstance as a parameter, instead get it from winapi
    // file for debugging/output purposes
    fp = fopen("error.txt", "w");
    if(fp == NULL)
        exit(1);
    // setbuf(fp, NULL); // only uncomment when instant flush is needed - don't overwork the hdd/ssd

    // Window Class Init
    WNDCLASSW wc = {0};
    wc.lpszClassName = L"My Class";
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    RegisterClassW(&wc);

    // Init the heart of the program, WindowAndRenderer structure
    wwWindowAndRenderer *windowAndRenderer = (wwWindowAndRenderer*) malloc(sizeof(wwWindowAndRenderer));
    windowAndRenderer->wc         = wc;
    windowAndRenderer->x          = x;
    windowAndRenderer->y          = y;
    windowAndRenderer->width      = width;
    windowAndRenderer->height     = height;
    windowAndRenderer->running    = wwTrue;
    windowAndRenderer->windowName = windowName;
    // lists of pointers to functions that take care of creating the controls
    windowAndRenderer->buttons    = NULL;
    windowAndRenderer->labels     = NULL;
    windowAndRenderer->checkboxes = NULL;
    windowAndRenderer->textboxes  = NULL;
    windowAndRenderer->listboxes  = NULL;
    windowAndRenderer->rectangles = NULL;
    windowAndRenderer->menus      = NULL;
    // Callbacks
    windowAndRenderer->keyboardCallback = NULL;
    windowAndRenderer->mouseCallback    = NULL;
    // Events
    windowAndRenderer->mouseEvent       = WWMOUSE_NONE;
    windowAndRenderer->keyboardEvent    = WWKEYBOARD_NONE;
    // User Data
    windowAndRenderer->mouseUserData    = NULL;
    windowAndRenderer->keyboardUserData = NULL;
    // misc
    windowAndRenderer->key = WWKEY_NONE;
    // set the global variable because i dont know how to pass it to WM_CREATE as a parameter :D 
    instance = windowAndRenderer;
    
    return windowAndRenderer;
}

void wwWindowAndRenderer_Init(wwWindowAndRenderer *windowAndRenderer)
{
    // the window
    windowAndRenderer->hwnd = CreateWindowExW(
        0, windowAndRenderer->wc.lpszClassName, windowAndRenderer->windowName, WS_OVERLAPPEDWINDOW | WS_VISIBLE ,
        windowAndRenderer->x, windowAndRenderer->y, windowAndRenderer->width, windowAndRenderer->height,
        0, 0, NULL, NULL);
    windowAndRenderer->hdc = GetDC(windowAndRenderer->hwnd);
    // the renderer
    windowAndRenderer->renderer = NULL;
}
wwBool ww_Running(wwWindowAndRenderer *windowAndRenderer)
{
    return windowAndRenderer->running;
}
/* GENERIC WIDGET */
wwWidget* wwWindow_GetWidgetById(wwList *list, unsigned short id)
{
    if(list == NULL)
        return NULL;
    Node *node = list->head;
    while(node != NULL)
    {
        wwWidget *widget = (wwWidget*) node->data;
        if(widget->widgetId == id)
            return widget;
        node = node->next;
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
    Node *node = buttons->head;
    unsigned long long id = 0;

    while (node != NULL)
    {
        wwWidget *button = (wwWidget *)node->data;
        button->id = id;
        button->widgetId = button->id - 0;
        button->window = CreateWindowExW(0, L"Button", button->text, WS_VISIBLE | WS_CHILD,
                                         button->x, button->y, button->width, button->height,
                                         windowAndRenderer->hwnd, (HMENU) id, windowAndRenderer->wc.hInstance, (LPVOID) 0xDEADBEEF);
        node = node->next;
        id++;
    }
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
            {
                buttonCallback(button, windowAndRenderer);
                SetFocus(windowAndRenderer->hwnd);
            }
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
    unsigned long long id = 1000;
    while (node != NULL)
    {
        wwWidget *label = (wwWidget *)node->data;
        label->id = id;
        label->widgetId = label->id - 1000;
        label->window = CreateWindowExW(0, L"Static", label->text, WS_VISIBLE | WS_CHILD,
                                        label->x, label->y, label->width, label->height,
                                        windowAndRenderer->hwnd, (HMENU) id, windowAndRenderer->wc.hInstance, NULL);
        node = node->next;
        id++;
    }
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
            {
                labelCallback(label, windowAndRenderer);
                SetFocus(windowAndRenderer->hwnd);
            }
            return;
        }
        node = node->next;
    }
}

// I don't think this belongs here :-(
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
    while (node != NULL)
    {
        wwWidget *checkbox = (wwWidget *)node->data;
        checkbox->id = id;
        checkbox->widgetId = id - 2000;
        checkbox->window = CreateWindowExW(0, L"Button", checkbox->text, WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
                                           checkbox->x, checkbox->y, checkbox->width, checkbox->height,
                                           windowAndRenderer->hwnd, (HMENU)((unsigned long long)id), windowAndRenderer->wc.hInstance, NULL);
        node = node->next;
        id++;
    }
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
            {
                checkboxCallback(checkbox, windowAndRenderer);
                SetFocus(windowAndRenderer->hwnd);
            }
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
    unsigned long long id = 3000;
    while (node != NULL)
    {
        wwWidget *textbox = (wwWidget *)node->data;
        textbox->id = id;
        textbox->widgetId = textbox->id - 3000;
        textbox->window = CreateWindowExW(0, L"Edit", textbox->text, WS_VISIBLE | WS_CHILD | WS_BORDER,
                                          textbox->x, textbox->y, textbox->width, textbox->height,
                                          windowAndRenderer->hwnd, (HMENU)((unsigned long long)id), windowAndRenderer->wc.hInstance, NULL);
        node = node->next;
        id++;
    }
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
            {
                textboxCallback(textbox, windowAndRenderer);
                SetFocus(windowAndRenderer->hwnd);
            }
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
    unsigned long long id = 4000;
    unsigned int longest;
    while (node != NULL)
    {
        wwWidget *listbox = (wwWidget*) node->data;
        wwListbox *listbox_type = (wwListbox*) listbox;
        longest = 0;
        listbox->id = id;
        listbox->widgetId = id - 4000;
        listbox->window = CreateWindowExW(0, L"listbox", NULL, WS_VISIBLE | WS_CHILD | LBS_NOTIFY | LBS_DISABLENOSCROLL | WS_HSCROLL | WS_VSCROLL ,
                                          listbox->x, listbox->y, listbox->width, listbox->height,
                                          windowAndRenderer->hwnd, (HMENU) id, windowAndRenderer->wc.hInstance, NULL);
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

wwListbox* wwWindow_GetListboxById(wwWindowAndRenderer *windowAndRenderer, unsigned short id)
{
    return (wwListbox*) wwWindow_GetWidgetById(windowAndRenderer->listboxes, id);
}
/* END OF LISTBOXES */


/* MENUS */

static void HandleMenusCreation(wwWindowAndRenderer *windowAndRenderer, LPARAM lParam)
{
    wwMenu *mainMenu = wwMenu_GetMainMenu(windowAndRenderer);
    if(mainMenu == NULL)
        return;
    SetMenu(windowAndRenderer->hwnd, mainMenu->hMenu);
}
static void HandleMenusCommand(wwWindowAndRenderer *windowAndRenderer, WORD menuId)
{
    if(windowAndRenderer->menus == NULL)
        return;
    Node *head = windowAndRenderer->menus->head;
    while(head != NULL)
    {
        wwMenu *menu = (wwMenu*) head->data;
        if (menuId == menu->id)
        {
            wwMenuCallback menuCallback = (wwMenuCallback)menu->callback;
            if (menuCallback != NULL)
            {
                menuCallback(menu, windowAndRenderer);
                SetFocus(windowAndRenderer->hwnd);
            }
            return;
        }
        head = head->next;
    }
}
/* END OF MENUS */
/* PAINTING */

// void HandlePaintingCreation(wwWindowAndRenderer *windowAndRenderer, LPARAM lParam)
// {
//     if(windowAndRenderer->rectangles == NULL)
//         return;
//     wwList *rectangles = windowAndRenderer->rectangles;
//     Node *node = textboxes->head;
//     unsigned short id = 3000;
//     fprintf(fp, "textboxes list = %p\n", windowAndRenderer->textboxes);
//     while (node != NULL)
//     {
//         wwWidget *textbox = (wwWidget *)node->data;
//         textbox->id = id;
//         textbox->widgetId = id - 3000;
//         fprintf(fp, "creating textbox %p (x = %d y = %d)\n", textbox, textbox->x, textbox->y);
//         textbox->window = CreateWindowExW(0, L"Edit", textbox->text, WS_VISIBLE | WS_CHILD | WS_BORDER,
//                                           textbox->x, textbox->y, textbox->width, textbox->height,
//                                           windowAndRenderer->hwnd, (HMENU)id, windowAndRenderer->wc.hInstance, NULL);
//         node = node->next;
//         id++;
//     }
// }

// static void HandleRectangleRepaint(wwWindowAndRenderer *instance, WPARAM wParam, LPARAM lParam)
// {
//     wwList *rectangles = instance->rectangles;
//     if(rectangles == NULL)
//         return;
//     Node *head = rectangles->head;

//     while(head != NULL)
//     {
//         wwColor color;
//         wwRectStruct *rect = (wwRectStruct*) head->data;
//         wwRenderer_DrawRectangle(instance, (wwRect*) rect, color);
//         wwRenderer_DisplayRectangle(instance, (wwRect*) rect);
        
//         head = head->next;
//     }
// }

// static void HandlePaintingCommand(wwWindowAndRenderer *instance, WPARAM wParam, LPARAM lParam)
// {
//     wwList *rectangles = instance->rectangles;
//     if(rectangles == NULL)
//         return;
//     Node *head = rectangles->head;

//     while(head != NULL)
//     {
//         wwRect *rect = (wwRect*) head->data;
//         HDC hdc;
//         PAINTSTRUCT ps;
//         hdc = BeginPaint(instance->hwnd, &ps);
//         RECT windowsRect = {.left = rect->x, .top = rect->y, .right = rect->x + rect->width, .bottom = rect->y + rect->height};
//         Rectangle(hdc, windowsRect.left, windowsRect.top, windowsRect.right, windowsRect.bottom);
//         EndPaint(instance->hwnd, &ps);
//         head = head->next;
//     }
// }

/* END OF PAINTING */

void wwWindowAndRenderer_Destroy(wwWindowAndRenderer *windowAndRenderer)
{
    static int numcalls = 0;
    if(numcalls != 0)
        return;
    if(windowAndRenderer->running == wwTrue)
        windowAndRenderer->running = wwFalse;
    wwList_Delete(instance->buttons);
    wwList_Delete(instance->labels);
    wwList_Delete(instance->checkboxes);
    wwList_Delete(instance->textboxes);
    wwList_Delete(instance->listboxes);
    wwList_Delete(instance->menus);
    ReleaseDC(windowAndRenderer->hwnd, windowAndRenderer->hdc);
    fclose(fp);
    PostQuitMessage(0);
    numcalls++;
}
static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        instance->hwnd = hwnd;
        HandleMenusCreation(instance, lParam);
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
        WORD hiwordWParam = HIWORD(wParam);
        // menu action happened
        if(hiwordWParam == 0)
            HandleMenusCommand(instance, lowordWParam);
        // FIXME !!!
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
    case WM_KEYDOWN:
    case WM_KEYUP:
    {
        // if(instance->keyboardEvent != WWKEYBOARD_KEYPRESSED && instance->key == (wwKey) wParam)
        //     break;
        instance->key = (wwKey) wParam;
        instance->keyboardEvent = (wwKeyboardEvent) msg;
        if(instance->keyboardCallback != NULL)
            instance->keyboardCallback(instance, instance->key, instance->keyboardEvent, instance->keyboardUserData);
        break;
    }
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    {
        instance->mouseEvent = (wwMouseEvent) msg;
        int mouseX = GET_X_LPARAM(lParam);
        int mouseY = GET_Y_LPARAM(lParam);
        if(instance->mouseCallback != NULL)
            instance->mouseCallback(instance, mouseX, mouseY, instance->mouseEvent, instance->mouseUserData);
        break;
    }
    case WM_PAINT:
    {
        // fprintf(fp, "painting rect i think\n");
        // HandleRectangleRepaint(instance, wParam, lParam);
        break;
    }
    case WM_DESTROY:
    { 
        instance->running = wwFalse;
        break;
    }
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}



void wwWindowSetTitle(wwWindowAndRenderer *windowAndRenderer, const wchar_t *title)
{
    SetWindowTextW(windowAndRenderer->hwnd, title);
}

void ww_GetMouseState(int *mouseX, int *mouseY)
{
    POINT mousePoint;
    GetCursorPos(&mousePoint);
    *mouseX = (int) mousePoint.x;
    *mouseY = (int) mousePoint.y;
}


void ww_ProcessEvents(wwWindowAndRenderer *windowAndRenderer)
{
    while (PeekMessageW(&windowAndRenderer->msg, NULL, 0, 0, PM_REMOVE)){
        TranslateMessage(&windowAndRenderer->msg);
        DispatchMessageW(&windowAndRenderer->msg);
    }
}