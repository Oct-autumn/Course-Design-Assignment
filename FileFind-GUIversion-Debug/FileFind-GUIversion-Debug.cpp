// FileFind-GUIversion-Debug.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "FileFind-GUIversion-Debug.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE Instance;                             // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Help(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK Setting(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。
    
    LoadStringW(hInstance, IDC_FILEFINDGUIVERSIONDEBUG, szWindowClass, MAX_LOADSTRING);
    wcscpy_s(szTitle, L"文件查找");

    Instance = hInstance; // 将实例句柄存储在全局变量中

    WNDCLASS MainWindow = { };

    MainWindow.lpfnWndProc = WndProc;
    MainWindow.hInstance = hInstance;
    MainWindow.lpszClassName = szWindowClass;
    MainWindow.lpszMenuName = MAKEINTRESOURCEW(IDC_FILEFINDGUIVERSIONDEBUG);

    RegisterClass(&MainWindow);

    // Create the window.

    HWND hwnd = CreateWindowEx
    (
        WS_EX_CLIENTEDGE,                               // 可选的窗口类型
        szWindowClass,                              // 窗口类的名称
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

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FILEFINDGUIVERSIONDEBUG));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        {
        //绘制控件
            {
                Label1 = CreateWindowEx               //创建“搜索根目录”静态文本框
                (
                    0,
                    Label_CLASS_NAME,
                    L"搜索根目录：",
                    (WS_CHILD | WS_VISIBLE),
                    10, 10, 150, 25,
                    hWnd,
                    (HMENU)UID_Label1,
                    Instance,
                    NULL
                );
                CreatCheck(Label1, 2);
                            
                TextBox_RootPath = CreateWindow     //创建“搜索根目录”文本编辑框
                (
                    TextBox_CLASS_NAME,
                    L"",
                    (WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_BORDER),
                    10, 35, 450, 25,
                    hWnd,
                    (HMENU)UID_TextBox_RootPath,
                    Instance,
                    NULL
                );
                CreatCheck(TextBox_RootPath, 3);

                Label2 = CreateWindow     //创建“文件名”静态文本框
                (
                    Label_CLASS_NAME,
                    L"文件名：",
                    (WS_CHILD | WS_VISIBLE),
                    10, 60, 100, 25,
                    hWnd,
                    (HMENU)UID_Label2,
                    Instance,
                    NULL
                );
                CreatCheck(Label2, 4);

                TextBox_FileName = CreateWindow     //创建“文件名”文本编辑框
                (
                    TextBox_CLASS_NAME,
                    L"",
                    (WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_BORDER),
                    10, 85, 200, 25,
                    hWnd,
                    (HMENU)UID_TextBox_FileName,
                    Instance,
                    NULL
                );
                CreatCheck(TextBox_FileName, 5);

                Start_Search = CreateWindow     //创建“开始搜索”按钮
                (
                    Button_CLASS_NAME,
                    L"开始搜索",
                    (WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT),
                    360, 70, 100, 40,
                    hWnd,
                    (HMENU)UID_StartSearch,
                    Instance,
                    NULL
                );
                CreatCheck(TextBox_FileName, 5);

                FileList = CreateWindow         //创建文件地址列表
                (
                    List_CLASS_NAME,
                    L"",
                    (WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | LBS_NOTIFY),
                    10, 120, 450, 75,
                    hWnd,
                    (HMENU)UID_FileList,
                    Instance,
                    NULL
                );
                CreatCheck(FileList, 6);

                ChoseButton1 = CreateWindow     //创建“精确查找”单选框
                (
                    CheckBox_CLASS_NAME,
                    L"精确查找",
                    (WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON | WS_GROUP),
                    230, 70, 125, 25,
                    hWnd,
                    (HMENU)UID_SearchMode,
                    Instance,
                    NULL
                );
                CreatCheck(ChoseButton1, 7);

                ChoseButton2 = CreateWindow     //创建“模糊查找”单选框
                (
                    CheckBox_CLASS_NAME,
                    L"模糊查找",
                    (WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON),
                    230, 95, 125, 25,
                    hWnd,
                    (HMENU)UID_SearchMode,
                    Instance,
                    NULL
                );
                CreatCheck(ChoseButton2, 8);

                Status = CreateWindow
                (
                    L"msctls_statusbar32",
                    (PCTSTR)NULL,
                    (WS_CHILD | WS_VISIBLE),
                    0, 0, 0, 0,
                    hWnd,
                    (HMENU)UID_StatusBar,
                    Instance,
                    NULL
                );
            }

            SendMessage(ChoseButton1, BM_SETCHECK, BST_CHECKED, NULL);
            wcscpy_s(ProgramStatus, L"就绪.");
            SendMessage(Status, WM_SETTEXT, NULL, (LPARAM)ProgramStatus);
            
        }
        break;
    case WM_COMMAND:
        {
            WORD wNotifyCode = HIWORD(wParam);
            WORD wmId = LOWORD(wParam);
            
            switch (wmId)
            {
                {//菜单栏操作分析
                case IDM_ABOUT: //关于
                    DialogBox(Instance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                    break;
                case IDM_EXIT:  //退出
                    if (MessageBox(hWnd, L"确定要退出吗？", L"注意", MB_OKCANCEL) == IDOK)
                    {
                        DestroyWindow(hWnd);
                    }
                    break; 
                case IDM_USERHELP:
                    DialogBox(Instance, MAKEINTRESOURCE(IDD_USERHELP), hWnd, Help);
                    break;
                case IDM_SETTING:
                    DialogBox(Instance, MAKEINTRESOURCE(IDD_SearchSetting), hWnd, Setting);
                    break;
                }
                
                {//按钮操作分析
                case UID_StartSearch:
                    if (MessageBox(hWnd, L"即将开始搜索\n注意，搜索期间不能中止，较多的搜索项将占用较多时间\n开始搜索吗？", L"提示", MB_OKCANCEL) == IDOK)   //显示提示
                    {
                        TCHAR RootPath_w[PATH_LONG];
                        TCHAR FileName_w[FILENAME_MAX];
                        GetWindowText(TextBox_RootPath, RootPath_w, PATH_LONG);
                        GetWindowText(TextBox_FileName, FileName_w, FILENAME_MAX);

                        char RootPath[PATH_LONG];
                        char FileName[FILENAME_MAX];

                        ExchCheck(WCtoMB((wchar_t*)RootPath_w, RootPath, sizeof(RootPath) / sizeof(RootPath[0])), 1);
                        ExchCheck(WCtoMB((wchar_t*)FileName_w, FileName, sizeof(FileName) / sizeof(FileName[0])), 1);

                        //检查是否漏掉了路径末尾的'\'
                        if (RootPath[strlen(RootPath) - 1] != '\\')
                        {
                            strcat_s(RootPath, "\\");
                            ExchCheck(MBtoWC(RootPath, RootPath_w, sizeof(RootPath_w) / sizeof(RootPath_w[0])), 1);
                            SetWindowText(TextBox_RootPath, RootPath_w);
                        }

                        if (SendMessage(ChoseButton1, BM_GETCHECK, NULL, NULL) == BST_CHECKED)  //进行精确查找
                        {
                            CleanFileList();
                            Sum = 0;
                            
                            DfsFolder(RootPath, FileName, 0, 1);
                            if (Sum == 0) MessageBox(hwnd, L"未在搜索根目录下找到相关文件", L"提示", MB_OK);
                            wcscpy_s(ProgramStatus, L"就绪.");
                            SendMessage(Status, WM_SETTEXT, NULL, (LPARAM)ProgramStatus);
                        }
                        if (SendMessage(ChoseButton2, BM_GETCHECK, NULL, NULL) == BST_CHECKED)  //进行模糊查找
                        {
                            CleanFileList();
                            Sum = 0;
                            
                            DfsFolder(RootPath, FileName, 0, 2);
                            if (Sum == 0) MessageBox(hwnd, L"未在搜索根目录下找到相关文件", L"提示", MB_OK);
                            wcscpy_s(ProgramStatus, L"就绪.");
                            SendMessage(Status, WM_SETTEXT, NULL, (LPARAM)ProgramStatus);
                        }
                    }

                    break;
                }

                {//搜索模式单选框操作分析
                case UID_SearchMode:
                    {
                        if (SendMessage(ChoseButton1, BM_GETCHECK, NULL, NULL) == BST_CHECKED)  //进行精确查找
                        {
                        SendMessage(Label2, WM_SETTEXT, NULL, (LPARAM)L"文件名：");
                        }
                        if (SendMessage(ChoseButton2, BM_GETCHECK, NULL, NULL) == BST_CHECKED)  //进行模糊查找
                        {
                            SendMessage(Label2, WM_SETTEXT, NULL, (LPARAM)L"关键字：");
                        }
                    }
                    break;
                }

                case UID_FileList:
                {
                    switch (wNotifyCode)
                    {
                        //文件列表操作分析
                        case LBN_DBLCLK:
                        {
                            wchar_t RootPath_w[PATH_LONG];
                            char RootPath[PATH_LONG];

                            WORD Cursel = SendMessage(FileList, LB_GETCURSEL, NULL, NULL);
                            SendMessage(FileList, LB_GETTEXT, Cursel, (LPARAM)RootPath_w);

                            WCtoMB(RootPath_w, RootPath, sizeof(RootPath) / sizeof(RootPath[0]));

                            if (OpenClipboard()) return -1;

                            wchar_t Msg[PATH_LONG + 23];
                            
                            {//将文件路径复制到剪贴板
                                EmptyClipboard();   //清空剪贴板

                                //分配全局内存
                                HGLOBAL hMem;
                                hMem = GlobalAlloc(GMEM_MOVEABLE, strlen(RootPath) + 1);

                                if (hMem == NULL)
                                {
                                    CloseClipboard();
                                    return -1;
                                }

                                //拷贝数据到剪贴板内存
                                LPTSTR lpStr = (LPTSTR)GlobalLock(hMem);

                                strcpy_s((char*)lpStr, strlen(RootPath) + 1, RootPath);

                                GlobalUnlock(hMem);

                                //设置数据到剪贴板
                                SetClipboardData(CF_TEXT, hMem);

                                //关闭剪贴板
                                CloseClipboard();

                                wcscpy_s(Msg, RootPath_w);
                                wcscat_s(Msg, L"\n（已复制到剪贴板）\n要打开文件所在位置吗？");
                            }
                            

                            if (MessageBox(hWnd, Msg, L"位置", MB_OKCANCEL) == MB_OK)
                            {
                                HWND handle = NULL;
                                ShellExecute(handle, L"explore", RootPath_w, NULL, NULL, SW_SHOWNORMAL);
                            }
                            
                            break;
                        }
                                                                        
                    default:
                        break;
                    }
                    
                    
                }            
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_3DFACE + 1)); //填充背景颜色

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_CLOSE:  //关闭窗口键
        if (MessageBox(hWnd, L"确定要退出吗？", L"注意", MB_OKCANCEL) == IDOK)
        {
            DestroyWindow(hWnd);
        }
        break;
    case WM_DESTROY://摧毁窗口
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Help(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);

    switch (message)
    {
    case WM_CLOSE:
        EndDialog(hDlg, LOWORD(wParam));
        return (INT_PTR)TRUE;
        break;

    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Setting(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);

    switch (message)
    {
    case WM_PAINT:
    {
        ShowHidden_CheckBox = CreateWindowEx               //创建“搜索根目录”静态文本框
        (
            0,
            CheckBox_CLASS_NAME,
            L"搜索隐藏文件（夹）",
            (WS_CHILD | WS_VISIBLE | BS_CHECKBOX),
            10, 10, 150, 25,
            hDlg,
            (HMENU)UID_ShowHidden,
            Instance,
            NULL
        );
        CreatCheck(ShowHidden_CheckBox, 2);

        if (ShowHidden)
        {
            SendMessage(ShowHidden_CheckBox, BM_SETCHECK, BST_CHECKED, NULL);
        }
        break;
    }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);

        switch (wmId)
        {
            case UID_ShowHidden:
            {
                if (SendMessage(ShowHidden_CheckBox, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
                {
                    ShowHidden = 0;
                    SendMessage(ShowHidden_CheckBox, BM_SETCHECK, BST_UNCHECKED, NULL);
                }
                else
                {
                    ShowHidden = 1;
                    SendMessage(ShowHidden_CheckBox, BM_SETCHECK, BST_CHECKED, NULL);
                }
            }
        }
        break;
    }    
    case WM_CLOSE:
        EndDialog(hDlg, LOWORD(wParam));
        return (INT_PTR)TRUE;
        break;

    }
    return (INT_PTR)FALSE;
}
