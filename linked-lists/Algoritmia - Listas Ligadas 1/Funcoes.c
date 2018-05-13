#include "Header.h"

/*****************************************************************************************************************************************************
* Cria um no'
*
* Parametros: data - apontador generico para os dados a inserir no no' criado
* Saida: apontador para o no' criado ou NULL em caso de erro
***************************************************************/
LIST_NODE *NewNode(void *data)
{
	LIST_NODE *new_node;
	if ((new_node = (LIST_NODE *)malloc(sizeof(LIST_NODE))) != NULL)
	{
		DATA(new_node) = data;
		NEXT(new_node) = NULL;
	}
	return(new_node);
}
/****************************************************************
* Insere um no' no inicio da lista
*
* Parametros: list - apontador para lista
* (duplo apontador para o primeiro no')
* data - apontador generico para os dados a inserir no no' criado
* Saida: apontador para o no' inserido (primeiro no' da lista)
***************************************************************/
LIST_NODE *InsertIni(LIST *list, void *data)
{
	LIST_NODE *new_node;
	if ((new_node = NewNode(data)) != NULL)
	{
		NEXT(new_node) = *list;
		*list = new_node;
	}
	return(new_node);      //new_node é igual a *list 
}
/****************************************************************
* Insere um no' no fim da lista
*
* Parametros: list - apontador para lista
* (duplo apontador para o primeiro no')
* data - apontador generico para os dados a inserir no no' criado
* Saida: apontador para o no' inserido (ultimo no' da lista)
***************************************************************/
LIST_NODE *InsertEnd(LIST *list, void *data)
{
	LIST_NODE *new_node, *temp;          //temp é do tipo LIST ou seja LIST_NODE *
	if ((new_node = NewNode(data)) != NULL)
	{
		if (*list == NULL)
			*list = new_node;
		else
		{
			temp = *list;
			while (NEXT(temp) != NULL)
				temp = NEXT(temp);
			NEXT(temp) = new_node;
		}
	}
	return(new_node);       //new_node é o endereço de memoria da lista (inicio da lista como os vetores)
}
/***************************************************************************
* Funcao: calcula quantos elementos contem a lista
* Parametros:
* list - apontador para uma lista
* Saida: numero de elementos da lista
***************************************************************************/
int ListSize(LIST list)
{
	int count = 0;
	while (list != NULL)
	{
		count++;
		list = NEXT(list);
	}
	return count;
}
/****************************************************************
* Escreve no ecra o conteudo da lista e retorna o seu tamanho
*
* Parametros: list - apontador para o primeiro no'
* Saida: numero de no's da lista
***************************************************************/
int ShowValues(LIST list)
{
	int n_nodes = 0;
	printf("LISTA ->");
	while (list != NULL)
	{
		printf(" %s;%d ->", ((ALUNO *)DATA(list))->nome, ((ALUNO *)DATA(list))->idade);
		list = NEXT(list);
		n_nodes++;
	}
	printf(" FIM");
	return(n_nodes);       //tbm faz a contagem
}


int findAluno(LIST L, char * nome) {   //ALUNO*

	LIST_NODE *paux = L;
	int pos = 0; //tirar

	while (paux != NULL && strcmp(((ALUNO*)paux->data)->nome, nome)) {
		pos++;  //tirar
		paux = paux->next;
	}

	if (paux == NULL) return (-1);  //return NULL
	return(pos);   //return ((ALUNO*)paux->data):
}


void deleteElemento(LIST *pl, char * nome) {
	LIST_NODE *paux = *pl, *ant = *pl;

	while (paux != NULL && strcmp(((ALUNO*)paux->data)->nome, nome)) {
		ant = paux;
		paux = paux->next;
	}

	if (paux == NULL) {                //chegou ao fim da lista ou não tem elementos
		printf("Elemento não encontrado.\n");
		return;
	}
	else {
		if (paux == *pl)              //alterar a lista:
			*pl = (*pl)->next;        //quando é o primeiro elemento
		else
			ant->next = paux->next;   //para outros elementos
	}
	free(paux->data);
	free(paux);
}


void deletefirst(LIST *pl) {
	LIST_NODE *paux=*pl;

	if (paux == NULL) return;

	*pl = paux->next;

	free(paux->data);
	free(paux);
}

void deleteList(LIST *pl)
{
	while (*pl != NULL) {
		deletefirst(pl);  //O(n)+c
	}
	return;
}

void deleteList2(LIST *pl)  //2*O(n)
{
	int i, size = ListSize(*pl);  //o(n)

	for (i = 0;i < size;i++) {
		deletefirst(pl);  //O(n)+c
	}
	return;
}

LIST_NODE* getAdress(LIST L, int p) {
	LIST paux=L;
	int i = 1;
	while (i < p && paux !=NULL) {
		paux = paux->next;
		i++;
	}
	//for (int i = 1, LIST paux=L; i < p && paux != NULL; i++, paux = paux->next); nao dá no compilador	
	//for (i = 1; i < p && paux != NULL; i++)
		//paux = paux->next;
	if (paux == NULL) return NULL;
	return (paux);
}

int readMembersFile(LIST *pLM, LIST *plB, char * fName) {
	FILE *fp;
	int i = 0, offset;
	MEMBER *paux=pLM;
	BOOK *baux;

	fp = fopen(fName, "r"); if (!fp) return(ERROR);

	while (!feof(fp)) {
		fscanf(fp, "%d;%[^;];%d\n", &(paux->number), paux->name, &offset);
		paux->loan = (BOOK*)((getAdress(&plB, offset))->data);
		InsertEndList(pLM, paux);
		i++;
	}
	fclose(fp);
	return(i);
}


int readBooksFile(LIST *pl) {
	FILE *fp;
	int i = 0;

	BOOK *baux;

	fp = fopen("livros.txt", "r"); 
	if (!fp) return(ERROR);

	while (!feof(fp)) {
		baux = (BOOK*)malloc(sizeof(BOOK));
		fscanf(fp, "%[^;];%[^;];%d\n", baux->author, baux->title, baux->loan);
		InsertEnd(pl, baux);
		i++;
	}
	fclose(fp);
	return(i);
}

int readBooksFile2(LIST *pl, char *fName) {
	FILE *fp;
	int i = 0;

	BOOK *paux;

	fp = fopen(fName, "r");
	if (!fp) return(ERROR);

	while (!feof(fp)) {
		paux = (BOOK*)malloc(sizeof(BOOK));
		fscanf(fp, "%[^;];%[^;];%d\n", paux->author, paux->title, paux->loan);
		InsertEnd(pl, paux);
		i++;
	}
	fclose(fp);
	return(i);
}


void printMemberList(LIST LM) {
	LIST_NODE * paux = LM;
	char straux[100] = {'\0'};

	while (paux != NULL) {
		if (((MEMBER*)(paux->data))->loan == NULL) strcpy(straux, "Nao tem um requisitado");
		else { 
		strcpy(straux, "Livro: "); 
		strcat(straux, (((MEMBER*)paux->data))->loan->title); 
		}

		printf("%d;%[^;];%d\n->", ((MEMBER*)(paux->data))->number);
		paux = paux->next;  ((MEMBER*)(paux->data), straux);
	}
}