// PARA TREINAR:
// 1) Fun��o para determinar e apresentar os n�meros Pares e Impares presentes numa �rvore Bin�ria;
// 2) Fun��o para eliminar em simult�neo todos os elementos de uma BST;
// 3) Fun��o para imprimir no ecr� todos os valores superiores a um certo n�mero numa �rvore Bin�ria;

#ifndef BINARYH
#define BINARYH

//-----Macros-----//
#define DATA(node) ((node)->data)
#define LEFT(node) ((node)->left)
#define RIGHT(node) ((node)->right)
#define EMPTY NULL
#define NO_LINK NULL
//-----Estruturas-----//
typedef enum _STATUS {OK,ERROR} STATUS;
typedef enum _BOOLEAN {FALSE=0, TRUE=1} BOOLEAN;

typedef struct _INT_BTREE_NODE 
{
	int data;
	struct _INT_BTREE_NODE *left;
	struct _INT_BTREE_NODE *right;
} INT_BTREE_NODE;

typedef INT_BTREE_NODE *INT_BTREE;
//-----Fun��es-----//
STATUS initIntBTree(INT_BTREE*);
BOOLEAN emptyIntBTree(INT_BTREE);
BOOLEAN isLeaf(INT_BTREE_NODE*);
STATUS createNewIntBTNode(INT_BTREE_NODE**, int);
STATUS insertIntBST(INT_BTREE*, int);
STATUS printIntBTreePreOrder(INT_BTREE);
STATUS printIntBTreeInOrder(INT_BTREE);
STATUS printIntBTreePostOrder(INT_BTREE);
STATUS rotateRight(INT_BTREE_NODE**);
STATUS rotateLeft(INT_BTREE_NODE**);
int countBST (INT_BTREE);
int countRepeatedIntBSTreeNode(INT_BTREE, int);
INT_BTREE_NODE* searchBST (INT_BTREE*, int);
int getMaxInt (INT_BTREE*);
int getMinInt (INT_BTREE*);
INT_BTREE_NODE* getParent (INT_BTREE*, int);
STATUS insertRootBSTree (INT_BTREE*, int);
STATUS deleteNode (INT_BTREE*, int);
STATUS joinBST (INT_BTREE*, INT_BTREE*);
int getBSTNodeDepth (INT_BTREE*, int);

#endif