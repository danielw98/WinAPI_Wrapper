#include "ww.h"

static wwWindowAndRenderer *instance;

static void HandleButtonsCreation(wwWindowAndRenderer *windowAndRenderer, LPARAM lParam)
{
    wwList *buttons = windowAndRenderer->buttons;
  
    fprintf(fp, "buttons list = %p\n",  windowAndRenderer->buttons);
 
    Node *node = buttons->head;
    unsigned int id = 1;
    
    while(node != NULL)
    {
        wwButton *button = (wwButton*) node->data;
        button->id = id;
        fprintf(fp, "creating button %p (x = %d y = %d)\n", button, button->x, button->y);
        CreateWindowExW(0, L"button", button->name, WS_VISIBLE | WS_CHILD, 
                        button->x, button->y, button->width, button->height, 
                        windowAndRenderer->hwnd, (HMENU) button->id, windowAndRenderer->wc.hInstance, NULL);
        node = node->next;
        id++;
    }
    fprintf(fp, "NULL node reached\n");
}

static void HandleButtonsCommand(wwList *buttons, WORD buttonId)
{
    Node *node = buttons->head;
    while(node != NULL)
    {
        wwButton *button = (wwButton*) node->data;
        if (buttonId == button->id)
        {
            button->callback(button->userData);
            break;
        }
        node = node->next;
    }
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_CREATE:{
        instance->hwnd = hwnd;
        HandleButtonsCreation(instance, lParam);
        break;
    }
    case WM_COMMAND:{
        HandleButtonsCommand(instance->buttons, LOWORD(wParam));
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
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
    instance = windowAndRenderer;
    return windowAndRenderer;
}

void wwWindowSetTitle(wwWindowAndRenderer *windowAndRenderer, const wchar_t *title)
{
    SetWindowTextW(windowAndRenderer->hwnd, title);
}
int wwMainLoop(wwWindowAndRenderer *windowAndRenderer)
{
    CreateWindowExW(0, windowAndRenderer->wc.lpszClassName, windowAndRenderer->windowName, WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
                  windowAndRenderer->x, windowAndRenderer->y, windowAndRenderer->width, windowAndRenderer->height, 
                  0, 0, windowAndRenderer->wc.hInstance, NULL);
    while(GetMessageW(&windowAndRenderer->msg, NULL, 0, 0)) 
    {
        TranslateMessage(&windowAndRenderer->msg);
        DispatchMessageW(&windowAndRenderer->msg);
    }
    wwList_Delete(windowAndRenderer->buttons);
    return (int) windowAndRenderer->msg.wParam;
}