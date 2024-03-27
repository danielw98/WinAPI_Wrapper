#include "utils.h"
UINT ww_CalcLBItemWidth(HWND window, wchar_t *text)
{
    if(text == NULL)
        return 0;
    RECT r;
    HDC hLBDC = GetDC(window);
    HDC hDC = CreateCompatibleDC(hLBDC);
    HFONT hFont = (HFONT) SendMessageW(window, WM_GETFONT, 0, 0);
    HGDIOBJ hOrgFont = SelectObject(hDC, hFont);
    ZeroMemory(&r, sizeof(r));
    DrawTextW(hDC, text, -1, &r, DT_CALCRECT|DT_SINGLELINE|DT_NOCLIP);
    SelectObject(hDC, hOrgFont);
    DeleteDC(hDC);
    ReleaseDC(window, hLBDC);
    return (r.right - r.left) + (2 * GetSystemMetrics(SM_CXEDGE));
}