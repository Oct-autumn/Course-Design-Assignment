/*
可移植库，用于转换多字节字符串与宽字符字符串

Programmed by Oct_Autumn
*/
#pragma once

#include <Windows.h>

bool WCtoMB(wchar_t* WideChar, char* MultiBite, DWORD Bites);
bool MBtoWC(char* MultiBite, wchar_t* WideChar, DWORD Bites);

bool WCtoMB(wchar_t* WideChar, char* MultiBite, DWORD Bites)
{
    DWORD MinBite = WideCharToMultiByte(CP_ACP, 0, WideChar, -1, NULL, 0, NULL, FALSE);

    if (Bites < MinBite) return true;

    WideCharToMultiByte(CP_ACP, 0, WideChar, -1, MultiBite, Bites, NULL, FALSE);

    return false;
}

char* WCtoMB(wchar_t* WideChar)
{
    DWORD MinBite = WideCharToMultiByte(CP_ACP, 0, WideChar, -1, NULL, 0, NULL, FALSE);
    char MultiBite[2048];

    if ((sizeof(MultiBite)) / sizeof(WideChar[0]) < MinBite) return 0;

    WideCharToMultiByte(CP_ACP, 0, WideChar, -1, MultiBite, sizeof(MultiBite) / sizeof(WideChar[0]), NULL, FALSE);

    return MultiBite;
}

bool MBtoWC(char* MultiBite, wchar_t* WideChar, DWORD Bites)
{
    DWORD MinBite = MultiByteToWideChar(CP_OEMCP, 0, MultiBite, -1, NULL, 0);

    if (Bites < MinBite) return true;

    MultiByteToWideChar(CP_OEMCP, 0, MultiBite, -1, WideChar, Bites);

    return false;
}

wchar_t* MBtoWC(char* MultiBite)
{
    DWORD MinBite = MultiByteToWideChar(CP_OEMCP, 0, MultiBite, -1, NULL, 0);
    wchar_t WideChar[2048];

    if ((sizeof(WideChar)) / sizeof(WideChar[0]) < MinBite) return 0;

    MultiByteToWideChar(CP_OEMCP, 0, MultiBite, -1, WideChar, sizeof(WideChar) / sizeof(WideChar[0]));

    return WideChar;
}