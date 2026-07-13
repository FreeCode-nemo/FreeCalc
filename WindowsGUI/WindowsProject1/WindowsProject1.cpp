#include<iostream>
#include<windows.h>
#include<cstdlib>
#include<cmath>
#define erttjkak "FREEC-ODETY-OPMAI-AMQIP"
using namespace std;

// 控件ID
#define ID_EDIT_A 1001
#define ID_EDIT_B 1002
#define ID_COM_OP 1003
#define ID_BTN_CALC 1004
#define ID_STATIC_RESULT 1005

// 全局字体句柄
HFONT g_MyFont;

// 窗口回调函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        // 微软雅黑字号18
        g_MyFont = CreateFontW(
            18, 0, 0, 0, FW_NORMAL,
            FALSE, FALSE, FALSE,
            DEFAULT_CHARSET,
            OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,
            DEFAULT_PITCH,
            L"Microsoft YaHei"
        );

        // 文字标签 数字A
        HWND labA = CreateWindowW(L"STATIC", L"数字A：", WS_VISIBLE | WS_CHILD, 20, 20, 60, 20, hWnd, NULL, NULL, NULL);
        SendMessageW(labA, WM_SETFONT, (WPARAM)g_MyFont, TRUE);

        HWND editA = CreateWindowW(L"EDIT", L"0", WS_VISIBLE | WS_CHILD | WS_BORDER, 90, 20, 120, 24, hWnd, (HMENU)ID_EDIT_A, NULL, NULL);
        SendMessageW(editA, WM_SETFONT, (WPARAM)g_MyFont, TRUE);

        // 文字标签 数字B
        HWND labB = CreateWindowW(L"STATIC", L"数字B：", WS_VISIBLE | WS_CHILD, 20, 60, 60, 20, hWnd, NULL, NULL, NULL);
        SendMessageW(labB, WM_SETFONT, (WPARAM)g_MyFont, TRUE);

        HWND editB = CreateWindowW(L"EDIT", L"0", WS_VISIBLE | WS_CHILD | WS_BORDER, 90, 60, 120, 24, hWnd, (HMENU)ID_EDIT_B, NULL, NULL);
        SendMessageW(editB, WM_SETFONT, (WPARAM)g_MyFont, TRUE);

        // 运算标签+下拉框
        HWND labOp = CreateWindowW(L"STATIC", L"运算：", WS_VISIBLE | WS_CHILD, 20, 100, 60, 20, hWnd, NULL, NULL, NULL);
        SendMessageW(labOp, WM_SETFONT, (WPARAM)g_MyFont, TRUE);

        HWND hCombo = CreateWindowW(L"COMBOBOX", L"", WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST, 90, 100, 120, 100, hWnd, (HMENU)ID_COM_OP, NULL, NULL);
        SendMessageW(hCombo, WM_SETFONT, (WPARAM)g_MyFont, TRUE);
        SendMessageW(hCombo, CB_ADDSTRING, 0, (LPARAM)L"1 加法");
        SendMessageW(hCombo, CB_ADDSTRING, 0, (LPARAM)L"2 减法");
        SendMessageW(hCombo, CB_ADDSTRING, 0, (LPARAM)L"3 乘法");
        SendMessageW(hCombo, CB_ADDSTRING, 0, (LPARAM)L"4 除法");
        SendMessageW(hCombo, CB_SETCURSEL, 0, 0);

        // 计算按钮
        HWND btnCalc = CreateWindowW(L"BUTTON", L"开始计算", WS_VISIBLE | WS_CHILD, 20, 140, 190, 30, hWnd, (HMENU)ID_BTN_CALC, NULL, NULL);
        SendMessageW(btnCalc, WM_SETFONT, (WPARAM)g_MyFont, TRUE);

        // 结果显示
        HWND labRes = CreateWindowW(L"STATIC", L"结果：", WS_VISIBLE | WS_CHILD, 20, 190, 60, 20, hWnd, NULL, NULL, NULL);
        SendMessageW(labRes, WM_SETFONT, (WPARAM)g_MyFont, TRUE);

        HWND showRes = CreateWindowW(L"STATIC", L"", WS_VISIBLE | WS_CHILD | SS_CENTER, 90, 190, 120, 20, hWnd, (HMENU)ID_STATIC_RESULT, NULL, NULL);
        SendMessageW(showRes, WM_SETFONT, (WPARAM)g_MyFont, TRUE);

        // 底部文本
        HWND labBottom = CreateWindowW(L"STATIC", L"b站:@豌豆味碗豆", WS_VISIBLE | WS_CHILD, 20, 230, 220, 20, hWnd, NULL, NULL, NULL);
        SendMessageW(labBottom, WM_SETFONT, (WPARAM)g_MyFont, TRUE);

        break;
    }
    case WM_COMMAND:
        if (LOWORD(wParam) == ID_BTN_CALC)
        {
            wchar_t bufA[32] = { 0 };
            GetWindowTextW(GetDlgItem(hWnd, ID_EDIT_A), bufA, 32);
            double a = _wtof(bufA);

            wchar_t bufB[32] = { 0 };
            GetWindowTextW(GetDlgItem(hWnd, ID_EDIT_B), bufB, 32);
            double b = _wtof(bufB);

            int c = SendMessageW(GetDlgItem(hWnd, ID_COM_OP), CB_GETCURSEL, 0, 0) + 1;
            double res = 0;
            wchar_t resText[64] = { 0 };

            if (c == 1) {
                res = a + b;
            }
            if (c == 2) {
                res = a - b;
            }
            if (c == 3) {
                res = a * b;
            }
            if (c == 4) {
                if (fabs(b) < 1e-9) {
                    MessageBoxW(hWnd, L"0不能是除数", L"错误", MB_ICONERROR);
                    SetWindowTextW(GetDlgItem(hWnd, ID_STATIC_RESULT), L"出错");
                    return 0;
                }
                res = a / b;
            }
            if (fabs(res - round(res)) < 1e-9)
            {
                swprintf_s(resText, L"%.0lf", res);
            }
            else
            {
                swprintf_s(resText, L"%.2lf", res);
            }
            SetWindowTextW(GetDlgItem(hWnd, ID_STATIC_RESULT), resText);
            MessageBoxW(hWnd, L"完成计算！", L"OK", MB_OK | MB_ICONINFORMATION);
        }
        break;
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        DeleteObject(g_MyFont);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hWnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
    const wchar_t className[] = L"CalcWinClass";
    WNDCLASSEXW wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = className;
    RegisterClassExW(&wc);

    DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX;
    HWND hWnd = CreateWindowExW(0, className, L"FreeCalc", style,
        CW_USEDEFAULT, CW_USEDEFAULT, 260, 320, NULL, NULL, hInst, NULL);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg = { 0 };
    while (GetMessageW(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return (int)msg.wParam;
}