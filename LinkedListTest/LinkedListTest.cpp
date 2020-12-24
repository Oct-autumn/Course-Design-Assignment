#include <stdio.h>		//标准输入输出库
#include <stdlib.h>		//标准库
#include <string.h>		//字符串库

#define PATH_LONG 1024		//路径字符串的最长长度

typedef struct linkNode		//定义链表节点类
{
	public:
		//指向上一节点的指针
		linkNode* before;
		//数据区
		char filepath[PATH_LONG];
		//指向下一节点的指针
		linkNode* next;
};

linkNode* NewNode(const char filepath_save[PATH_LONG], linkNode* BeforeNode, linkNode* NextNode);	//预定义 创建新节点函数
void DeleteNode(linkNode* Node_todelete);														//预定义 删除节点函数
linkNode* TraverseFind(linkNode* head, long untilposi);											//预定义 查找节点函数

int main()		//主函数
{
	linkNode* Head = NULL;			//链表头指针
	linkNode* BeforeNode = NULL;	//前一个链表节点的指针
	linkNode* NextNode = NULL;		//后一个链表节点的指针

	//以下为新建链表的过程
	Head = NewNode("Hello", NULL, NULL);				//创建链表头节点
	BeforeNode = Head;									//继承链表头的指针
	BeforeNode = NewNode("World", BeforeNode, NULL);	//新建节点
	BeforeNode = NewNode("!", BeforeNode, NULL);		//新建节点

	//以下为查找特定链表项并输出的过程
	long i = 2;											//要查找的项目标号
	if (!TraverseFind(Head, i))							//检查标号是否会使链表溢出
	{
		printf("Error: Linked list overflow!\n");
		return 0;
	}
	printf("%s\n", TraverseFind(Head, i)->filepath);	//输出

	DeleteNode(TraverseFind(Head, 2));
	if (!TraverseFind(Head, i))							//检查标号是否会使链表溢出
	{
		printf("Error: Linked list overflow!\n");
		return 0;
	}
	printf("%s\n", TraverseFind(Head, i)->filepath);	//输出

	return 0;
}

linkNode* NewNode(const char filepath_save[PATH_LONG], linkNode* BeforeNode, linkNode* NextNode) //预定义 创建新节点函数
{
	linkNode* p = (linkNode*)malloc(sizeof(linkNode));				//新建节点并为之分配内存空间

	if (p == NULL) exit(-1);										//检查是否创建成功

	strcpy_s(p->filepath, filepath_save);							//将内容存储到新节点里
	
	//进行索引
	if (BeforeNode) BeforeNode->next = p;							//若前一项存在，则向前一项添加索引
	p->before = BeforeNode;										//新节点的前索引
	p->next = NextNode;											//新节点的后索引
	if (NextNode) NextNode->before = p;								//若后一项存在，则向后一项添加索引

	return p;														//返回新节点的内存指针
}

void DeleteNode(linkNode* Node_todelete)	//预定义 删除节点函数
{
	linkNode* beforeNode = Node_todelete->before;	//找到上一节点
	linkNode* nextNode = Node_todelete->next;		//找到下一节点
	
	//进行索引
	beforeNode->next = nextNode;
	nextNode->before = beforeNode;

	//删除节点释放内存
	free(Node_todelete);

	return ;
}

linkNode* TraverseFind(linkNode* head, long untilposi)	//预定义 查找节点函数
{
	linkNode* p = head;			//获取头节点指针
	long posi = 1;				//位置

	while (posi != untilposi)	//在截止编号前运行
	{
		if (p != NULL)	//确认不是链表尾部
		{
			posi++;				//位置加一
			p = p->next;		//向后移一位继续遍历
			continue;			//下一次循环
		}
		return NULL;			//未找到（链表溢出）时，返回空指针
	}
	
	return p;					//返回查找到的节点的指针
}