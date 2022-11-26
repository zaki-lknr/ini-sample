#include "main.h"

// コードベースは「猫でもわかるWindowsプログラミング(第2版) 11章「メモ帳もどきを作ろう」より

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

char szClassName[] = "controls02"; // ウインドウクラス
HINSTANCE hInst;

int APIENTRY WinMain(HINSTANCE hInstance,
                        HINSTANCE hPrevInstance,
                        LPSTR     lpCmdLine,
                        int       nCmdShow )
{
    MSG msg;
    BOOL bRet;

    hInst = hInstance;
    if (! InitApp(hInstance)) {
        return FALSE;
    }
    if (! InitInstance(hInstance, nCmdShow)) {
        return FALSE;
    }
    while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
        if (bRet == -1) {
            break;
        }
        else {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

// ウインドウクラスの登録
ATOM InitApp(HINSTANCE hInst)
{
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;
    wc.hIcon = NULL;
    wc.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = (LPCSTR)szClassName;
    wc.hIconSm = NULL;

    return (RegisterClassEx(&wc));
}

// ウインドウの生成
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;

    hWnd = CreateWindow(szClassName, "ini sample",
                        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 230, 125,
                        NULL, NULL, hInst, NULL
                        );
    if (! hWnd) {
        return FALSE;
    }
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}

// ウインドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    int id;
    static HWND hWrite, hRead, hClr, hEdit;
    char szBuf[64];

    switch (msg) {
    case WM_CREATE:
        hEdit = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                                10, 10, 200, 25, hWnd, (HMENU)ID_EDIT, hInst, NULL);
        hWrite = CreateWindow("BUTTON", "write", WS_CHILD | WS_VISIBLE,
                            85, 45, 50, 30, hWnd, (HMENU)ID_BTN_WRITE, hInst, NULL);
        hRead = CreateWindow("BUTTON", "read", WS_CHILD | WS_VISIBLE,
                            25, 45, 50, 30, hWnd, (HMENU)ID_BTN_READ, hInst, NULL);
        hClr = CreateWindow("BUTTON", "clear", WS_CHILD | WS_VISIBLE,
                            145, 45, 50, 30, hWnd, (HMENU)ID_BTN_CLEAR, hInst, NULL);
        SendMessage(hEdit, EM_SETLIMITTEXT, (WPARAM)63, 0);
        break;
    case WM_SETFOCUS:
        SetFocus(hEdit);
        break;
    case WM_COMMAND:
        switch (LOWORD(wp)) {
        case ID_BTN_READ:
            // readボタン押下
            GetPrivateProfileString("Section", "config", "", szBuf, sizeof(szBuf), "./config.ini");
            SetWindowText(hEdit, szBuf);
            break;
        case ID_BTN_WRITE:
            // writeボタン押下時
            GetWindowText(hEdit, szBuf, 64);
            WritePrivateProfileString("Section", "config", szBuf, "./config.ini");
            MessageBox(hWnd, szBuf, "input text", MB_OK);
            break;
        case ID_BTN_CLEAR:
            SetWindowText(hEdit, "");
            break;
        }
        break;
    case WM_CLOSE:
        DestroyWindow(hEdit);
        DestroyWindow(hWrite);
        DestroyWindow(hRead);
        DestroyWindow(hClr);
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return (DefWindowProc(hWnd, msg, wp, lp));
    }
    return 0;
}
