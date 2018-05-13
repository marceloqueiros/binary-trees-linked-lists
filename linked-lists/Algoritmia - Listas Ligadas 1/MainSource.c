#include "Header.h"
//
///****************************************************************
//* Programa principal
//***************************************************************/
void main(void)
{
	LIST list = NULL;
	ALUNO *ptr_aluno;
	ALUNO al1, al2;
	char nome_aux[30];
	int idade_aux;

	strcpy(al1.nome, "Aluno 1");
	al1.idade = 11;
	strcpy(al2.nome, "Aluno 2");
	al2.idade = 22;

	if (InsertIni(&list, &al1) == NULL)
	{
		printf("\nErro na alocacao de memoria\n");
		printf("\n<Prima qualquer tecla>\n");
		//getch();
		exit(1);
	}
	if (InsertIni(&list, &al2) == NULL)
	{
		printf("\nErro na alocacao de memoria\n");
		printf("\n<Prima qualquer tecla>\n");
		//getch();
		exit(1);
	}
	printf("\n");
	printf("\nTamanho = %d\n", ListSize(list));
	printf("\nALUNOS\n", ShowValues(list));
	printf("\n");
	ptr_aluno = (ALUNO *)malloc(sizeof(ALUNO));
	//printf("Introduza o nome do aluno: ");
	//flushall();
	strcpy(ptr_aluno->nome,"al ptr");
	ptr_aluno->idade=11;
	if (InsertEnd(&list, ptr_aluno) == NULL)
	{
		printf("\nErro na alocacao de memoria\n");
		printf("\n<Prima qualquer tecla>\n");
		//getch();
		exit(1);
	}
	printf("\n");
	printf("\nTamanho = %d\n", ShowValues(list));
	strcpy(((ALUNO *)DATA(list))->nome, "Desconhecido 1");
	//  strcpy(((ALUNO *)(list->data))->nome,"Desconhecido 1");
	((ALUNO *)DATA(list))->idade = 111;
	//  ((ALUNO *)(list->data))->idade = 111;
	((ALUNO *)DATA(NEXT(list)))->idade = 222;
	//  ((ALUNO *)(list->next->data))->idade = 222;
	((ALUNO *)DATA(NEXT(NEXT(list))))->idade = 333;
	//  ((ALUNO *)(list->next->next->data))->idade = 333;
	printf("\n");
	printf("\nTamanho = %d\n", ShowValues(list));

	printf("Posição do aluno 1: %d \n", findAluno(list, "Aluno 1"));

	//Nunca fazer o seguinte segmento de código. Porquê?
	//while (NEXT(list) != NULL)           //o começo da lista perde-se
	//	list = NEXT(list);            //neste caso a lista vai passar a iniciar-se no ultimo elemento e NEXT(list) ficou a apontar pra NULL
	//strcpy(((ALUNO *)DATA(list))->nome, "Desconhecido 3");
	//printf("\n");
	//printf("\nTamanho = %d\n", ShowValues(list));
	//printf("\n<Prima qualquer tecla>\n");
	////getch();
	deleteElemento(&list, "al ptr");
	printf("\nTamanho = %d\n", ShowValues(list));
	system("pause");
}