#include "Functions.h"

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
    printf("********************************************\n");
    printf("请选择搜索功能：");

    char Func = 0;
    Func = getchar();
    getchar();

    char path[PATH_LONG + 1];
    char filename[FILENAME_MAX];

    switch (Func)
    {
    case '0':
        return 0;
    case '1':
        printf("Please ENTER the Root-Path of Finding:(Example:C:\\windows\\)\n");
        gets_s(path);
        printf("Please ENTER the Name of file:\n");
        gets_s(filename);
        printf("\n");

        Sum = 0;
        DfsFolder(path, filename, 0, 1);

        if (Sum == 0) printf("None File was found.\n");
        printf("\n");
        goto MENU_START;
        break;
    case '2':
        printf("Please ENTER the Root-Path of Finding:(Example:C:\\windows\\)\n");
        gets_s(path);
        printf("Please ENTER the Key-Word:\n");
        gets_s(filename);
        printf("\n");

        Sum = 0;
        DfsFolder(path, filename, 0, 2);

        if (Sum == 0) printf("None File was found.\n");
        printf("\n");
        goto MENU_START;
        break;
    default:goto MENU_START;
    }

    return 0;
}