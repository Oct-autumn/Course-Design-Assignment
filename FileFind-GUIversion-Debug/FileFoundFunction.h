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

int DfsFolder(char path[PATH_LONG + 1], char filename[FILENAME_MAX], int layer, int type)   //��ȱ����ļ�Ŀ¼����
{
    int LayerFiles = 0;
    
    wcscpy_s(ProgramStatus, L"����������");
    wcscat_s(ProgramStatus, MBtoWC(path));
    SendMessage(Status, WM_SETTEXT, NULL, (LPARAM)ProgramStatus);

    switch (type)
    {
    case 1:LayerFiles = FindFile_1((char*)path, (char*)filename, layer); break;
    case 2:LayerFiles = FindFile_2((char*)path, (char*)filename, layer); break;
    default:
        return -1;
    }

    _finddata_t file_info;  //�ļ���Ϣ����

    char current_path[PATH_LONG + 1];//��ǰ���ڱ�����Ŀ¼
    strcpy_s(current_path, (char*)path);

    strcat_s(current_path, "*"); //��\*��ƥ������

    intptr_t handle = _findfirst(current_path, &file_info);  //�ļ��������

    if (-1 == handle)//������ֵΪ-1����Ϊ����һ��Ŀ¼
    {
        return LayerFiles;
    }

    do
    {
        if (strcmp(file_info.name, "..") != 0 && strcmp(file_info.name, ".") != 0)//.�ǵ�ǰĿ¼��..���ϲ�Ŀ¼�������ų������������
        {
            if (file_info.attrib == _A_SUBDIR)//�ж��Ƿ�Ϊ��Ŀ¼
            {
                char path_NEW[PATH_LONG + 1];
                strcpy_s(path_NEW, (char*)path); //��ȡ����·��

                strcat_s(path_NEW, file_info.name);//��windows�¿�����ת��ָ��������Ƽ�
                strcat_s(path_NEW, "\\");

                DfsFolder(path_NEW, filename, layer + 1, type);//�ݹ������Ŀ¼
            }
        }
    } while (!_findnext(handle, &file_info));//����0���������

    //�ر��ļ����

    _findclose(handle);

    return LayerFiles;
}


int FindFile_1(char path[PATH_LONG + 1], char filename[FILENAME_MAX], int layer)
{
    int LayerFiles = 0;
    _finddata_t file_info;  //�ļ���Ϣ����

    char findingPath[PATH_LONG + 1 + FILENAME_MAX];
    strcpy_s(findingPath, path);
    strcat_s(findingPath, filename);

    intptr_t handle = _findfirst(findingPath, &file_info); //�ļ��������

    if (-1 == handle)
    {
        return 0;
    }
    else
    {
        if (strcmp(file_info.name, "..") != 0 && strcmp(file_info.name, ".") != 0)
        {
            AddFilePath(path, file_info.name);
            Sum++; //���ļ�������һ
            LayerFiles++;   //�ò�Ŀ¼���ļ�����һ
        }

        while (!_findnext(handle, &file_info))
        {
            if (strcmp(file_info.name, "..") != 0 && strcmp(file_info.name, ".") != 0)
            {
                AddFilePath(path, file_info.name);
                Sum++; //���ļ�������һ
                LayerFiles++;   //�ò�Ŀ¼���ļ�����һ
            }
        }
    }

    _findclose(handle);

    return LayerFiles;
}//��ǰĿ¼���ھ�ȷ�ļ����Һ���

int FindFile_2(char path[PATH_LONG + 1], char filename[FILENAME_MAX], int layer)
{
    int LayerFiles = 0;
    _finddata_t file_info;  //�ļ���Ϣ����

    char findingPath[PATH_LONG + 1 + FILENAME_MAX];
    strcpy_s(findingPath, path);
    strcat_s(findingPath, "*");//ƴ�ӡ�*����ƥ����������

    intptr_t handle = _findfirst(findingPath, &file_info); //�ļ��������
    if (-1 == handle)
    {
        return 0;
    }
    else
    {
        do
        {
            if (strstr(file_info.name, filename))   //ƥ��ؼ���
            {
                AddFilePath(path, file_info.name);
                Sum++; //���ļ�������һ
                LayerFiles++;   //�ò�Ŀ¼���ļ�����һ

            }
        } while (!_findnext(handle, &file_info));
    }

    _findclose(handle);

    return LayerFiles;
}//��ǰĿ¼����ģ���ļ����Һ���

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