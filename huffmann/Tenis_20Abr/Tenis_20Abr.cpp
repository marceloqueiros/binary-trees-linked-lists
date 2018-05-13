// Tenis_20Abr.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#define MAX_NAME 20
#define STAGES 15

typedef struct _PLAYER
{
	char name[MAX_NAME];
	int sets;
}PLAYER;

typedef struct _BTREE_NODE
{
	void * data;
	struct _BTREE_NODE * left;
	struct _BTREE_NODE * right;
} BTREE_NODE;

typedef BTREE_NODE * BTREE;
typedef enum _BTREE_LOCATION { BTREE_LEFT, BTREE_RIGHT } BTREE_LOCATION;
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum _STATUS { ERROR = 0, OK = 1 } STATUS;

#define DATA(node) ((node)->data)
#define LEFT(node) ((node)->left)
#define RIGHT(node) ((node)->right)
#define EMPTY NULL
#define NO_LINK NULL
//
//BTREE_NODE * NewBtreeNode(void * data);
//BTREE_NODE * AddBtreeNode(BTREE_NODE * upnode, BTREE_NODE * node, BTREE_LOCATION where);
//int BtreeSize(BTREE btree);
//int BtreeDeep(BTREE btree);
//BOOLEAN BtreeLeaf(BTREE_NODE * node);
//BTREE_NODE * InitNode(void *, BTREE_NODE *, BTREE_NODE *);
//BTREE_NODE * CreateBtree(void **, int, int);
//STATUS ReadPlayersFromFile(void **, char *);
////void PrintLeafs(BTREE);
//void BtreeFree(BTREE);
//void PrintWinnerGames(BTREE);
//int CountTotalSets(BTREE);
//int CountWinnerSets(BTREE, void *);
//void PrintAllGames(BTREE);


BTREE_NODE * NewBtreeNode(void * data)
{
	BTREE_NODE * tmp_pt;
	if ((tmp_pt = (BTREE_NODE *)malloc(sizeof(BTREE_NODE))) != NULL)
	{
		DATA(tmp_pt) = data;
		LEFT(tmp_pt) = RIGHT(tmp_pt) = NULL;
	}
	return tmp_pt;
}



BTREE_NODE * AddBtreeNode(BTREE_NODE * upnode, BTREE_NODE * node, BTREE_LOCATION where)
{
	BTREE_NODE * tmp_pt = upnode;
	if (where == BTREE_LEFT)
	{
		if (LEFT(upnode) == NULL)
			LEFT(upnode) = node;
		else
			tmp_pt = NULL;
	}
	else
	{
		if (RIGHT(upnode) == NULL)
			RIGHT(upnode) = node;
		else
			tmp_pt = NULL;
	}
	return tmp_pt;
}



BTREE_NODE *InitNode(void * ptr_data, BTREE_NODE * node1, BTREE_NODE * node2)
{
	BTREE_NODE * tmp_pt = NULL;
	tmp_pt = NewBtreeNode(ptr_data);
	LEFT(tmp_pt) = node1;
	RIGHT(tmp_pt) = node2;
	return(tmp_pt);
}



BTREE_NODE *CreateBtree(void ** v, int i, int size)
{
	if (i >= size)
		return(NULL);
	else
		return(InitNode(*(v + i), CreateBtree(v, 2 * i + 1, size), CreateBtree(v, 2 * i + 2, size)));
}



void BtreeFree(BTREE btree)
{
	if (btree != NULL)
	{
		BtreeFree(LEFT(btree));
		BtreeFree(RIGHT(btree));
		free(btree);
	}
}

/*Número total de nós*/
int BtreeSize(BTREE btree)
{
	int count = 0;
	if (btree != NULL)
		count = 1 + BtreeSize(LEFT(btree)) + BtreeSize(RIGHT(btree));
	return(count);
}



BOOLEAN BtreeLeaf(BTREE_NODE * btree)
{
	if ((LEFT(btree) == NULL) && (RIGHT(btree) == NULL))
		return(TRUE);
	else
		return(FALSE);
}



int BtreeDeep(BTREE btree)
{
	int deep = 0, left, right;
	if (btree != NULL)
	{
		left = BtreeDeep(LEFT(btree));
		right = BtreeDeep(RIGHT(btree));
		deep = 1 + ((left > right) ? left : right);
	}
	return(deep);
}



STATUS ReadPlayersFromFile(void ** players, char * file_name)
{
	FILE * fp;
	int j, i = 0;
	void * ptr_data;
	if ((fp = fopen(file_name, "r")) != NULL)
	{
		while (!feof(fp))
		{
			if ((ptr_data = malloc(sizeof(PLAYER))) != NULL)
			{
				fscanf(fp, "%[^;];", ((PLAYER *)ptr_data)->name);
				fscanf(fp, "%d\n", &(((PLAYER *)ptr_data)->sets));
				players[i] = ptr_data;
				i++;
			}
			else
			{
				for (j = i; j >= 0; j--)
					free(players[j]);
				return(ERROR);
			}
		}
		fclose(fp);
		return(OK);
	}
	else
		return(ERROR);
}


void PrintLeafs(BTREE btree)
{
	if (LEFT(btree) != NULL)
		PrintLeafs(LEFT(btree));
	if (RIGHT(btree) != NULL)
		PrintLeafs(RIGHT(btree));
	if (LEFT(btree) == NULL && RIGHT(btree))
		printf("%s\n", ((PLAYER *)DATA(btree))->name);
	return;
}



void PrintWinnerGames(BTREE btree)
{
	static char * winner = ((PLAYER *)DATA(btree))->name;
	if (btree == NULL) return;

	if (LEFT(btree) != NULL && RIGHT(btree) != NULL)
	{
		if (strcmp(((PLAYER *)DATA(LEFT(btree)))->name, winner) == 0)
			PrintWinnerGames(LEFT(btree));
		else
			PrintWinnerGames(RIGHT(btree));
		printf("%s-%d VS %s-%d\n", ((PLAYER *)DATA(LEFT(btree)))->name, ((PLAYER *)DATA(LEFT(btree)))->sets, ((PLAYER *)DATA(RIGHT(btree)))->name, ((PLAYER *)DATA(RIGHT(btree)))->sets);
	}
}

int CountTotalSets(BTREE btree)
{
	int Sets=0;//nessecário inicializar senão dá erro no ultimo
	if (btree != NULL)
		Sets = ((PLAYER *)DATA(btree))->sets + CountTotalSets(LEFT(btree)) + CountTotalSets(RIGHT(btree));
	return Sets;
}


int CountWinnerSets(BTREE btree)
{
	int Sets;
	static char * winner = ((PLAYER *)DATA(btree))->name;
	if (btree == NULL) return 0;
	
	if (LEFT(btree) != NULL && RIGHT(btree) != NULL)
	{
		Sets = ((PLAYER *)DATA(btree))->sets;
		if (strcmp(((PLAYER *)DATA(LEFT(btree)))->name, winner) == 0)
			Sets += CountTotalSets(LEFT(btree));
		else
			Sets += CountTotalSets(RIGHT(btree));
	}
	return Sets;
}







void PrintPlayerGames(BTREE btree, void * Player)
{
	char * nomePlayer = ((PLAYER *)Player)->name;
	if (btree == NULL) return;

	if (LEFT(btree) != NULL && RIGHT(btree) != NULL)
	{
		if (strcmp(((PLAYER *)DATA(LEFT(btree)))->name, nomePlayer) == 0) {
			PrintPlayerGames(LEFT(btree), Player);
			printf("%s-%d VS %s-%d\n", ((PLAYER *)DATA(LEFT(btree)))->name, ((PLAYER *)DATA(LEFT(btree)))->sets, ((PLAYER *)DATA(RIGHT(btree)))->name, ((PLAYER *)DATA(RIGHT(btree)))->sets);
		}
		else
			if (strcmp(((PLAYER *)DATA(RIGHT(btree)))->name, nomePlayer) == 0) {
				PrintPlayerGames(RIGHT(btree), Player);
				printf("%s-%d VS %s-%d\n", ((PLAYER *)DATA(LEFT(btree)))->name, ((PLAYER *)DATA(LEFT(btree)))->sets, ((PLAYER *)DATA(RIGHT(btree)))->name, ((PLAYER *)DATA(RIGHT(btree)))->sets);
			}else
			{
				PrintPlayerGames(RIGHT(btree), Player);
				PrintPlayerGames(LEFT(btree), Player);
			}
	}
}

int CountPlayerSets(BTREE btree, void *Player)
{
	int Sets;
	char * nomePlayer = ((PLAYER *)Player)->name;
	if (btree == NULL) return 0;

	if (LEFT(btree) != NULL && RIGHT(btree) != NULL)
	{
		if (strcmp(((PLAYER *)DATA(btree))->name, nomePlayer) == 0)
			Sets = ((PLAYER *)DATA(btree))->sets + CountTotalSets(LEFT(btree)) + CountTotalSets(RIGHT(btree));
	}
	return Sets;
}


void PrintAllGames(BTREE btree)
{
	if (btree == NULL) return;
	if (LEFT(btree) != NULL && RIGHT(btree) != NULL)
	{
		PrintAllGames(LEFT(btree));
		printf("%s-%d VS %s-%d\n", ((PLAYER *)DATA(LEFT(btree)))->name, ((PLAYER *)DATA(LEFT(btree)))->sets, ((PLAYER *)DATA(RIGHT(btree)))->name, ((PLAYER *)DATA(RIGHT(btree)))->sets);
		PrintAllGames(RIGHT(btree));
	}
}

bool ProcurarJogador(BTREE btree, void * Player) {
	bool x = false;
	if (btree == NULL) return false;
	if (LEFT(btree) != NULL && RIGHT(btree) != NULL)
	{
		if (((PLAYER *)DATA(btree))->name==((PLAYER *)Player)->name)
		PrintAllGames(LEFT(btree));
		
		PrintAllGames(RIGHT(btree));
	}
	return x;
}

//void AcrescentarEliminatoria(BTREE btree)
//{
//	if (btree != NULL)
//	{
//		AcrescentarEliminatoria(LEFT(btree));
//		AcrescentarEliminatoria(RIGHT(btree));
//		if (BtreeLeaf(btree))
//			NovoJogo(btree);
//	}
//}
//
//void NovoJogo(BTREE btree)
//{
//	PLAYER * data1, *data2;
//
//	if ((data1 = (PLAYER*)malloc(sizeof(PLAYER))) != NULL)
//	{
//		strcpy(((PLAYER *)data1)->name, ((PLAYER*)DATA(btree))->name);
//		((PLAYER *)data1)->sets = 3;
//	}
//	if ((data2 = (PLAYER*)malloc(sizeof(PLAYER))) != NULL)
//	{
//		printf("Novo Jogador:");
//		strcpy(((PLAYER *)data2)->name, ((PLAYER*)DATA(btree))->name);
//		//scanf("%[^;];", ((PLAYER *)data2)->name);
//		((PLAYER *)data2)->sets = 0;
//	}
//	LEFT(btree) = NewBtreeNode(data1);
//	RIGHT(btree) = NewBtreeNode(data2);
//}
//
//STATUS DeleteLeafs(BTREE btree)
//{
//	if (btree != NULL)
//		DeleteLeafs(LEFT(btree));
//	DeleteLeafs(RIGHT(btree));
//	if (BtreeLeaf)
//		free(btree);
//	return OK;
//}

//int _tmain(int argc, _TCHAR* argv[])
//{
//	BTREE Btree;
//	void * players[STAGES];
//	char file_name[MAX_NAME];
//	printf("Nome do ficheiro: ");
//	//scanf("%s", file_name);
//	strcpy(file_name, "torneio.txt");
//	setlocale(LC_ALL, "Portuguese");
//	if (ReadPlayersFromFile(players, file_name))
//	{
//		Btree = CreateBtree(players, 0, STAGES);
//		printf("\nLista de participantes:\n");
//		PrintLeafs(Btree);
//		printf("\nLista de Jogos:\n");
//		PrintAllGames(Btree);
//		printf("\nNúmero de eliminatórias: %d", BtreeDeep(Btree) - 1);
//		printf("\nNúmero de Jogos: %d", BtreeSize(Btree) / 2);
//		printf("\nNúmero de Sets: %d", CountTotalSets(Btree));
//		printf("\nVencedor do torneio: %s\n", ((PLAYER *)DATA(Btree))->name);
//		printf("\nJogos disputados pelo Vencedor:\n");PrintWinnerGames(Btree);
//		printf("Total de sets do vencedor: %d\n", CountWinnerSets(Btree));
//		char name[MAX_NAME];
//		printf("Nome de um jogador: ");
//		scanf("%s", name);
//		//if ()
//		//printf("\nSets ganhos pelo Vencedor: %d\n", CountWinnerSets(Btree, DATA(Btree)));
//		BtreeFree(Btree);
//		_getch();
//	}
//	else
//		printf("ERRO na leitura do ficheiro\n");
//	_getch();
//	return 0;
//}


//1-calcular frequencias dos simbolos
//2-construir árvore huffman
//3-construir tabela de codigos
//4-codificar
//5-descodificar

typedef struct _HUFFMAN_NODE
{
	char caracter;
	int frequencia;
	struct _HUFFMAN_NODE * left;
	struct _HUFFMAN_NODE * right;
} HUFFMAN_NODE;


STATUS CountFrequencyCharacters(char * file, HUFFMAN_NODE **v[]) {
	FILE *fp;

	fp = fopen(file, "r"); 
	if (fp==NULL) return(ERROR);
	char c;
	while (!feof(fp)) {
		c = fgetc(fp);
		if(c!=-1)
		((*v)[c]->frequencia)++;
	}
	fclose(fp);
	return OK;
}


void OrdenarVetor(HUFFMAN_NODE **v[]) {
	int c, d;
	HUFFMAN_NODE *aux;
	for (c = 0; c < (256 - 1); c++)
	{
		for (d = 0; d < 256 - c - 1; d++)
		{
			if ((*v)[d]->frequencia > (*v)[d+1]->frequencia) 
			{
				aux = (*v)[d];
				(*v)[d] = (*v)[d+1];
				(*v)[d + 1] = aux;
			}
		}
	}
}

HUFFMAN_NODE * ConstruirArvoreHuffman(HUFFMAN_NODE *v[]) {
	HUFFMAN_NODE * head=NULL, *aux1, *aux2;
	int smallerIndex, j=0, i=0;

	for (smallerIndex = 0; smallerIndex<256 && v[smallerIndex]->frequencia == 0; smallerIndex++) {
		i = i;
	}

	while (smallerIndex < 256) {
		head = (HUFFMAN_NODE*)malloc(sizeof(HUFFMAN_NODE));
		head->caracter = 0;
		head->frequencia = v[smallerIndex]->frequencia + v[smallerIndex + 1]->frequencia; 
		head->left = v[smallerIndex];
		head->right = v[smallerIndex+1];
		smallerIndex+=2;
		for (i = smallerIndex; v[smallerIndex]->frequencia < head->frequencia;i++)
			for (j = smallerIndex;j > i;j++)
				v[j - 1] = v[j];
		v[j - 1] = head; smallerIndex--;
	}
	return head;
}

void print_tree(HUFFMAN_NODE *r, int l)
{
	int i;

	if (!r) return;

	print_tree(r->right, l + 1);
	for (i = 0; i<l; ++i) printf(" ");
	printf("%c-%i\n", r->caracter, r->frequencia);
	print_tree(r->left, l + 1);
}

//void CodeCable(HUFFMAN_NODE * ht)

int _tmain(int argc, _TCHAR* argv[])
{
	HUFFMAN_NODE **v;
	v = (HUFFMAN_NODE**)malloc(sizeof(HUFFMAN_NODE)*256);
	for (int i = 0;i < 256;i++) v[i] = (HUFFMAN_NODE*)malloc(sizeof(HUFFMAN_NODE));
	for (int i = 0;i < 256;i++) {
		v[i]->frequencia = 0; v[i]->caracter = i; v[i]->left = NULL; v[i]->right = NULL;
	}

	CountFrequencyCharacters("torneio.txt",&v);

	OrdenarVetor(&v);
	HUFFMAN_NODE *h=ConstruirArvoreHuffman(v);
	print_tree(h,0);
	system("pause");
}