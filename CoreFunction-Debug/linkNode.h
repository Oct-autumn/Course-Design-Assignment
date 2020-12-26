#pragma once

#include <stdio.h>
#include <string.h>

typedef struct linkNode		//��������ڵ���
{
public:
    //ָ����һ�ڵ��ָ��
    linkNode *before;
    //������
    char *filepath;
    //ָ����һ�ڵ��ָ��
    linkNode *next;
};

static linkNode *Head = NULL;       //���� ��̬����ͷ
static linkNode *BeforeNode = NULL; //���� ǰһ�ڵ�ָ��
static linkNode *NextNode = NULL;   //���� ��һ�ڵ�ָ��

int Sum = 0;                    //�ļ�����ȫ�ֱ���

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

linkNode* DeleteLink(linkNode *head)             //ɾ������
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

int DeleteNode(linkNode* Node_todelete)     //ɾ��������ָ���ڵ�
{
    if (Node_todelete)
    {
        //�ض����Ⱥ�ڵ�
        Node_todelete->before->next = Node_todelete->next;
        Node_todelete->next->before = Node_todelete->before;
        //ɾ���ڵ㲢�ͷ��ڴ�
        free(Node_todelete->filepath);
        free(Node_todelete);

        return 0;
    }

    return -1;
}

int DeleteNode(linkNode* head, int number)  //ɾ��������ָ��λ�õĽڵ�
{
    linkNode* PresentNode = head;
    int Count = 1;

    while (PresentNode)
    {
        if (Count == number)
        {
            //�ض����Ⱥ�ڵ�
            PresentNode->before->next = PresentNode->next;
            PresentNode->next->before = PresentNode->before;
            //ɾ���ڵ㲢�ͷ��ڴ�
            free(PresentNode);

            return 0;
        }
        Count++;
        PresentNode = PresentNode->next;
    }

    return -1;
}

int printf(linkNode* head)                 //�������
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