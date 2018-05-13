#include "Header.h"

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


//algoritmo pesquisa BST

INT_BTREE_NODE* pesquisaIntBST(INT_BTREE pBT, int data)
{
	if (emptyIntBTree(pBT))
	{
		return NULL;
	}
	else
	{
		if (data == DATA(pBT)) return pBT;
		else {
			if (data < DATA(pBT)) pesquisaIntBST((LEFT(pBT)), data);
			else pesquisaIntBST((RIGHT(pBT)), data);
		}

	}
}

//algoritmo pesquisa BT
INT_BTREE_NODE* pesquisaIntBT(INT_BTREE pBT, int data)
{
	static INT_BTREE_NODE* posicao = NULL;
	if (emptyIntBTree(pBT) == TRUE || posicao != NULL) return posicao;

	pesquisaIntBT(LEFT(pBT), data);
	if (data == DATA(pBT)) {
		posicao = pBT;
		return posicao;
	}
	pesquisaIntBT(RIGHT(pBT), data);
}

int pesquisaIntBTpos(INT_BTREE BT, int data)
{
	static int c = 0;
	static STATUS f = ERROR;
	if (emptyIntBTree(BT) == TRUE || f == OK) return c;

	c = pesquisaIntBTpos(LEFT(BT), data);
	if (f == ERROR) c++;
	if (data == DATA(BT)) {
		f = OK;
		return c;
	}
	c = pesquisaIntBTpos(RIGHT(BT), data);

	if (f == ERROR) { c = -1; return c; }
}


//-------------------------------------------
void printIntBTree(INT_BTREE BT)
{
	INT_BTREE pTemp = BT;
	//UTAD.Algoritmia.Caderno de Exercícios A03. 3
	if (emptyIntBTree(pTemp) == TRUE) return;
	printf("%d , ", DATA(pTemp));
	printIntBTree(LEFT(pTemp));
	printIntBTree(RIGHT(pTemp));

	return;
}
//-------------------------------------------
STATUS createNewIntBTNode(INT_BTREE_NODE **pNew, int data)
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

//INT_BTREE_NODE * createNewIntBTNode(int data)
//{
//	INT_BTREE_NODE* pTemp;
//	pTemp = (INT_BTREE_NODE *)malloc(sizeof(INT_BTREE_NODE));
//	if (pTemp == NULL) return NULL;
//	DATA(pTemp) = data;
//	LEFT(pTemp) = NULL;
//	RIGHT(pTemp) = NULL;
//
//	return pTemp;
//}

//------------------------------------------- 

int countBT(INT_BTREE BT)
{
	static int c = 0;

	if (emptyIntBTree(BT) == TRUE) return c;
	c = countBT(LEFT(BT));
	c++;
	c = countBT(RIGHT(BT));

	return c;
}




//-------------------------------------------

int CountNodesBT(INT_BTREE b, int c) {
	if (b == NULL) return c;
	c = CountNodesBT(LEFT(b), c);
	c++;
	c = CountNodesBT(RIGHT(b), c);

	return (c);
}

int countNodesBT2(INT_BTREE b) {
	static int c = 0;
	if (b == NULL) return c;
	c = countNodesBT2(LEFT(b));
	c++;
	c = countNodesBT2(RIGHT(b));

	return c;
}

int countFolhas(INT_BTREE b) {
	static int c = 0;
	if (b == NULL) return c;
	c = countNodesBT2(LEFT(b));
	if (LEFT(b) == NULL && RIGHT(b) == NULL) c++;
	c = countNodesBT2(RIGHT(b));

	return c;
}


int countNivelBST(INT_BTREE b, int x) {
	static int depth = 0, flag = 0;
	if (b == NULL) {
		if (flag = 0) {
			depth = -1;
			return depth;
		}
	}
	else
		return depth;


	if (x == DATA(b)) {
		flag = 1;
		return depth;  //chegou ao fim
	}

	if (x == DATA(b)) return depth;
	else{
	if (x < b->data) {
		depth++;
		depth = countNodesBT2(LEFT(b));
	}
	else {
		depth++;
		depth = countNodesBT2(RIGHT(b));
	}
	}
	return depth;
}

int countNivelBT(INT_BTREE b, int x) {
	static int n = 0;
	static STATUS flag = ERROR;
	if (b == NULL && flag == ERROR) {
		n--;
		return n;
	}
	if (flag == OK) return n;

	if (x == DATA(b)) {
		flag = OK;
		return n;
	}

	if (flag == ERROR) {
		n++;
		n = countNivelBT(LEFT(b), x);
	}
	if (flag == ERROR){
		n++;
		n = countNivelBT(RIGHT(b), x);
	}
	if (flag == ERROR) n--;
	return n;
}

//int profundidadeArvore(INT_BTREE b) {
//	static int N = 0, n1 = 0, n2 = 0;
//	static STATUS flag = ERROR, flag = 0;
//	
//	if (b == NULL) flag == OK;
//
//	if (b != NULL && flag == ERROR){
//		n1 = profundidadeArvore(LEFT(b));
//		n1++;
//		flag = 1;
//	}
//	if (b != NULL && flag == ERROR && flag ==0) {
//		n2 = profundidadeArvore(RIGHT(b));
//		n2++;
//	}
//
//	if (n1 > n2) N = n1;
//	else N = n2;
//
//	return N;
//}

int profArvore(INT_BTREE b) {
	int maxE, maxD;

	if (b == NULL) return ;

	maxE = profArvore(LEFT(b) + 1);
	maxD = profArvore(RIGHT(b) + 1);

		return (maxE > maxD) ? maxE : maxD;
}

STATUS searchBST(BTREE bst, void *data, int(*pf)(void*, void*)) {
	static STATUS f = ERROR;

	if (bst == NULL || f == OK) return f;

	if (!pf(data, DATA(bst))) { f = OK; return f; }
	else if (pf(data, DATA(bst)) < 0)
		searchBST(LEFT(bst), data, pf);
	else
		searchBST(RIGHT(bst), data, pf);
	return f;
}


int ComparaInts(void *d1, void *d2) {
	if ((*(int*)d1) == (*(int*)d2)) return 0;
	else if ((*(int*)d1) < (*(int*)d2)) return -1;
	else return 1;
}

//contar folhas
//determinar nivel de um elemento
//determinar profundidade árvore
//eliminar árvore (+ conteúdo)
