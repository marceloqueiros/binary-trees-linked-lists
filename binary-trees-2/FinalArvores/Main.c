#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Binary.h"

int main (void)
{
	INT_BTREE BT; // Árvore Binária de Inteiros; 
	
	//---------------Variáveis para o "case"---------------//
	int case1 = 0, case2 = 0, case3 = 0, caseA = 0, caseB = 0, caseB2 = 0, caseC = 0, caseD = 0, caseE = 0, caseF = 0, caseG = 0, caseG2 = 0;
	// Para testar a função de Pesquisa e a função de obter o Pai de um Nó;
	INT_BTREE_NODE *caseE2 = NULL, *caseF2 = NULL;
	// Para testar a função de Unir duas Árvores Binárias;
	INT_BTREE case9;

	int c = 0; 
	BOOLEAN sair = FALSE;
	// ---------------------------------------------------//

	// Inicializar Árvores Binárias;
	initIntBTree(&BT);
	initIntBTree(&case9);

	do
	{
        fprintf (stdout, "\n0 -- Sair");
        fprintf (stdout, "\n1 -- Inserir na Raiz");
        fprintf (stdout, "\n2 -- Inserir Vertice");
		fprintf (stdout, "\n3 -- Eliminar Vertice"); // Completar;
        fprintf (stdout, "\n4 -- Percorrer Arvore Binaria (PreOrder)");
		fprintf (stdout, "\n5 -- Percorrer Arvore Binaria (InOrder)");
		fprintf (stdout, "\n6 -- Percorrer Arvore Binaria (PostOrder)");
		fprintf (stdout, "\n7 -- Rodar a Direita");
		fprintf (stdout, "\n8 -- Rodar a Esquerda");
        fprintf (stdout, "\n9 -- Unir duas Arvores Binarias");
		fprintf (stdout, "\nA -- Contar Nos");
		fprintf (stdout, "\nB -- Contar Numero de Repeticoes (No)");
		fprintf (stdout, "\nC -- Obter Valor Maximo");
		fprintf (stdout, "\nD -- Obter Valor Minimo");
		fprintf (stdout, "\nE -- Pesquisar Elemento (No)");
		fprintf (stdout, "\nF -- Obter Pai (No)");
		fprintf (stdout, "\nG -- Obter Nivel de Profundidade (No)");
        
        fprintf (stdout, "\nOpcao: ");
		fflush(stdin);
        c = getchar();
		while ( '\n' != getchar());

        switch (c) 
		{
            case '0': 
				sair = TRUE;
				break;
            case '1':
				fprintf(stdout, "Que valor deseja inserir na raiz da Arvore Binaria? \n");
				fscanf(stdin,"%d", &case1);

				insertRootBSTree(&BT, case1);
				break;
			case '2':
				fprintf(stdout, "Que valor deseja inserir na Arvore Binaria? \n");
				fscanf(stdin,"%d", &case2);

				insertIntBST(&BT, case2);
				break;
			case '3':
				fprintf(stdout, "Que no deseja eliminar? \n");
				fscanf(stdin, "%d", &case3);

				if (deleteNode(&BT, case3) == OK)
					fprintf(stdout, "O No foi eliminado! \n");
				else
					fprintf(stdout, "Esse valor nao existe! \n");
				break;
			case '4':
				if (printIntBTreePreOrder(BT) == ERROR)
					fprintf(stdout, "\nA Arvore esta vazia!\n");
				break;
			case '5':
				if (printIntBTreeInOrder(BT) == ERROR)
					fprintf(stdout, "\nA Arvore esta vazia!\n");
				break;
			case '6':
				if (printIntBTreePostOrder(BT) == ERROR)
					fprintf(stdout, "\nA Arvore esta vazia!\n");
				break;
			case '7':
				if (rotateRight(&BT) == ERROR)
					fprintf(stdout, "\nNao foi possivel rodar a Arvore pois ja nao possui Filho da Esquerda!\n");
				break;
			case '8':
				if (rotateLeft(&BT) == ERROR)
					fprintf(stdout, "\nNao foi possivel rodar a Arvore pois ja nao possui Filho da Direita!\n");
				break;
			case '9':
				//---Valores de Teste:---//
				insertIntBST(&case9, 4);
				insertIntBST(&case9, 2);
				insertIntBST(&case9, 6);
				insertIntBST(&case9, 3);
				insertIntBST(&case9, 1);
				insertIntBST(&case9, 5);
				insertIntBST(&case9, 7);
				//----------------------//

				if (joinBST(&BT, &case9) == ERROR)
					fprintf(stdout, "\nErro ao unir as Arvores, ambas estao vazias!\n");
				break;
			case 'A':
				caseA = countBST(BT);
				fprintf(stdout, "A Arvore contem %d nos! \n", caseA);
				break;
			case 'B':
				fprintf(stdout, "De que valor quer procurar repeticoes? \n");
				fscanf(stdin, "%d", &caseB);

				caseB2 = countRepeatedIntBSTreeNode(BT, caseB);
				fprintf(stdout, "O valor repete-se %d vezes! \n", caseB2);
				break;
			case 'C':
				caseC = getMaxInt(&BT);

				if (caseC == INT_MIN)
					fprintf(stdout, "A Arvore esta vazia! \n");
				else
					fprintf(stdout, "O maior valor presente na arvore e: %d! \n", caseC);
				break;
			case 'D':
				caseD = getMinInt(&BT);

				if (caseD == INT_MAX)
					fprintf(stdout, "A Arvore esta vazia! \n");
				else
					fprintf(stdout, "O menor valor presente na arvore e: %d! \n", caseD);
				break;
			case 'E':
				fprintf(stdout, "Que valor deseja procurar? \n");
				fscanf(stdin, "%d", &caseE);

				caseE2 = searchBST (&BT, caseE);

				if (caseE2 != NULL)
					fprintf(stdout, "O valor existe! \n");
				else
					fprintf(stdout, "O valor nao existe! \n");
				break;
			case 'F':
				fprintf(stdout, "De que valor pretende saber se tem pai? \n");
				fscanf(stdin, "%d", &caseF);

				caseF2 = getParent (&BT, caseF);

				if (caseF2 != NULL)
					fprintf(stdout, "O No possui um pai com o valor %d! \n", DATA(caseF2));
				else
					fprintf(stdout, "O No nao possui um pai! \n");
				break;
			case 'G':
				fprintf(stdout, "De que valor pretende saber a profundidade? \n");
				fscanf(stdin, "%d", &caseG2);

				caseG = getBSTNodeDepth (&BT, caseG2);
				if (caseG == -1)
					fprintf(stdout, "A Arvore esta vazia! \n");
				else
					if (caseG == -2)
						fprintf(stdout, "O No nao existe! \n");
					else
						fprintf(stdout, "O No esta no nivel %d ! \n", caseG);
				break;
		}
	} while (sair != TRUE);
	return 0;
}