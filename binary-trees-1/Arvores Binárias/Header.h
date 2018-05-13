#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
//------------------------------------------

typedef struct _NODE_BT
{
	void *data;
	struct _NODE_BT *left;
	struct _NODE_BT *right;
}NODE_BT;

typedef NODE_BT *BTREE;

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
int ComparaInts(void *d1, void *d2);