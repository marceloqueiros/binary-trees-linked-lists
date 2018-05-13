#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct _LIST_NODE    //nome temporário
{
	void * data;
	struct _LIST_NODE * next;     //apontador para a propria lista -- tem de ser com o nome temporario porque o permanente só é definido a seguir
} LIST_NODE;             //nome a utilizar durante o código

typedef LIST_NODE * LIST;        // LIST_NODE* = LIST  AGORA LIST_NODE* É EQUIVALENTE A LIST ----> logo isto também por exemplo: LIST_NODE = &LIST

typedef struct _ALUNO
{
	char nome[30];
	int  idade;
}ALUNO;

typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum _LIST_LOCATION { LIST_START, LIST_END } LIST_LOCATION;
typedef enum _STATUS {ERROR = 0, OK = 1} STATUS;

#define DATA(node)  ((node)->data)    //DATA(node) = (node)->data    agora é igual utilizar um ou outro
#define NEXT(node)  ((node)->next)    //NEXT(node) = (node)->next

#define EMPTY    NULL          
#define NO_LINK   NULL    

typedef struct _BOOK {
	char author[50];
	char title[50];
	BOOLEAN loan;
}BOOK;

typedef struct _MEMBER {
	char name[50];
	int number;
	BOOK *loan;
}MEMBER;

LIST_NODE *NewNode(void *data);
LIST_NODE *InsertIni(LIST *list, void *data);
//falta o resto das assinaturas de funções