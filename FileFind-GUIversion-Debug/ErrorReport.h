#pragma once

int CreatCheck(HWND hwnd, int ErrorCode)
{
    if (hwnd == NULL)
    {
        switch (ErrorCode)
        {
        case 1:MessageBox(hwnd, L"Could not create the MainWindow.E-001",
            L"Error", MB_OK | MB_ICONERROR); break;
        case 2:MessageBox(hwnd, L"Could not create the Label1.E-002",
            L"Error", MB_OK | MB_ICONERROR); break;
        case 3:MessageBox(hwnd, L"Could not create the TextBox1.E-003",
            L"Error", MB_OK | MB_ICONERROR); break;
        case 4:MessageBox(hwnd, L"Could not create the Label2.E-004",
            L"Error", MB_OK | MB_ICONERROR); break;
        case 5:MessageBox(hwnd, L"Could not create the TextBox2.E-005",
            L"Error", MB_OK | MB_ICONERROR); break;
        case 6:MessageBox(hwnd, L"Could not create the FileList.E-006",
            L"Error", MB_OK | MB_ICONERROR); break;
        case 7:MessageBox(hwnd, L"Could not create the CheckBox1.E-007",
            L"Error", MB_OK | MB_ICONERROR); break;
        case 8:MessageBox(hwnd, L"Could not create the CheckBox2.E-008",
            L"Error", MB_OK | MB_ICONERROR); break;
        }
        return 0;
    }
    return 1;
}

int ExchCheck(int result, int ErrorCode)
{
    if (result)
    {
        switch (ErrorCode)
        {
        case 1:MessageBox(hwnd, L"Cannot be converted to multi-byte encoding.E-101",
            L"Error", MB_OK | MB_ICONERROR); break;
        case 2:MessageBox(hwnd, L"Cannot convert to wide character encoding.E-102",
            L"Error", MB_OK | MB_ICONERROR); break;

        }
        return 0;
    }
    return 1;
}
