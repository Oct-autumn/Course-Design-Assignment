#pragma once

#define PATH_LONG 1024

#include <stdio.h>
#include <io.h>
#include <string.h>


int Sum = 0;    //�ļ�����ȫ�ֱ���
int DfsFolder(char path[PATH_LONG + 1], char filename[FILENAME_MAX], int layer, int type);//��ȱ����ļ�Ŀ¼
int FindFile_1(char path[PATH_LONG + 1], char filename[FILENAME_MAX], int layer);//�ڵ�ǰĿ¼���ھ�ȷ�ļ�����
int FindFile_2(char path[PATH_LONG + 1], char filename[FILENAME_MAX], int layer);//�ڵ�ǰĿ¼����ģ���ļ�����
void PrintOut(char path[PATH_LONG + 1], char filename[FILENAME_MAX]);//�������

int DfsFolder(char path[PATH_LONG+1], char filename[FILENAME_MAX], int layer,int type)   //��ȱ����ļ�Ŀ¼����
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

    char current_path[PATH_LONG+1];//��ǰ���ڱ�����Ŀ¼
    strcpy_s(current_path, path);

    strcat_s(current_path, "*"); //��\*��ƥ������

    int handle = _findfirst(current_path, &file_info);  //�ļ��������

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
                strcpy_s(path_NEW, path); //��ȡ����·��

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

    long handle = _findfirst(findingPath, &file_info); //�ļ��������
    if (-1 == handle)
    {
        return 0;
    }
    else
    {
        if (strcmp(file_info.name, "..") != 0 && strcmp(file_info.name, ".") != 0)
        {
            PrintOut(path, file_info.name);
            Sum++; //���ļ�������һ
            LayerFiles++;   //�ò�Ŀ¼���ļ�����һ
        }
        

        while (!_findnext(handle, &file_info))
        {
            if (strcmp(file_info.name, "..") != 0 && strcmp(file_info.name, ".") != 0)
            {
                PrintOut(path, file_info.name);
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

    long handle = _findfirst(findingPath, &file_info); //�ļ��������
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
                PrintOut(path, file_info.name);
                Sum++; //���ļ�������һ
                LayerFiles++;   //�ò�Ŀ¼���ļ�����һ
                
            }
        } while (!_findnext(handle, &file_info));
    }

    _findclose(handle);

    return LayerFiles;
}//��ǰĿ¼����ģ���ļ����Һ���

void PrintOut(char path[PATH_LONG + 1], char filename[FILENAME_MAX])
{
    printf("%d: %s", Sum, path);
    printf("%s\n", filename);
}