#pragma once
static HINSTANCE Instance;
static char ProgramStatus[1024];

#include "Functions-1.h"	//�ں�ר�к���

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)     //������
{
    switch (uMsg)
    {
    case WM_CREATE:
    {
        Label1 = CreateWindow     //������������Ŀ¼����̬�ı���
        (
            Label_CLASS_NAME,
            L"������Ŀ¼��",
            (WS_CHILD | WS_VISIBLE),
            10, 10, 150, 25,
            hwnd,
            (HMENU)UID_Label1,
            Instance,
            NULL
        );
        CreatCheck(Label1, 2);

        TextBox_RootPath = CreateWindow     //������������Ŀ¼���ı��༭��
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

        Label2 = CreateWindow     //�������ļ�������̬�ı���
        (
            Label_CLASS_NAME,
            L"�ļ�����",
            (WS_CHILD | WS_VISIBLE),
            10, 60, 100, 25,
            hwnd,
            (HMENU)UID_Label2,
            Instance,
            NULL
        );
        CreatCheck(Label2, 4);

        TextBox_FileName = CreateWindow     //�������ļ������ı��༭��
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

        Start_Search = CreateWindow     //��������ʼ��������ť
        (
            Button_CLASS_NAME,
            L"��ʼ����",
            (WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT),
            360, 70, 100, 40,
            hwnd,
            (HMENU)UID_StartSearch,
            Instance,
            NULL
        );
        CreatCheck(TextBox_FileName, 5);

        FileList = CreateWindow         //�����ļ���ַ�б�
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

        ChoseButton1 = CreateWindow     //��������ȷ���ҡ���ѡ��
        (
            CheckBox_CLASS_NAME,
            L"��ȷ����",
            (WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON | WS_GROUP),
            230, 70, 125, 25,
            hwnd,
            (HMENU)UID_SearchMode,
            Instance,
            NULL
        );
        CreatCheck(ChoseButton1, 7);

        ChoseButton2 = CreateWindow     //������ģ�����ҡ���ѡ��
        (
            CheckBox_CLASS_NAME,
            L"ģ������",
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
        SendMessage(Status, WM_SETTEXT, NULL, (LPARAM)L"����.");

        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    case WM_COMMAND:
    {
        
        int wmEvent = HIWORD(wParam);
        switch (LOWORD(wParam)) 
        {
        case UID_StartSearch:  //���°�ť
            //��ʾ��ʾ
            if (MessageBox(hwnd, L"������ʼ����\nע�⣬�����ڼ䲻����ֹ\n��ʼ������", L"��ʾ", MB_OKCANCEL) == IDOK)
            {
                TCHAR RootPath[256];
                TCHAR FileName[260];
                GetWindowText(TextBox_RootPath, RootPath, 256);
                GetWindowText(TextBox_FileName, FileName, 260);
                
                if (SendMessage(ChoseButton1, BM_GETCHECK, NULL, NULL) == BST_CHECKED)  //���о�ȷ����
                {
                    MessageBox(hwnd, L"��ȷ������ʼ", L"��ʾ", MB_OK);
                    DfsFolder(RootPath, FileName, 0, 1);
                }
                if (SendMessage(ChoseButton2, BM_GETCHECK, NULL, NULL) == BST_CHECKED)  //����ģ������
                {
                    MessageBox(hwnd, L"ģ��������ʼ", L"��ʾ", MB_OK);
                    DfsFolder(RootPath, FileName, 0, 2);
                }
            }

            break;
        case UID_SearchMode:
            if (SendMessage(ChoseButton1, BM_GETCHECK, NULL, NULL) == BST_CHECKED)  //���о�ȷ����
            {
                SendMessage(Label2, WM_SETTEXT, NULL, (LPARAM)L"�ļ�����");
            }
            if (SendMessage(ChoseButton2, BM_GETCHECK, NULL, NULL) == BST_CHECKED)  //����ģ������
            {
                SendMessage(Label2, WM_SETTEXT, NULL, (LPARAM)L"�ؼ��֣�");
            }

            break;
        default:
            //���������Ϣһ��Ҫ���� DefWindowProc ����
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
        if (MessageBox(hwnd, L"ȷ��Ҫ�˳���", L"ע��", MB_OKCANCEL) == IDOK)
        {
            DestroyWindow(hwnd);
        }
        // �������ɶ��û����û��Ӧ
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
        MessageBox(hwnd, L"��ոյ���������ť", L"��ʾ", MB_OK);
        return 0;
    }
    }
}
*/