#include "Header.h"

int main(void)
{
	/*INT_BTREE BT;
	int x1 = 32, x2 = -17, x3 = 36, x4 = 21;
	initIntBTree(&BT);
	insertIntBST(&BT, x1);
	insertIntBST(&BT, x2);
	insertIntBST(&BT, x3);
	insertIntBST(&BT, x4);
	printIntBTree(BT);
	system("pause");*/
	INT_BTREE BT;
	INT_BTREE BT2;
	//INT_BTREE_NODE* elemento;

	int x1 = 32, x2 = -17, x3 = 36, x4 = 21;
	int x[] = { 32, -7, 16, 21, 12, 8, 42, 33, 12, 39, 12, 45 };
	int i = 0;

	initIntBTree(&BT);
	insertIntBST(&BT, x1);
	insertIntBST(&BT, x2);
	insertIntBST(&BT, x3);
	insertIntBST(&BT, x4);
	//printIntBTree(BT);

	//printf("\n\n Segunda Arvore:\n");

	initIntBTree(&BT2);
	for (i = 0; i < 12; i++)
		insertIntBST(&BT2, x[i]);

	printIntBTree(BT2);

	//system("pause");
	printf("\n\nProcurar o elemento:\n");
	//i = pesquisaIntBTpos(BT2, 12); //funciona mal para elementos iguais
	printf("12 -> posicao: %d", i);
	//int depth = 
	printf("\n\ndepth: ");
	//printf("\n\nDepth: %d", );
	system("pause");
}

//main() {
//	int *d = (int*)malloc(sizeof(int));
//	BTREE bst=NULL;
//	*d = 12;
//	searchBST(bst, d, &ComparaInts);
//}