#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Binary.h"

//---------------Iniciar �rvore Bin�ria de Inteiros---------------//
STATUS initIntBTree(INT_BTREE *pBT)
{
	*pBT = NULL;
	return OK;
}
//---------------Testar se a �rvore Bin�ria de Inteiros est� vazia---------------//
BOOLEAN emptyIntBTree (INT_BTREE BT)
{
	if (BT == NULL)
		return TRUE;
	else
		return FALSE;
}
//---------------Testar se um determinado elemento � folha---------------//
BOOLEAN isLeaf(INT_BTREE_NODE *pBT)
{
	// Se o n� possui um apontador para o n� da esquerda e da direita a "null";
	if ( LEFT(pBT) == NULL &&  RIGHT(pBT) == NULL)
		return TRUE; // Ent�o � uma folha;
	else
		return FALSE;
}
//---------------Criar novo n� para �rvore Bin�ria de Inteiros---------------//
STATUS createNewIntBTNode(INT_BTREE_NODE **pNew, int data)
{
	INT_BTREE_NODE *pTemp;

	// Aloca mem�ria para um novo n� de �rvore Bin�ria;
	if( (pTemp = (INT_BTREE_NODE *) malloc (sizeof(INT_BTREE_NODE))) == NULL)
		return ERROR;
	
	// Cria o novo n�, com o valor passado como par�metro de entrada e com os apontadores para a esquerda/direita a "null";
	*pNew = pTemp;
	DATA(pTemp) = data;
	LEFT(pTemp) = NULL;
	RIGHT(pTemp) = NULL;

	return OK;
}
//---------------Inserir n� na �rvore Bin�ria de Inteiros---------------//
STATUS insertIntBST(INT_BTREE *pBT, int data)
{
	INT_BTREE_NODE *pNew;
	
	if (emptyIntBTree(*pBT)) // Se a �rvore Bin�ria est� vazia;
	{
		// Cria um novo n�;
		if (createNewIntBTNode(&pNew, data) == ERROR)
			return ERROR;

		// � inserido na ra�z da �rvore;
		*pBT = pNew;
		return OK;
	}
	else
		// Como se trata de uma BST, todos os valores menores que a ra�z s�o colocados � esquerda e todos os maiores � direita;
		if (data <= DATA (*pBT)) // Se o valor do n� a inserir for menor que o valor da ra�z;
			insertIntBST( &(LEFT(*pBT)), data); // Uso recursivo da fun��o � esquerda da ra�z;
		else  // Sen�o;
			insertIntBST( &(RIGHT(*pBT)), data); // Uso recursivo da fun��o � direita da ra�z;
	return OK;
}
//---------------Imprimir �rvore Bin�ria de Inteiros percorrendo PreOrder---------------//
STATUS printIntBTreePreOrder(INT_BTREE BT)
{
	INT_BTREE pTemp = BT;

	if (emptyIntBTree(pTemp) == TRUE)
		return ERROR;

	printf("%d - ", DATA(pTemp));
	printIntBTreePreOrder(LEFT(pTemp));
	printIntBTreePreOrder(RIGHT(pTemp));
	return OK;
}
//---------------Imprimir �rvore Bin�ria de Inteiros percorrendo InOrder---------------//
STATUS printIntBTreeInOrder(INT_BTREE BT)
{
	INT_BTREE pTemp = BT;

	if (emptyIntBTree(pTemp) == TRUE) 
		return ERROR;
	
	printIntBTreeInOrder(LEFT(pTemp));
	printf("%d - ",DATA(pTemp));
	printIntBTreeInOrder(RIGHT(pTemp));
	return OK;;
}
//---------------Imprimir �rvore Bin�ria de Inteiros percorrendo PostOrder---------------//
STATUS printIntBTreePostOrder(INT_BTREE BT)
{
	INT_BTREE pTemp = BT;

	if (emptyIntBTree(pTemp) == TRUE)
		return ERROR;

	printIntBTreePostOrder(LEFT(pTemp));
	printIntBTreePostOrder(RIGHT(pTemp));
	printf("%d - ", DATA(pTemp));
	return OK;
}
//---------------Rodar � Direita---------------//
STATUS rotateRight(INT_BTREE_NODE **pBT)
{
	// Auxiliares;
	INT_BTREE_NODE *pTemp, *pAux, *pAux2;

	// Verifica se a �rvore tem valores;
	if (emptyIntBTree(*pBT))
		return ERROR;

	// Se a �rvore n�o possui um Filho da Esquerda;
	if (LEFT(*pBT) == NULL)
		return ERROR; // N�o pode rodar � direita;

	// Filho da Esquerda;
	pAux = LEFT(*pBT);
	// Filho da Direita do Filho da Esquerda;
	pAux2 = RIGHT(LEFT(*pBT));

	// O N� "pTemp" passa a apontar para o Filho da Esquerda da Ra�z;
	pTemp = pAux;
	// A Ra�z passa a ser o Filho da Direita de "pTemp";
	RIGHT(pTemp) = *pBT;
	// O Filho da Direita do Filho da Esquerda da Ra�z passa a ser o Filho da Esquerda do Filho da Direita da Ra�z;
	LEFT(RIGHT(pTemp)) = pAux2;
	// A Ra�z passa a apontar para o mesmo N� que "pTemp" ("pTemp" tornou-se a nova Ra�z);
	*pBT = pTemp;

	return OK;
}
//---------------Rodar � Esquerda---------------//
STATUS rotateLeft(INT_BTREE_NODE **pBT)
{
	// Auxiliares;
	INT_BTREE_NODE *pTemp, *pAux, *pAux2;

	// Verifica se a �rvore tem valores;
	if (emptyIntBTree(*pBT))
		return ERROR;

	// Se a �rvore n�o possui um Filho da Direita;
	if (RIGHT(*pBT) == NULL)
		return ERROR;

	// Filho da Direita;
	pAux = RIGHT(*pBT);
	// Filho da Esquerda do Filho da Direita;
	pAux2 = LEFT(RIGHT(*pBT));

	// O N� "pTemp" passa a apontar para o Filho da Direita da Ra�z;
	pTemp = pAux;
	// A Ra�z passa a ser o Filho da Esquerda de "pTemp";
	LEFT(pTemp) = *pBT;
	// O Filho da Esquerda do Filho da Direita da Ra�z passa a ser o Filho da Direita do Filho da Esquerda da Ra�z;
	RIGHT(LEFT(pTemp)) = pAux2;
	// A Ra�z passa a apontar para o mesmo N� que "pTemp" ("pTemp" tornou-se a nova Ra�z);
	*pBT = pTemp;

	return OK;
}
//---------------Contar N�s---------------//
int countBST (INT_BTREE BT)
{
	int count = 0;
	INT_BTREE pTemp = BT;

	// Se a �rvore est� vazia;
	if (emptyIntBTree(pTemp) == TRUE)
		return count; // Retorna o contador a 0;

	count++; // Incrementa o contador;
	count += countBST(LEFT(pTemp)); // Uso recursivo da fun��o para os n�s � esquerda da ra�z;
	count += countBST(RIGHT(pTemp)); // Uso recursivo da fun��o para os n�s � direita da ra�z;

	return count; // Retorna o contador;
}
//---------------Contar n�mero de repeti��es de um determinado N�---------------//
int countRepeatedIntBSTreeNode(INT_BTREE BT, int N)
{
	int count = 0;
	INT_BTREE pTemp = BT;

	// Se a �rvore est� vazia;
	if (emptyIntBTree(pTemp) == TRUE)
		return count; // Retorna o contador a 0;

	// Se a Ra�z possui o valor procurado;
	if (DATA(pTemp) == N)
		count++; // Incrementa o contador;
		
	count += countRepeatedIntBSTreeNode(LEFT(pTemp), N); // Uso recursivo da fun��o para os n�s � esquerda da ra�z;
	count += countRepeatedIntBSTreeNode(RIGHT(pTemp), N); // Uso recursivo da fun��o para os n�s � direita da ra�z;

	return count; // Retorna o contador;
}
//---------------Pesquisar N�---------------//
INT_BTREE_NODE* searchBST (INT_BTREE *pBT, int data)
{
	INT_BTREE_NODE *pTemp = *pBT;

	// Como se trata de uma BST, todos os valores maiores que a Ra�z est�o na parte direita da �rvore, enquanto os menores est�o na parte da esquerda;
	while (pTemp != NULL && DATA(pTemp) != data) // Enquanto n�o tiver sido percorrida toda a �rvore e encontrado o valor procurado;
	{
		if (DATA(pTemp) > data) // Se o N� atual possuir um valor maior do que aquele procurado;
			pTemp = LEFT(pTemp); // Procura-se no lado esquerdo da �rvore;
		else // Se for menor;
			pTemp = RIGHT(pTemp); // Procura-se no lado direito da �rvore;
	}

	return pTemp; // Retorna o N�;
}
//---------------Obter o M�ximo Valor Presente na �rvore Bin�ria de Inteiros---------------//
int getMaxInt (INT_BTREE *pBT)
{
	INT_BTREE_NODE *pTemp = *pBT;
	// Auxiliar para guardar o maior valor presente na �rvore:
	int maior = INT_MIN;

	// Se a �rvore est� vazia;
	if (emptyIntBTree (*pBT))
		return INT_MIN;

	// Enquanto n�o tiver sido percorrida toda a �rvore:
	while (pTemp != NULL)
	{
		// Se o valor do N� atual for maior que o valor guardado na vari�vel auxiliar;
		if (DATA(pTemp) > maior)
			maior = DATA(pTemp);
		
		// Como se trata de uma BST, todos os valores maiores que a Ra�z (N� verificado na primeira itera��o) est�o na parte direita da �rvore;
		// Procura no lado direito da �rvore (apenas se o N� atual possuir filho da direita, caso contr�rio a fun��o termina);
		pTemp = RIGHT(pTemp);
	}

	return maior;
}
//---------------Obter o M�nimo Valor Presente na �rvore Bin�ria de Inteiros---------------//
int getMinInt (INT_BTREE *pBT)
{
	INT_BTREE_NODE *pTemp = *pBT;
	// Auxiliar para guardar o menor valor presente na �rvore:
	int menor = INT_MAX;

	// Se a �rvore est� vazia;
	if (emptyIntBTree (*pBT))
		return INT_MAX;

	// Enquanto n�o tiver sido percorrida toda a �rvore:
	while (pTemp != NULL)
	{
		// Se o valor do N� atual for menor que o valor guardado na vari�vel auxiliar;
		if (DATA(pTemp) < menor)
			menor = DATA(pTemp);
		
		// Como se trata de uma BST, todos os valores menores que a Ra�z (N� verificado na primeira itera��o) est�o na parte esquerda da �rvore;
		// Procura no lado esquerdo da �rvore (apenas se o N� atual possuir filho da esquerda, caso contr�rio a fun��o termina);
		pTemp = LEFT(pTemp);
	}

	return menor;
}
//---------------Obter Pai de um N�---------------//
INT_BTREE_NODE* getParent (INT_BTREE *pBT, int data)
{
	INT_BTREE_NODE *pTemp = *pBT;
	INT_BTREE_NODE *parent = NULL;
	// Contador auxiliar;
	int aux = 0;

	if (emptyIntBTree(*pBT))
		return NULL;

	// Enquanto n�o tiver sido percorrida toda a �rvore;
	while (pTemp != NULL)
	{
		// Incrementa o contador;
		aux ++;
		// Se encontrou o N�;
		if (DATA(pTemp) == data)
		{
			// Se o contador for igual a 1, quer dizer que encontrou o N� na Ra�z, logo ele n�o possui um N� pai;
			if (aux == 1)
				return NULL;

			// Retorna o N� como sendo o Pai;
			return parent;
		}

		// Coloca o Pai a apontar para o N� atual;
		parent = pTemp;

		// Como se trata de uma BST, todos os valores maiores que a Ra�z est�o na parte direita da �rvore, enquanto os menores est�o na parte da esquerda;
		if (DATA(pTemp) > data) // Se o N� atual possuir um valor maior do que aquele procurado;
			pTemp = LEFT(pTemp); // Procura-se no lado esquerdo da �rvore;
		else
			pTemp = RIGHT(pTemp); // Procura no lado direito da �rvore;
	}

	return NULL;
}
//---------------Inserir na Ra�z---------------//
STATUS insertRootBSTree (INT_BTREE *pBT, int data)
{
	// Vari�vel para guardar o N�, para guardar o seu Pai e Auxiliar para colmatar a falta de atualiza��o da �rvore ap�s a rota��o;
	INT_BTREE_NODE *pAux, *pAux2, *pAux3;
	
	// Insere o N� na �rvore;
	insertIntBST (pBT, data);		
	// Obt�m o N�;
	pAux = searchBST (pBT, data);
	// Obt�m o seu Pai;
	pAux2 = getParent(pBT, data);

	// Enquanto o N� a inserir na Ra�z n�o estiver efetivamente na Ra�z (se a �rvore estiver vazia a fun��o "insertIntBST" insere o N� diretamente na Ra�z);
	while (pAux != *pBT)
	{
		// Se o N� for Filho da Esquerda;
		if (LEFT(pAux2) == pAux)
		{
			rotateRight(&pAux2); // Roda o Pai � Direita;

			// Como a �rvore n�o � atualizada, ap�s a rota��o � direita o antigo Pai (agora o Filho da Direita do N� a colocar na Ra�z) possui 2 Pais:
			// O N� a colocar na Ra�z, que assim se tornou depois da Rota��o da �rvore;
			// E a antiga Ra�z da �rvore, que n�o foi atualizada;
			// Logo, vamos buscar o N� Pai do antigo Pai;
			pAux3 = getParent(pBT, DATA(RIGHT(pAux2)));
			// Se for nulo, o N� j� est� na Ra�z;
			if (pAux3 == NULL)
				// Atualiza-se "*pBT";
				*pBT = pAux2;
			else
				// Se n�o for nulo, existem duas possibilidades;
				// A antiga Ra�z (agora representada por pAux3) possui como Filho da Esquerda o Filho da Direita do N� a colocar na Ra�z (que ainda n�o est� l�);
				if (LEFT(pAux3) == RIGHT(pAux2))
					// Basta dizer que o N� j� rodado � direita � assim Filho da Esquerda da Ra�z;
					LEFT(pAux3) = pAux2;
				else
					// Se n�o, a antiga Ra�z possui como Filho da Direita o Filho da Esquerda do N� a colocar na Ra�z (que ainda n�o est� l�);
					// Basta dizer que o N� j� rodado � direita � assim Filho da Direita da Ra�z;
					RIGHT(pAux3) = pAux2;
			
			pAux2 = getParent(pBT, DATA(pAux)); // Obt�m o novo Pai;
		}
		else
		{
			rotateLeft (&pAux2); // Roda � Esquerda;
			// Como a �rvore n�o � atualizada, ap�s a rota��o � esquerda o antigo Pai (agora o Filho da Esquerda do N� a colocar na Ra�z) possui 2 Pais:
			// O N� a colocar na Ra�z, que assim se tornou depois da Rota��o da �rvore;
			// E a antiga Ra�z da �rvore, que n�o foi atualizada;
			// Logo, vamos buscar o N� Pai do antigo Pai;
			pAux3 = getParent(pBT, DATA(LEFT(pAux2)));
			// Se for nulo, o N� j� est� na Ra�z;
			if (pAux3 == NULL)
				// Atualiza-se "*pBT";
				*pBT = pAux2;
			else
				// Se n�o for nulo, existem duas possibilidades;
				// A antiga Ra�z (agora representada por pAux3) possui como Filho da Direita o Filho da Esquerda do N� a colocar na Ra�z (que ainda n�o est� l�);
				if (RIGHT(pAux3) == LEFT(pAux2))
					// Basta dizer que o N� j� rodado � esquerda � assim Filho da Direita da Ra�z;
					RIGHT(pAux3) = pAux2;
				else
					// Se n�o, a antiga Ra�z possui como Filho da Esquerda o Filho da Direita do N� a colocar na Ra�z (que ainda n�o est� l�);
					// Basta dizer que o N� j� rodado � esquerda � assim Filho da Esquerda da Ra�z;
					LEFT(pAux3) = pAux2;

			pAux2 = getParent(pBT, DATA(pAux)); // Obt�m o novo Pai;
		}
	}

	return OK;
}
//---------------Eliminar N�---------------//
STATUS deleteNode (INT_BTREE *pBT, int data)
{
	INT_BTREE_NODE *pTemp = *pBT;
	// Auxiliar para guardar o valor do N� a eliminar e para guardar o valor do Pai do N�;
	INT_BTREE_NODE *pAux, *pAux2;

	// Se a �rvore est� vazia;
	if (emptyIntBTree(*pBT))
		return ERROR;

	// Procura o valor do N� a eliminar na �rvore e o valor do seu Pai;
	pAux = searchBST (&pTemp, data);
	pAux2 = getParent (&pTemp, data);

	if (pAux != NULL) // Se encontrou o N�;
	{
		// Existem 3 casos a considerar para eliminar um N�:
		// Eliminar um n� sem filhos (folha);
		if (isLeaf(pAux)) // Se o N� � folha;
		{
			// Se o N� n�o possui Pai (ou seja, � a Ra�z);
			if (pAux2 == NULL)
			{
				// Os apontadores que est�o a apontar para a Ra�z da �rvore passam a apontar para NULL;
				*pBT = NULL;
				pTemp = NULL;

				// Liberta a mem�ria de "pAux";
				free(pAux);
				return OK;
			}

			// Se o N� � Filho da Direita;
			if (RIGHT(pAux2) == pAux)
				RIGHT(pAux2) = NULL; // O Pai deixa de possuir Filho da Direita;
			else
				LEFT(pAux2) = NULL; // O Pai deixa de possuir Filho da Esquerda;
			
			// Liberta a mem�ria de "pAux";
			free(pAux);
		}

		// Eliminar um n� com um filho:
		if (RIGHT(pAux) == NULL && LEFT(pAux) != NULL) 
		{
			// Se o N� for Filho da Esquerda;
			if (LEFT(pAux2) == pAux)
				// O Filho da Esquerda do Pai passa a ser o Filho da Esquerda do N� a eliminar;
				LEFT(pAux2) = LEFT(pAux);
			// Se o N� for Filho da Direita;
			else
				// O Filho da Direita do Pai passa a ser o Filho da Esquerda do N� a eliminar;
				RIGHT(pAux2) = LEFT(pAux);

			// O N� a eliminar deixa de apontar para qualquer outro N�;
			LEFT(pAux) = NULL;
			RIGHT(pAux) = NULL;
			// Liberta a mem�ria de "pAux";
			free (pAux);
		}
		if (RIGHT(pAux) != NULL && LEFT(pAux) == NULL)
		{
			// Se o N� for Filho da Esquerda;
			if (LEFT(pAux2) == pAux)
				// O Filho da Esquerda do Pai passa a ser o Filho da Esquerda do N� a eliminar;
				LEFT(pAux2) = RIGHT(pAux);
			// Se o N� for Filho da Direita;
			else
				// O Filho da Direita do Pai passa a ser o Filho da Direita do N� a eliminar;
				RIGHT(pAux2) = RIGHT(pAux);

			// O N� a eliminar deixa de apontar para qualquer outro N�;
			LEFT(pAux) = NULL;
			RIGHT(pAux) = NULL;
			// Liberta a mem�ria de "pAux";
			free (pAux);
		}

		// Eliminar um n� com dois filhos:
		if (RIGHT(pAux) != NULL && LEFT(pAux) != NULL)
		{
			// Substitui-se pelo seu antecessor ou sucessor (ao percorrer a �rvore utilizando o m�todo in-order), eliminando este da sua posi��o anterior;
		}
	}
	else // Caso contr�rio;
		return ERROR;

	return OK;
}
//---------------Juntar Duas �rvores Bin�rias de Inteiros---------------//
STATUS joinBST (INT_BTREE *pBT, INT_BTREE *pBT2)
{
	INT_BTREE_NODE *pTemp2 = *pBT2;

	// Se ambas as �rvores est�o vazias;
	if (emptyIntBTree(*pBT) && emptyIntBTree(*pBT2))
		return ERROR;
	
	// Verifica se a segunda �rvore possui valores;
	if (emptyIntBTree(*pBT2))
	{
		// Se a segunda �rvore n�o possui valores;
		// Apresenta o resultado:
		fprintf (stdout, "\nArvore Resultante:\n");
		printIntBTreeInOrder(*pBT);
		fprintf(stdout, "\nArvore Eliminada:\n");
		printIntBTreeInOrder(*pBT2);
		return OK;
	}
	else
	{
		// Verifica se a primeira �rvore possui valores (contando que a segunda �rvore possui valores);
		if (emptyIntBTree(*pBT))
		{
			// Se a primeira �rvore n�o possui valores;
			// Troca os apontadores das �rvores;
			*pBT = *pBT2;

			// Destr�i a segunda �rvore;
			pTemp2 = NULL;
			*pBT2 = NULL;

			// Apresenta o resultado:
			fprintf (stdout, "\nArvore Resultante:\n");
			printIntBTreeInOrder(*pBT);
			fprintf(stdout, "\nArvore Eliminada:\n");
			printIntBTreeInOrder(*pBT2);
			return OK;
		}
		// Se ambas as �rvores possuem valores;
		else
		{
			// Uso recursivo da fun��o para os N�s � esquerda e direita da segunda �rvore;
			// Insere todos os N�s da segunda �rvore na primeira;
			joinBST(pBT, &LEFT(pTemp2));
			insertIntBST(pBT, DATA(pTemp2));
			joinBST(pBT, &RIGHT(pTemp2));
			
			// Destr�i a segunda �rvore;
			pTemp2 = NULL;
			*pBT2 = NULL;
			
			// Apresenta o resultado:
			fprintf (stdout, "\nArvore Resultante:\n");
			printIntBTreeInOrder(*pBT);
			fprintf(stdout, "\nArvore Eliminada:\n");
			printIntBTreeInOrder(*pBT2);
			return OK;
		}
	}
	
	return OK;
}
//---------------Obter Profundidade de um N�---------------//
int getBSTNodeDepth (INT_BTREE *pBT, int data)
{
	INT_BTREE_NODE *pTemp = *pBT;
	// Auxiliar para contar a profundidade;
	int depth = -1;

	// Se a �rvore est� vazia, retorna o valor "-1" (o N� n�o existe);
	if (emptyIntBTree(*pBT))
		return -1;

	// Enquanto n�o percorrer a �rvore toda e encontrar o N� procurado;
	while (pTemp != NULL)
	{
		// Se encontra o N� na primeira posi��o:
		if (DATA(pTemp) == data)
		{
			// Incrementa o contador;
			depth++;
			return depth;
		}

		// Incrementa o contador;
		depth++;

		// Como se trata de uma BST, todos os valores maiores que a Ra�z est�o na parte direita da �rvore, enquanto os menores est�o na parte da esquerda;
		// Se o valor do N� atual for menor que o valor procurado;
		if (data >= DATA(pTemp))
			pTemp = RIGHT(pTemp); // Procura-se no lado direito da �rvore;
		else
			pTemp = LEFT(pTemp); // Procura-se no lado esquerdo da �rvore;
	}

	// Se no fim do ciclo o valor for 0, quer dizer que o N� n�o existe;
	if (depth == 0)
	{
		depth = -2;
		return depth;
	}

	return depth;
}