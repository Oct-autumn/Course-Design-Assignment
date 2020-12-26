#pragma once

#include <stdio.h>
#include <string.h>

typedef struct linkNode		//定义链表节点类
{
public:
    //指向上一节点的指针
    linkNode *before;
    //数据区
    char *filepath;
    //指向下一节点的指针
    linkNode *next;
};

static linkNode *Head = NULL;       //定义 静态链表头
static linkNode *BeforeNode = NULL; //定义 前一节点指针
static linkNode *NextNode = NULL;   //定义 后一节点指针

int Sum = 0;                    //文件计数全局变量

linkNode *NewNode(char filePath_tosave[PATH_LONG], linkNode *beforeNode, linkNode *nextNode)
{
    linkNode* Node = (linkNode*)malloc(sizeof(linkNode*)+8);
    if (Node == NULL) exit(-1);

    long MemorySize = sizeof(char) * strlen(filePath_tosave) + 1;
    Node->filepath = (char*)malloc(MemorySize);
    if (Node->filepath == NULL) exit(-1);

    strcpy_s(Node->filepath, MemorySize, filePath_tosave);
    Node->next = NULL;

    if (beforeNode) beforeNode->next = Node;
    Node->before = beforeNode;
    Node->next = nextNode;
    if (nextNode) nextNode->before = Node;

    return Node;
}

linkNode* DeleteLink(linkNode *head)             //删除链表
{
    linkNode *PresentNode = head, *NextNode = NULL;

    while (PresentNode)
    {
        NextNode = PresentNode->next;
        free(PresentNode->filepath);
        free(PresentNode);
        PresentNode = NextNode;
    }

    return NULL;
}

int DeleteNode(linkNode* Node_todelete)     //删除链表中指定节点
{
    if (Node_todelete)
    {
        //重定向先后节点
        Node_todelete->before->next = Node_todelete->next;
        Node_todelete->next->before = Node_todelete->before;
        //删除节点并释放内存
        free(Node_todelete->filepath);
        free(Node_todelete);

        return 0;
    }

    return -1;
}

int DeleteNode(linkNode* head, int number)  //删除链表中指定位置的节点
{
    linkNode* PresentNode = head;
    int Count = 1;

    while (PresentNode)
    {
        if (Count == number)
        {
            //重定向先后节点
            PresentNode->before->next = PresentNode->next;
            PresentNode->next->before = PresentNode->before;
            //删除节点并释放内存
            free(PresentNode);

            return 0;
        }
        Count++;
        PresentNode = PresentNode->next;
    }

    return -1;
}

int printf(linkNode* head)                 //输出链表
{
    linkNode* PresentNode = head->next;
    
    if (PresentNode)
    {
        while (PresentNode)
        {
            printf("%s\n", PresentNode->filepath);
            PresentNode = PresentNode->next;
        }
        return 0;
    }
    
    return -1;
}