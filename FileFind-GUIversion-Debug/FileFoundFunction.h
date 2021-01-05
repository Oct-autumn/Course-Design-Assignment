#pragma once

#define PATH_LONG 4096

#include <string.h>
#include <stdlib.h>
#include <cstdio>
#include <io.h>
#include <winnt.h>

#include "WideChar-MultiBite.h"

static wchar_t ProgramStatus[1024];

static long Sum = 0;

int FindFile_1(char path[PATH_LONG + 1], char filename[FILENAME_MAX], int layer);
int FindFile_2(char path[PATH_LONG + 1], char filename[FILENAME_MAX], int layer);
void AddFilePath(char path[PATH_LONG + 1], char filename[FILENAME_MAX]);

int DfsFolder(char path[PATH_LONG + 1], char filename[FILENAME_MAX], int layer, int type)   //深度遍历文件目录函数
{
    int LayerFiles = 0;
    
    wcscpy_s(ProgramStatus, L"正在搜索：");
    wcscat_s(ProgramStatus, MBtoWC(path));
    SendMessage(Status, WM_SETTEXT, NULL, (LPARAM)ProgramStatus);

    switch (type)
    {
    case 1:LayerFiles = FindFile_1((char*)path, (char*)filename, layer); break;
    case 2:LayerFiles = FindFile_2((char*)path, (char*)filename, layer); break;
    default:
        return -1;
    }

    _finddata_t file_info;  //文件信息变量

    char current_path[PATH_LONG + 1];//当前正在遍历的目录
    strcpy_s(current_path, (char*)path);

    strcat_s(current_path, "*"); //用\*来匹配所有

    intptr_t handle = _findfirst(current_path, &file_info);  //文件句柄变量

    if (-1 == handle)//若返回值为-1则认为无下一级目录
    {
        return LayerFiles;
    }

    do
    {
        if (strcmp(file_info.name, "..") != 0 && strcmp(file_info.name, ".") != 0)//.是当前目录，..是上层目录，必须排除掉这两种情况
        {
            if (file_info.attrib == _A_SUBDIR)//判断是否为子目录
            {
                char path_NEW[PATH_LONG + 1];
                strcpy_s(path_NEW, (char*)path); //获取查找路径

                strcat_s(path_NEW, file_info.name);//在windows下可以用转义分隔符，不推荐
                strcat_s(path_NEW, "\\");

                DfsFolder(path_NEW, filename, layer + 1, type);//递归遍历子目录
            }
        }
    } while (!_findnext(handle, &file_info));//返回0则继续遍历

    //关闭文件句柄

    _findclose(handle);

    return LayerFiles;
}


int FindFile_1(char path[PATH_LONG + 1], char filename[FILENAME_MAX], int layer)
{
    int LayerFiles = 0;
    _finddata_t file_info;  //文件信息变量

    char findingPath[PATH_LONG + 1 + FILENAME_MAX];
    strcpy_s(findingPath, path);
    strcat_s(findingPath, filename);

    intptr_t handle = _findfirst(findingPath, &file_info); //文件句柄变量

    if (-1 == handle)
    {
        return 0;
    }
    else
    {
        if (strcmp(file_info.name, "..") != 0 && strcmp(file_info.name, ".") != 0)
        {
            AddFilePath(path, file_info.name);
            Sum++; //总文件计数加一
            LayerFiles++;   //该层目录内文件数加一
        }

        while (!_findnext(handle, &file_info))
        {
            if (strcmp(file_info.name, "..") != 0 && strcmp(file_info.name, ".") != 0)
            {
                AddFilePath(path, file_info.name);
                Sum++; //总文件计数加一
                LayerFiles++;   //该层目录内文件数加一
            }
        }
    }

    _findclose(handle);

    return LayerFiles;
}//当前目录层内精确文件查找函数

int FindFile_2(char path[PATH_LONG + 1], char filename[FILENAME_MAX], int layer)
{
    int LayerFiles = 0;
    _finddata_t file_info;  //文件信息变量

    char findingPath[PATH_LONG + 1 + FILENAME_MAX];
    strcpy_s(findingPath, path);
    strcat_s(findingPath, "*");//拼接‘*’以匹配所有类型

    intptr_t handle = _findfirst(findingPath, &file_info); //文件句柄变量
    if (-1 == handle)
    {
        return 0;
    }
    else
    {
        do
        {
            if (strstr(file_info.name, filename))   //匹配关键字
            {
                AddFilePath(path, file_info.name);
                Sum++; //总文件计数加一
                LayerFiles++;   //该层目录内文件数加一

            }
        } while (!_findnext(handle, &file_info));
    }

    _findclose(handle);

    return LayerFiles;
}//当前目录层内模糊文件查找函数

void AddFilePath(char path[PATH_LONG + 1], char filename[FILENAME_MAX])
{
    char str[PATH_LONG + 1 + FILENAME_MAX];

    strcpy_s(str, path);
    strcat_s(str, filename);

    wchar_t Wstr[PATH_LONG + 1 + FILENAME_MAX];

    MBtoWC(str, Wstr, sizeof(Wstr) / sizeof(Wstr[0]));

    SendMessage(FileList, LB_ADDSTRING, NULL, (LPARAM)Wstr);
}

void CleanFileList()
{
    for (int i = 1; i <= Sum; i++)
    {
        SendMessage(FileList, LB_DELETESTRING, 0, NULL);
    }
}