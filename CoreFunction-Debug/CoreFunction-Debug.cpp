﻿/*
--版本发布--
**文件查找程序V1.0（当前为CMD控制台版本）**
    该版本程序实现了核心的遍历目录查找文件功能
    支持中文操作
    支持精确查找（文件名查找）、模糊查找（关键字查找）
    支持基于通配符‘ * ’的文件类型查找。

Oct-Autumn——2020 - 12 - 22


--版本更新--
**文件查找程序V1.1（CMD最终发布版）**
    该版本程序在V1.0的基础上进一步：
        实现了基于链表的路径动态暂存功能
        优化了数据结构以压缩内存占用

Oct-Autumn——2020 - 12 - 26


--版本更新--
**文件查找程序V1.2（内部-功能测试版）**
    该版本程序在V1.1的基础上进一步：
        实现了允许用户选择是否搜索隐藏文件

Oct-Autumn——2021 - 01 - 08
*/


#include "Functions.h"

char Func = 0;

int main()
{
MENU_START:
    printf("********************************************\n");
    printf("*           欢迎使用文件查找程序           *\n");
    printf("* 菜单：                                   *\n");
    printf("*     1-精确搜索（可使用通配符“*”）      *\n");
    printf("*     2-模糊搜索（耗时较长）               *\n");
    printf("*                                          *\n");
    printf("*     0-退出                               *\n");
    printf("*                                          *\n");
    printf("* 注意：本程序使用链表存储文件地址，在搜索 *\n");
    printf("*       时会占用部分内存资源               *\n");
    printf("********************************************\n");
    printf("请选择搜索功能：");

    Func = getchar();
    getchar();

    printf("********************************************\n");
    printf("* 是否显示隐藏文件（夹）？                 *\n");
    printf("* 1-是                                     *\n");
    printf("* 0-否                                     *\n");
    printf("********************************************\n");
    printf("请选择：");

    ShowHidden = getchar();
    getchar();

    char path[PATH_LONG + 1];
    char filename[FILENAME_MAX];

    switch (Func)
    {
    case '0':
        return 0;
    case '1':
    {
        //获取搜索路径与文件名
        printf("Please ENTER the Root-Path of Finding:(Example:C:\\windows\\)\n");
        gets_s(path);
        printf("Please ENTER the Name of file:\n");
        gets_s(filename);
        printf("\n");

        //创建暂存链表
        Head = NewNode((char*)"Start", NULL, NULL);
        BeforeNode = Head;

        //清空文件计数并开始搜索
        Sum = 0;
        DfsFolder(path, filename, 0, 1);

        //输出搜索结果并清理资源
        printf("共找到相关文件（夹）%d个\n**************************\n", Sum);
        printf(Head);
        DeleteLink(Head);

        if (Sum == 0) printf("None File was found.\n");
        printf("\n");
        goto MENU_START;
        break;
    }
    case '2':
    {
        //获取搜索路径与文件名
        printf("Please ENTER the Root-Path of Finding:(Example:C:\\windows\\)\n");
        gets_s(path);
        printf("Please ENTER the Key-Word:\n");
        gets_s(filename);
        printf("\n");

        //创建暂存链表
        Head = NewNode((char*)"Start", NULL, NULL);
        BeforeNode = Head;

        //清空文件计数并开始搜索
        Sum = 0;
        DfsFolder(path, filename, 0, 2);

        //输出搜索结果并清理资源
        printf("共找到相关文件（夹）%d个\n*****", Sum);
        printf(Head);
        DeleteLink(Head);

        if (Sum == 0) printf("None File was found.\n");
        printf("\n");
        goto MENU_START;
        break;
    }
    default:goto MENU_START;
    }

    return 0;
}