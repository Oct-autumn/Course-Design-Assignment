#pragma once

#define PATH_LONG 1024

#include <stdio.h>
#include <io.h>
#include <string.h>


int Sum = 0;    //文件计数全局变量
int DfsFolder(char path[PATH_LONG + 1], char filename[FILENAME_MAX], int layer, int type);//深度遍历文件目录
int FindFile_1(char path[PATH_LONG + 1], char filename[FILENAME_MAX], int layer);//在当前目录层内精确文件查找
int FindFile_2(char path[PATH_LONG + 1], char filename[FILENAME_MAX], int layer);//在当前目录层内模糊文件查找
void PrintOut(char path[PATH_LONG + 1], char filename[FILENAME_MAX]);//输出函数

int DfsFolder(char path[PATH_LONG+1], char filename[FILENAME_MAX], int layer,int type)   //深度遍历文件目录函数
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

    char current_path[PATH_LONG+1];//当前正在遍历的目录
    strcpy_s(current_path, path);

    strcat_s(current_path, "*"); //用\*来匹配所有

    int handle = _findfirst(current_path, &file_info);  //文件句柄变量

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
                strcpy_s(path_NEW, path); //获取查找路径

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

    long handle = _findfirst(findingPath, &file_info); //文件句柄变量
    if (-1 == handle)
    {
        return 0;
    }
    else
    {
        if (strcmp(file_info.name, "..") != 0 && strcmp(file_info.name, ".") != 0)
        {
            PrintOut(path, file_info.name);
            Sum++; //总文件计数加一
            LayerFiles++;   //该层目录内文件数加一
        }
        

        while (!_findnext(handle, &file_info))
        {
            if (strcmp(file_info.name, "..") != 0 && strcmp(file_info.name, ".") != 0)
            {
                PrintOut(path, file_info.name);
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

    long handle = _findfirst(findingPath, &file_info); //文件句柄变量
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
                PrintOut(path, file_info.name);
                Sum++; //总文件计数加一
                LayerFiles++;   //该层目录内文件数加一
                
            }
        } while (!_findnext(handle, &file_info));
    }

    _findclose(handle);

    return LayerFiles;
}//当前目录层内模糊文件查找函数

void PrintOut(char path[PATH_LONG + 1], char filename[FILENAME_MAX])
{
    printf("%d: %s", Sum, path);
    printf("%s\n", filename);
}