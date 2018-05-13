#include "stdafx.h"
#include "Header.c"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

//------------------------------------------

#define DATA(node)  ((node)->data)
#define LEFT(node)   ((node)->left)
#define RIGHT(node)  ((node)->right)
#define EMPTY         NULL
#define NO_LINK      NULL

//-------------------------------------------

typedef enum _STATUS { OK, ERROR } STATUS;
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef struct _INT_BTREE_NODE {
	int data;
	struct _INT_BTREE_NODE *left;
	struct _INT_BTREE_NODE *right;
} INT_BTREE_NODE;
typedef INT_BTREE_NODE *INT_BTREE;

//-------------------------------------------

STATUS createNewIntBTNode(INT_BTREE_NODE **, int);
STATUS initIntBTree(INT_BTREE *);
BOOLEAN emptyIntBTree(INT_BTREE);
void printIntBTree(INT_BTREE);
BOOLEAN isLeaf(INT_BTREE_NODE *);
STATUS insertIntBST(INT_BTREE *, int);

//-------------------------------------------
STATUS initIntBTree(INT_BTREE *pBT)
{
	*pBT = NULL;
	return OK;
}
//-------------------------------------------
BOOLEAN emptyIntBTree(INT_BTREE BT)
{
	return (BT == NULL) ? TRUE : FALSE;
}
//-------------------------------------------
BOOLEAN isLeaf(INT_BTREE_NODE *pBT)
{
	return ((LEFT(pBT) == NULL) && (RIGHT(pBT) == NULL)) ?
		TRUE : FALSE;
}
//-------------------------------------------
STATUS insertIntBST(INT_BTREE *pBT, int data)
{
	if (emptyIntBTree(*pBT))
	{
		INT_BTREE_NODE *pNew;
		if (createNewIntBTNode(&pNew, data) == ERROR)
			return ERROR;
		*pBT = pNew;
		return OK;
	}
	else if (data<DATA(*pBT)) insertIntBST(&(LEFT(*pBT)
		), data);
	else insertIntBST(&(RIGHT(*pBT)), data);
	return OK;
}
//-------------------------------------------
void printIntBTree(INT_BTREE BT)
{
	INT_BTREE pTemp = BT;
	if(emptyIntBTree(pTemp) == TRUE) return;
	printIntBTree(LEFT(pTemp));
	printf("%d ,  ", DATA(pTemp));
	printIntBTree(RIGHT(pTemp));
	return;
}
//-------------------------------------------
STATUS createNewIntBTNode(INT_BTREE_NODE **pNew, int
	data)
{
	INT_BTREE_NODE *pTemp;
	if ((pTemp = (INT_BTREE_NODE *)malloc(sizeof(INT_BTREE_NODE))) == NULL)
		return ERROR;
	*pNew = pTemp;
	DATA(pTemp) = data;
	LEFT(pTemp) = NULL;
	RIGHT(pTemp) = NULL;
	return OK;
}

int countNodesBT2(INT_BTREE b) {
	static int c = 0;
	if (b == NULL) return c;
	c = countNodesBT2(LEFT(b));
	c++;
	c = countNodesBT2(RIGHT(b));

	return c;
}


int CountNodesBT(INT_BTREE b, int c) {
	if (b==NULL) return c;
	c = CountNodesBT(LEFT(b),c);
	c++;
	c = CountNodesBT(RIGHT(b),c);

	return (c);
}
//-------------------------------------------
//Exemplo de aplicação :
int main(void)
{
	INT_BTREE BT;
	int x1 = 32, x2 = -17, x3 = 36, x4 = 21;
	initIntBTree(&BT);
	insertIntBST(&BT, x1);
	insertIntBST(&BT, x2);
	insertIntBST(&BT, x3);
	insertIntBST(&BT, x4);
	printIntBTree(BT);
	return 0;
}