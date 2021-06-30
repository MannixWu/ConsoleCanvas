/*
 * @Author: your name
 * @Date: 2021-05-23 21:13:40
 * @LastEditTime: 2021-06-28 15:23:03
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \myCanvas\mytest.c
 */
/**************************************************************************************
 * @Author       : your name
 * @Date         : 2021-05-23 21:13:40
 * @LastEditTime : 2021-06-01 22:15:15
 * @LastEditors  : Please set LastEditors
 * @Description  : In User Settings Edit
 * @FilePath     : \vscodeProject\cProject\mytest.c
 **************************************************************************************/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#define MAXSIZE 100

typedef struct
{
	int data[MAXSIZE];
	int length;
} SeqList;

SeqList *initList()
{
	SeqList *L = malloc(sizeof(SeqList));
	L->length = 0;
	return L;
}
int insertList(SeqList *L, int i, int x)
{
	if (L->length == MAXSIZE)
	{
		printf("表满");
		return -1;
	}
	if (i < 0 || i > L->length + 1)
	{
		printf("位置错");
		return 0;
	}
	for (int j = L->length - 1; j >= i; j--)
	{
		L->data[j + 1] = L->data[j];
	}
	L->data[i] = x;
	L->length++;
	return 1;
}
int deleteList(SeqList *L, int i)
{
	if (i < 0 || i >= L->length)
	{
		printf("位置错");
		return 0;
	}
	int result = L->data[i];
	for (int j = i; j <= L->length; j++)
	{
		L->data[j] = L->data[j + 1];
	}
	L->length--;
	return result;
}
int pushList(SeqList *L, int x)
{
	return insertList(L, L->length, x);
}
int popList(SeqList *L)
{
	return deleteList(L, L->length - 1);
}
int shiftList(SeqList *L)
{
	return deleteList(L, 0);
}
int unshiftList(SeqList *L, int x)
{
	return insertList(L, 0, x);
}
int showList(SeqList *L)
{
	printf("\n线性表元素为:\n");
	for (int i = 0; i < L->length; i++)
	{
		if (!(i % 5) && i)
		{
			printf("\n");
		}
		printf("%d\t", L->data[i]);
	}
	printf("\n数组长度为:\t%d\n", L->length);
	return 1;
}
void logInt(int num)
{
	printf("log:\t%d\n", num);
}
int main()
{
	// SeqList *L = initList();
	// insertList(L, 0, 22);
	// insertList(L, 0, 33);
	// for (int i = 0; i < 10; i++)
	// {
	// 	pushList(L, i);
	// }
	// showList(L);
	// logInt(popList(L));
	// logInt(shiftList(L));
	// pushList(L, 44);
	// unshiftList(L, 55);
	// showList(L);
	for(int y = 0;y<5;y++){
		for (int x = 0; x<5;x++){
			if(x==3){
				break;
			}
			printf("%d:%d\t",x,y);
		}
		printf("\n");
	}
	system("pause");
}