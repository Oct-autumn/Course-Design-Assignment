#pragma once

#define PATH_LONG 4096

#include <stdio.h>
#include <io.h>
#include <string.h>

#include <stdlib.h>

#include "linkNode.h"   //�����������



int Sum = 0;                    //�ļ�����ȫ�ֱ���
char ShowHidden = 0;            //��ʾ�����ļ����

int FindFile_1(char path[PATH_LONG + 1], char filename[FILENAME_MAX], int layer);
int FindFile_2(char path[PATH_LONG + 1], char filename[FILENAME_MAX], int layer);
void AddFilePath(char path[PATH_LONG + 1], char filename[FILENAME_MAX], linkNode* head);

int DfsFolder(char path[PATH_LONG + 1], char filename[FILENAME_MAX], int layer, int type)   //��ȱ����ļ�Ŀ¼����
{
    int LayerFiles = 0;
    switch (type)
    {
    case 1:LayerFiles = FindFile_1(path, filename, layer); break;
    case 2:LayerFiles = FindFile_2(path, filename, layer); break;
    default:
        return -1;
    }

    _finddata_t file_info;  //�ļ���Ϣ����

    char current_path[PATH_LONG + 1];//��ǰ���ڱ�����Ŀ¼
    strcpy_s(current_path, path);

    strcat_s(current_path, "*"); //��\*��ƥ������

    intptr_t handle = _findfirst(current_path, &file_info);  //�ļ��������

    if (-1 == handle)//������ֵΪ-1����Ϊ����һ��Ŀ¼
    {
        return LayerFiles;
    }

    do
    {
        if (strcmp(file_info.name, "..") != 0 && strcmp(file_info.name, ".") != 0 && (file_info.attrib & _A_SUBDIR))//.�ǵ�ǰĿ¼��..���ϲ�Ŀ¼�������ų������������ �� �ж��Ƿ�Ϊ��Ŀ¼
        {
            if (ShowHidden == '1')
            {
                char path_NEW[PATH_LONG + 1];
                strcpy_s(path_NEW, path); //��ȡ����·��

                strcat_s(path_NEW, file_info.name);//��windows�¿�����ת��ָ��������Ƽ�
                strcat_s(path_NEW, "\\");

                DfsFolder(path_NEW, filename, layer + 1, type);//�ݹ������Ŀ¼
            }
            else
            {
                if (!(file_info.attrib & _A_HIDDEN))
                {
                    char path_NEW[PATH_LONG + 1];
                    strcpy_s(path_NEW, path); //��ȡ����·��

                    strcat_s(path_NEW, file_info.name);//��windows�¿�����ת��ָ��������Ƽ�
                    strcat_s(path_NEW, "\\");

                    DfsFolder(path_NEW, filename, layer + 1, type);//�ݹ������Ŀ¼
                }
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
        do
        {
            if (strcmp(file_info.name, "..") != 0 && strcmp(file_info.name, ".") != 0)
            {
                if (ShowHidden == '1')
                {
                    AddFilePath(path, file_info.name, Head);
                    Sum++; //���ļ�������һ
                    LayerFiles++;   //�ò�Ŀ¼���ļ�����һ
                }
                else
                {
                    if (!(file_info.attrib & _A_HIDDEN))
                    {
                        AddFilePath(path, file_info.name, Head);
                        Sum++; //���ļ�������һ
                        LayerFiles++;   //�ò�Ŀ¼���ļ�����һ
                    }
                }
                
            }
        }while (!_findnext(handle, &file_info));
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
                if (ShowHidden == '1')
                {
                    AddFilePath(path, file_info.name, Head);
                    Sum++; //���ļ�������һ
                    LayerFiles++;   //�ò�Ŀ¼���ļ�����һ
                }
                else
                {
                    if (!(file_info.attrib & _A_HIDDEN))
                    {
                        AddFilePath(path, file_info.name, Head);
                        Sum++; //���ļ�������һ
                        LayerFiles++;   //�ò�Ŀ¼���ļ�����һ
                    }
                }
            }
        } while (!_findnext(handle, &file_info));
    }

    _findclose(handle);

    return LayerFiles;
}//��ǰĿ¼����ģ���ļ����Һ���

void AddFilePath(char path[PATH_LONG + 1], char filename[FILENAME_MAX], linkNode *head)
{
    char filepath[PATH_LONG + FILENAME_MAX + 1];

    strcpy_s(filepath, path);
    strcat_s(filepath, filename);

    BeforeNode = NewNode(filepath, BeforeNode, NULL);
}