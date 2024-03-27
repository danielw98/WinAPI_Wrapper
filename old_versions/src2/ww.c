#include "ww.h"

static wwWindowAndRenderer *instance;

/* BUTTONS */
static void HandleButtonsCreation(wwWindowAndRenderer *windowAndRenderer, LPARAM lParam)
{
    wwList *buttons = windowAndRenderer->buttons;
  
    fprintf(fp, "buttons list = %p\n",  windowAndRenderer->buttons);
 
    Node *node = buttons->head;
    int id = 1;
    
    while(node != NULL)
    {
        wwButton *button = (wwButton*) node->data;
        button->id = id;
        fprintf(fp, "creating button %p (x = %d y = %d)\n", button, button->x, button->y);
        button->window = CreateWindowExW(0, L"Button", button->name, WS_VISIBLE | WS_CHILD, 
                         button->x, button->y, button->width, button->height, 
                         windowAndRenderer->hwnd, (HMENU) button->id, windowAndRenderer->wc.hInstance, NULL);
        node = node->next;
        id++;
    }
    fprintf(fp, "NULL node reached\n");
}

static void HandleButtonsCommand(wwWindowAndRenderer *windowAndRenderer, WORD buttonId)
{
    Node *node = windowAndRenderer->buttons->head;
    while(node != NULL)
    {
        wwLabel *button = (wwLabel*) node->data;
        if (buttonId == button->id)
        {
            button->callback(button, windowAndRenderer);
            break;
        }
        node = node->next;
    }
}
/* END OF BUTTONS */

/* LABELS */
static void HandleLabelsCreation(wwWindowAndRenderer *windowAndRenderer, LPARAM lParam)
{
    wwList *labels = windowAndRenderer->labels;
    Node *node = labels->head;
    int id = 1000;
    fprintf(fp, "labels list = %p\n",  windowAndRenderer->labels);
    while(node != NULL)
    {
        wwLabel *label = (wwLabel*) node->data;
        label->id = id;
        fprintf(fp, "creating label %p (x = %d y = %d)\n", label, label->x, label->y);
        label->window = CreateWindowExW(0, L"Static", label->text, WS_VISIBLE | WS_CHILD, 
                        label->x, label->y, label->width, label->height, 
                        windowAndRenderer->hwnd, (HMENU) label->id, windowAndRenderer->wc.hInstance, NULL);
        node = node->next;
        id++;
    }
    fprintf(fp, "NULL node reached\n");
}

static void HandleLabelsCommand(wwWindowAndRenderer *windowAndRenderer, WORD labelId)
{
    Node *node = windowAndRenderer->labels->head;
    while(node != NULL)
    {
        wwLabel *label = (wwLabel*) node->data;
        if (labelId == label->id)
        {
            label->callback(label, windowAndRenderer);
            break;
        }
        node = node->next;
    }
}
/* END OF LABELS */

/* CHECKBOXES */
static void HandleCheckboxesCreation(wwWindowAndRenderer *windowAndRenderer, LPARAM lParam)
{
    wwList *checkboxes = windowAndRenderer->checkboxes;
    Node *node = checkboxes->head;
    int id = 10000;
    fprintf(fp, "checkboxes list = %p\n",  windowAndRenderer->checkboxes);
    while(node != NULL)
    {
        wwCheckbox *checkbox = (wwCheckbox*) node->data;
        checkbox->id = id;
        fprintf(fp, "creating checkbox %p (x = %d y = %d)\n", checkbox, checkbox->x, checkbox->y);
        checkbox->window = CreateWindowExW(0, L"Button", checkbox->text, WS_VISIBLE | WS_CHILD | BS_CHECKBOX, 
                        checkbox->x, checkbox->y, checkbox->width, checkbox->height, 
                        windowAndRenderer->hwnd, (HMENU) checkbox->id, windowAndRenderer->wc.hInstance, NULL);
        node = node->next;
        id++;
    }
    fprintf(fp, "NULL node reached\n");
}

static void HandleCheckboxesCommand(wwWindowAndRenderer *windowAndRenderer, WORD checkboxId)
{
    Node *node = windowAndRenderer->checkboxes->head;
    while(node != NULL)
    {
        wwCheckbox *checkbox = (wwCheckbox*) node->data;
        if (checkboxId == checkbox->id)
        {
            checkbox->callback(checkbox, windowAndRenderer);
            break;
        }
        node = node->next;
    }
}
/* END OF CHECKBOXES */
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_CREATE:{
        instance->hwnd = hwnd;
        HandleButtonsCreation(instance, lParam);
        HandleLabelsCreation(instance, lParam);
        HandleCheckboxesCreation(instance, lParam);
        break;
    }
    case WM_COMMAND:{
        HandleButtonsCommand(instance, LOWORD(wParam));
        HandleLabelsCommand(instance, LOWORD(wParam));
        HandleCheckboxesCommand(instance, LOWORD(wParam));
        break;
    }
    case WM_DESTROY:{
        fclose(fp);
        PostQuitMessage(0);
        break;
    }
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

wwWindowAndRenderer* wwWindowAndRenderer_Create(HINSTANCE hInstance, wchar_t *className, wchar_t *windowName, int x, int y, int width, int height)
{
    wwWindowAndRenderer *windowAndRenderer = (wwWindowAndRenderer*) malloc(sizeof(wwWindowAndRenderer));
    MSG msg;
    WNDCLASSW wc = {0};
    wc.lpszClassName = className;
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    RegisterClassW(&wc);
    windowAndRenderer->msg    = msg;
    windowAndRenderer->wc     = wc;
    windowAndRenderer->x      = x;
    windowAndRenderer->y      = y;
    windowAndRenderer->width  = width;
    windowAndRenderer->height = height;
    windowAndRenderer->windowName = windowName;
    // lists of pointers to functions that take care of creating the controls
    windowAndRenderer->buttons = NULL;
    windowAndRenderer->labels  = NULL;
    windowAndRenderer->checkboxes = NULL;
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
    while(GetMessageW(&windowAndRenderer->msg, NULL, 0, 0)) 
    {
        TranslateMessage(&windowAndRenderer->msg);
        DispatchMessageW(&windowAndRenderer->msg);
    }
    wwList_Delete(windowAndRenderer->buttons);
    wwList_Delete(windowAndRenderer->labels);
    return (int) windowAndRenderer->msg.wParam;
}