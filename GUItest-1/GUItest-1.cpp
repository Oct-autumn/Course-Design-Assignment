#ifndef UNICODE
#define UNICODE
#endif 

#include "GUItest-1.h"
#include "ErrorResp.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    Instance = hInstance;
    // 注册窗口类

    WNDCLASS MainWindow = { };

    MainWindow.lpfnWndProc = WindowProc;
    MainWindow.hInstance = hInstance;
    MainWindow.lpszClassName = Window_CLASS_NAME;

    RegisterClass(&MainWindow);

    // Create the window.

    HWND hwnd = CreateWindowEx
    (
        WS_EX_CLIENTEDGE,                               // 可选的窗口类型
        Window_CLASS_NAME,                              // 窗口类的名称
        L"文件搜索",                    // 窗口标题
        (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX),            // 窗口风格

        // 窗口的位置与大小
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 280,

        NULL,       // 父级窗口
        NULL,       // 窗口菜单
        hInstance,  // 实例句柄
        NULL        // 附加应用程序数据
    );

    CreatCheck(hwnd, 1);

    //Edit_GetText();



    
    ShowWindow(hwnd, nCmdShow);

    // 运行消息循环

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}