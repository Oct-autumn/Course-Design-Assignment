#pragma once

int CreatCheck(HWND hwnd,int ErrorCode)
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
        }
        return 0;
    }
    return 1;
}

