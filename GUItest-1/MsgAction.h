#pragma once
static HINSTANCE Instance;
static char ProgramStatus[1024];

#include "Functions-1.h"	//内含专有函数

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)     //主窗口
{
    switch (uMsg)
    {
    case WM_CREATE:
    {
        Label1 = CreateWindow     //创建“搜索根目录”静态文本框
        (
            Label_CLASS_NAME,
            L"搜索根目录：",
            (WS_CHILD | WS_VISIBLE),
            10, 10, 150, 25,
            hwnd,
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
            hwnd,
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
            hwnd,
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
            hwnd,
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
            hwnd,
            (HMENU)UID_StartSearch,
            Instance,
            NULL
        );
        CreatCheck(TextBox_FileName, 5);

        FileList = CreateWindow         //创建文件地址列表
        (
            List_CLASS_NAME,
            L"",
            (WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL),
            10, 120, 450, 75,
            hwnd,
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
            hwnd,
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
            hwnd,
            (HMENU)UID_SearchMode,
            Instance,
            NULL
        );
        CreatCheck(ChoseButton2, 8);

        Status = CreateWindow
        (
            STATUSCLASSNAME,
            (PCTSTR)NULL,
            (WS_CHILD | WS_VISIBLE),
            0, 0, 0, 0,
            hwnd,
            (HMENU)UID_StatusBar,
            Instance,
            NULL
        );                   
        
        SendMessage(ChoseButton1, BM_SETCHECK, BST_CHECKED, NULL);
        SendMessage(Status, WM_SETTEXT, NULL, (LPARAM)L"就绪.");

        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    case WM_COMMAND:
    {
        
        int wmEvent = HIWORD(wParam);
        switch (LOWORD(wParam)) 
        {
        case UID_StartSearch:  //按下按钮
            //显示提示
            if (MessageBox(hwnd, L"即将开始搜索\n注意，搜索期间不能终止\n开始搜索吗？", L"提示", MB_OKCANCEL) == IDOK)
            {
                TCHAR RootPath[256];
                TCHAR FileName[260];
                GetWindowText(TextBox_RootPath, RootPath, 256);
                GetWindowText(TextBox_FileName, FileName, 260);
                
                if (SendMessage(ChoseButton1, BM_GETCHECK, NULL, NULL) == BST_CHECKED)  //进行精确查找
                {
                    MessageBox(hwnd, L"精确搜索开始", L"提示", MB_OK);
                    DfsFolder(RootPath, FileName, 0, 1);
                }
                if (SendMessage(ChoseButton2, BM_GETCHECK, NULL, NULL) == BST_CHECKED)  //进行模糊查找
                {
                    MessageBox(hwnd, L"模糊搜索开始", L"提示", MB_OK);
                    DfsFolder(RootPath, FileName, 0, 2);
                }
            }

            break;
        case UID_SearchMode:
            if (SendMessage(ChoseButton1, BM_GETCHECK, NULL, NULL) == BST_CHECKED)  //进行精确查找
            {
                SendMessage(Label2, WM_SETTEXT, NULL, (LPARAM)L"文件名：");
            }
            if (SendMessage(ChoseButton2, BM_GETCHECK, NULL, NULL) == BST_CHECKED)  //进行模糊查找
            {
                SendMessage(Label2, WM_SETTEXT, NULL, (LPARAM)L"关键字：");
            }

            break;
        default:
            //不处理的消息一定要交给 DefWindowProc 处理。
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);;
    }
        
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_3DFACE + 1));

        EndPaint(hwnd, &ps);

        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    case WM_CLOSE:
    {
        if (MessageBox(hwnd, L"确定要退出吗？", L"注意", MB_OKCANCEL) == IDOK)
        {
            DestroyWindow(hwnd);
        }
        // 否则，如果啥都没做就没反应
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

/*
LRESULT CALLBACK Button_StartSearch(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case DLGC_BUTTON:
    {
        MessageBox(hwnd, L"你刚刚点击了这个按钮", L"提示", MB_OK);
        return 0;
    }
    }
}
*/