#pragma once

#define PATH_LONG 4096

#include <stdio.h>
#include <io.h>
#include <string.h>

#include <stdlib.h>

#include "linkNode.h"   //链表操作定义



int Sum = 0;                    //文件计数全局变量
char ShowHidden = 0;            //显示隐藏文件与否

int FindFile_1(char path[PATH_LONG + 1], char filename[FILENAME_MAX], int layer);
int FindFile_2(char path[PATH_LONG + 1], char filename[FILENAME_MAX], int layer);
void AddFilePath(char path[PATH_LONG + 1], char filename[FILENAME_MAX], linkNode* head);

int DfsFolder(char path[PATH_LONG + 1], char filename[FILENAME_MAX], int layer, int type)   //深度遍历文件目录函数
{
    int LayerFiles = 0;
    switch (type)
    {
    case 1:LayerFiles = FindFile_1(path, filename, layer); break;
    case 2:LayerFiles = FindFile_2(path, filename, layer); break;
    default:
        return -1;
    }

    _finddata_t file_info;  //文件信息变量

    char current_path[PATH_LONG + 1];//当前正在遍历的目录
    strcpy_s(current_path, path);

    strcat_s(current_path, "*"); //用\*来匹配所有

    intptr_t handle = _findfirst(current_path, &file_info);  //文件句柄变量

    if (-1 == handle)//若返回值为-1则认为无下一级目录
    {
        return LayerFiles;
    }

    do
    {
        if (strcmp(file_info.name, "..") != 0 && strcmp(file_info.name, ".") != 0 && (file_info.attrib & _A_SUBDIR))//.是当前目录，..是上层目录，必须排除掉这两种情况 并 判断是否为子目录
        {
            if (ShowHidden == '1')
            {
                char path_NEW[PATH_LONG + 1];
                strcpy_s(path_NEW, path); //获取查找路径

                strcat_s(path_NEW, file_info.name);//在windows下可以用转义分隔符，不推荐
                strcat_s(path_NEW, "\\");

                DfsFolder(path_NEW, filename, layer + 1, type);//递归遍历子目录
            }
            else
            {
                if (!(file_info.attrib & _A_HIDDEN))
                {
                    char path_NEW[PATH_LONG + 1];
                    strcpy_s(path_NEW, path); //获取查找路径

                    strcat_s(path_NEW, file_info.name);//在windows下可以用转义分隔符，不推荐
                    strcat_s(path_NEW, "\\");

                    DfsFolder(path_NEW, filename, layer + 1, type);//递归遍历子目录
                }
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
        do
        {
            if (strcmp(file_info.name, "..") != 0 && strcmp(file_info.name, ".") != 0)
            {
                if (ShowHidden == '1')
                {
                    AddFilePath(path, file_info.name, Head);
                    Sum++; //总文件计数加一
                    LayerFiles++;   //该层目录内文件数加一
                }
                else
                {
                    if (!(file_info.attrib & _A_HIDDEN))
                    {
                        AddFilePath(path, file_info.name, Head);
                        Sum++; //总文件计数加一
                        LayerFiles++;   //该层目录内文件数加一
                    }
                }
                
            }
        }while (!_findnext(handle, &file_info));
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
                if (ShowHidden == '1')
                {
                    AddFilePath(path, file_info.name, Head);
                    Sum++; //总文件计数加一
                    LayerFiles++;   //该层目录内文件数加一
                }
                else
                {
                    if (!(file_info.attrib & _A_HIDDEN))
                    {
                        AddFilePath(path, file_info.name, Head);
                        Sum++; //总文件计数加一
                        LayerFiles++;   //该层目录内文件数加一
                    }
                }
            }
        } while (!_findnext(handle, &file_info));
    }

    _findclose(handle);

    return LayerFiles;
}//当前目录层内模糊文件查找函数

void AddFilePath(char path[PATH_LONG + 1], char filename[FILENAME_MAX], linkNode *head)
{
    char filepath[PATH_LONG + FILENAME_MAX + 1];

    strcpy_s(filepath, path);
    strcat_s(filepath, filename);

    BeforeNode = NewNode(filepath, BeforeNode, NULL);
}