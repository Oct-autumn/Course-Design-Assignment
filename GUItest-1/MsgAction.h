#pragma once
static HINSTANCE Instance;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)     //������
{
    switch (uMsg)
    {
    case WM_CREATE:
    {
        Label1 = CreateWindowEx     //������������Ŀ¼����̬�ı���
        (
            0,
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
        
        TextBox_RootPath = CreateWindowEx     //������������Ŀ¼���ı��༭��
        (
            WS_EX_CLIENTEDGE,
            TextBox_CLASS_NAME,
            L"",
            (WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL),
            10, 35, 400, 25,
            hwnd,
            (HMENU)UID_TextBox_RootPath,
            Instance,
            NULL
        );
        CreatCheck(TextBox_RootPath, 3);

        Label2 = CreateWindowEx     //�������ļ�������̬�ı���
        (
            0,
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

        TextBox_FileName = CreateWindowEx     //�������ļ������ı��༭��
        (
            WS_EX_CLIENTEDGE,
            TextBox_CLASS_NAME,
            L"",
            (WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL),
            10, 85, 200, 25,
            hwnd,
            (HMENU)UID_TextBox_FileName,
            Instance,
            NULL
        );
        CreatCheck(TextBox_FileName, 5);

        Start_Search = CreateWindowEx     //��������ʼ��������ť
        (
            0,
            Button_CLASS_NAME,
            L"��ʼ����",
            (WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT),
            300, 70, 100, 40,
            hwnd,
            (HMENU)UID_StartSearch,
            Instance,
            NULL
        );
        CreatCheck(TextBox_FileName, 5);
        
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