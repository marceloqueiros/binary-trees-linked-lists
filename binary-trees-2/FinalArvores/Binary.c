#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Binary.h"

//---------------Iniciar Árvore Binária de Inteiros---------------//
STATUS initIntBTree(INT_BTREE *pBT)
{
	*pBT = NULL;
	return OK;
}
//---------------Testar se a Árvore Binária de Inteiros está vazia---------------//
BOOLEAN emptyIntBTree (INT_BTREE BT)
{
	if (BT == NULL)
		return TRUE;
	else
		return FALSE;
}
//---------------Testar se um determinado elemento é folha---------------//
BOOLEAN isLeaf(INT_BTREE_NODE *pBT)
{
	// Se o nó possui um apontador para o nó da esquerda e da direita a "null";
	if ( LEFT(pBT) == NULL &&  RIGHT(pBT) == NULL)
		return TRUE; // Então é uma folha;
	else
		return FALSE;
}
//---------------Criar novo nó para Árvore Binária de Inteiros---------------//
STATUS createNewIntBTNode(INT_BTREE_NODE **pNew, int data)
{
	INT_BTREE_NODE *pTemp;

	// Aloca memória para um novo nó de Árvore Binária;
	if( (pTemp = (INT_BTREE_NODE *) malloc (sizeof(INT_BTREE_NODE))) == NULL)
		return ERROR;
	
	// Cria o novo nó, com o valor passado como parâmetro de entrada e com os apontadores para a esquerda/direita a "null";
	*pNew = pTemp;
	DATA(pTemp) = data;
	LEFT(pTemp) = NULL;
	RIGHT(pTemp) = NULL;

	return OK;
}
//---------------Inserir nó na Árvore Binária de Inteiros---------------//
STATUS insertIntBST(INT_BTREE *pBT, int data)
{
	INT_BTREE_NODE *pNew;
	
	if (emptyIntBTree(*pBT)) // Se a Árvore Binária está vazia;
	{
		// Cria um novo nó;
		if (createNewIntBTNode(&pNew, data) == ERROR)
			return ERROR;

		// É inserido na raíz da Árvore;
		*pBT = pNew;
		return OK;
	}
	else
		// Como se trata de uma BST, todos os valores menores que a raíz são colocados à esquerda e todos os maiores à direita;
		if (data <= DATA (*pBT)) // Se o valor do nó a inserir for menor que o valor da raíz;
			insertIntBST( &(LEFT(*pBT)), data); // Uso recursivo da função à esquerda da raíz;
		else  // Senão;
			insertIntBST( &(RIGHT(*pBT)), data); // Uso recursivo da função à direita da raíz;
	return OK;
}
//---------------Imprimir Árvore Binária de Inteiros percorrendo PreOrder---------------//
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
//---------------Imprimir Árvore Binária de Inteiros percorrendo InOrder---------------//
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
//---------------Imprimir Árvore Binária de Inteiros percorrendo PostOrder---------------//
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
//---------------Rodar à Direita---------------//
STATUS rotateRight(INT_BTREE_NODE **pBT)
{
	// Auxiliares;
	INT_BTREE_NODE *pTemp, *pAux, *pAux2;

	// Verifica se a Árvore tem valores;
	if (emptyIntBTree(*pBT))
		return ERROR;

	// Se a Árvore não possui um Filho da Esquerda;
	if (LEFT(*pBT) == NULL)
		return ERROR; // Não pode rodar à direita;

	// Filho da Esquerda;
	pAux = LEFT(*pBT);
	// Filho da Direita do Filho da Esquerda;
	pAux2 = RIGHT(LEFT(*pBT));

	// O Nó "pTemp" passa a apontar para o Filho da Esquerda da Raíz;
	pTemp = pAux;
	// A Raíz passa a ser o Filho da Direita de "pTemp";
	RIGHT(pTemp) = *pBT;
	// O Filho da Direita do Filho da Esquerda da Raíz passa a ser o Filho da Esquerda do Filho da Direita da Raíz;
	LEFT(RIGHT(pTemp)) = pAux2;
	// A Raíz passa a apontar para o mesmo Nó que "pTemp" ("pTemp" tornou-se a nova Raíz);
	*pBT = pTemp;

	return OK;
}
//---------------Rodar à Esquerda---------------//
STATUS rotateLeft(INT_BTREE_NODE **pBT)
{
	// Auxiliares;
	INT_BTREE_NODE *pTemp, *pAux, *pAux2;

	// Verifica se a Árvore tem valores;
	if (emptyIntBTree(*pBT))
		return ERROR;

	// Se a Árvore não possui um Filho da Direita;
	if (RIGHT(*pBT) == NULL)
		return ERROR;

	// Filho da Direita;
	pAux = RIGHT(*pBT);
	// Filho da Esquerda do Filho da Direita;
	pAux2 = LEFT(RIGHT(*pBT));

	// O Nó "pTemp" passa a apontar para o Filho da Direita da Raíz;
	pTemp = pAux;
	// A Raíz passa a ser o Filho da Esquerda de "pTemp";
	LEFT(pTemp) = *pBT;
	// O Filho da Esquerda do Filho da Direita da Raíz passa a ser o Filho da Direita do Filho da Esquerda da Raíz;
	RIGHT(LEFT(pTemp)) = pAux2;
	// A Raíz passa a apontar para o mesmo Nó que "pTemp" ("pTemp" tornou-se a nova Raíz);
	*pBT = pTemp;

	return OK;
}
//---------------Contar Nós---------------//
int countBST (INT_BTREE BT)
{
	int count = 0;
	INT_BTREE pTemp = BT;

	// Se a Árvore está vazia;
	if (emptyIntBTree(pTemp) == TRUE)
		return count; // Retorna o contador a 0;

	count++; // Incrementa o contador;
	count += countBST(LEFT(pTemp)); // Uso recursivo da função para os nós à esquerda da raíz;
	count += countBST(RIGHT(pTemp)); // Uso recursivo da função para os nós à direita da raíz;

	return count; // Retorna o contador;
}
//---------------Contar número de repetições de um determinado Nó---------------//
int countRepeatedIntBSTreeNode(INT_BTREE BT, int N)
{
	int count = 0;
	INT_BTREE pTemp = BT;

	// Se a Árvore está vazia;
	if (emptyIntBTree(pTemp) == TRUE)
		return count; // Retorna o contador a 0;

	// Se a Raíz possui o valor procurado;
	if (DATA(pTemp) == N)
		count++; // Incrementa o contador;
		
	count += countRepeatedIntBSTreeNode(LEFT(pTemp), N); // Uso recursivo da função para os nós à esquerda da raíz;
	count += countRepeatedIntBSTreeNode(RIGHT(pTemp), N); // Uso recursivo da função para os nós à direita da raíz;

	return count; // Retorna o contador;
}
//---------------Pesquisar Nó---------------//
INT_BTREE_NODE* searchBST (INT_BTREE *pBT, int data)
{
	INT_BTREE_NODE *pTemp = *pBT;

	// Como se trata de uma BST, todos os valores maiores que a Raíz estão na parte direita da Árvore, enquanto os menores estão na parte da esquerda;
	while (pTemp != NULL && DATA(pTemp) != data) // Enquanto não tiver sido percorrida toda a Árvore e encontrado o valor procurado;
	{
		if (DATA(pTemp) > data) // Se o Nó atual possuir um valor maior do que aquele procurado;
			pTemp = LEFT(pTemp); // Procura-se no lado esquerdo da Árvore;
		else // Se for menor;
			pTemp = RIGHT(pTemp); // Procura-se no lado direito da Árvore;
	}

	return pTemp; // Retorna o Nó;
}
//---------------Obter o Máximo Valor Presente na Árvore Binária de Inteiros---------------//
int getMaxInt (INT_BTREE *pBT)
{
	INT_BTREE_NODE *pTemp = *pBT;
	// Auxiliar para guardar o maior valor presente na Árvore:
	int maior = INT_MIN;

	// Se a Árvore está vazia;
	if (emptyIntBTree (*pBT))
		return INT_MIN;

	// Enquanto não tiver sido percorrida toda a Árvore:
	while (pTemp != NULL)
	{
		// Se o valor do Nó atual for maior que o valor guardado na variável auxiliar;
		if (DATA(pTemp) > maior)
			maior = DATA(pTemp);
		
		// Como se trata de uma BST, todos os valores maiores que a Raíz (Nó verificado na primeira iteração) estão na parte direita da Árvore;
		// Procura no lado direito da Árvore (apenas se o Nó atual possuir filho da direita, caso contrário a função termina);
		pTemp = RIGHT(pTemp);
	}

	return maior;
}
//---------------Obter o Mínimo Valor Presente na Árvore Binária de Inteiros---------------//
int getMinInt (INT_BTREE *pBT)
{
	INT_BTREE_NODE *pTemp = *pBT;
	// Auxiliar para guardar o menor valor presente na Árvore:
	int menor = INT_MAX;

	// Se a Árvore está vazia;
	if (emptyIntBTree (*pBT))
		return INT_MAX;

	// Enquanto não tiver sido percorrida toda a Árvore:
	while (pTemp != NULL)
	{
		// Se o valor do Nó atual for menor que o valor guardado na variável auxiliar;
		if (DATA(pTemp) < menor)
			menor = DATA(pTemp);
		
		// Como se trata de uma BST, todos os valores menores que a Raíz (Nó verificado na primeira iteração) estão na parte esquerda da Árvore;
		// Procura no lado esquerdo da Árvore (apenas se o Nó atual possuir filho da esquerda, caso contrário a função termina);
		pTemp = LEFT(pTemp);
	}

	return menor;
}
//---------------Obter Pai de um Nó---------------//
INT_BTREE_NODE* getParent (INT_BTREE *pBT, int data)
{
	INT_BTREE_NODE *pTemp = *pBT;
	INT_BTREE_NODE *parent = NULL;
	// Contador auxiliar;
	int aux = 0;

	if (emptyIntBTree(*pBT))
		return NULL;

	// Enquanto não tiver sido percorrida toda a Árvore;
	while (pTemp != NULL)
	{
		// Incrementa o contador;
		aux ++;
		// Se encontrou o Nó;
		if (DATA(pTemp) == data)
		{
			// Se o contador for igual a 1, quer dizer que encontrou o Nó na Raíz, logo ele não possui um Nó pai;
			if (aux == 1)
				return NULL;

			// Retorna o Nó como sendo o Pai;
			return parent;
		}

		// Coloca o Pai a apontar para o Nó atual;
		parent = pTemp;

		// Como se trata de uma BST, todos os valores maiores que a Raíz estão na parte direita da Árvore, enquanto os menores estão na parte da esquerda;
		if (DATA(pTemp) > data) // Se o Nó atual possuir um valor maior do que aquele procurado;
			pTemp = LEFT(pTemp); // Procura-se no lado esquerdo da Árvore;
		else
			pTemp = RIGHT(pTemp); // Procura no lado direito da Árvore;
	}

	return NULL;
}
//---------------Inserir na Raíz---------------//
STATUS insertRootBSTree (INT_BTREE *pBT, int data)
{
	// Variável para guardar o Nó, para guardar o seu Pai e Auxiliar para colmatar a falta de atualização da Árvore após a rotação;
	INT_BTREE_NODE *pAux, *pAux2, *pAux3;
	
	// Insere o Nó na Árvore;
	insertIntBST (pBT, data);		
	// Obtém o Nó;
	pAux = searchBST (pBT, data);
	// Obtém o seu Pai;
	pAux2 = getParent(pBT, data);

	// Enquanto o Nó a inserir na Raíz não estiver efetivamente na Raíz (se a Árvore estiver vazia a função "insertIntBST" insere o Nó diretamente na Raíz);
	while (pAux != *pBT)
	{
		// Se o Nó for Filho da Esquerda;
		if (LEFT(pAux2) == pAux)
		{
			rotateRight(&pAux2); // Roda o Pai à Direita;

			// Como a Árvore não é atualizada, após a rotação à direita o antigo Pai (agora o Filho da Direita do Nó a colocar na Raíz) possui 2 Pais:
			// O Nó a colocar na Raíz, que assim se tornou depois da Rotação da Árvore;
			// E a antiga Raíz da Árvore, que não foi atualizada;
			// Logo, vamos buscar o Nó Pai do antigo Pai;
			pAux3 = getParent(pBT, DATA(RIGHT(pAux2)));
			// Se for nulo, o Nó já está na Raíz;
			if (pAux3 == NULL)
				// Atualiza-se "*pBT";
				*pBT = pAux2;
			else
				// Se não for nulo, existem duas possibilidades;
				// A antiga Raíz (agora representada por pAux3) possui como Filho da Esquerda o Filho da Direita do Nó a colocar na Raíz (que ainda não está lá);
				if (LEFT(pAux3) == RIGHT(pAux2))
					// Basta dizer que o Nó já rodado à direita é assim Filho da Esquerda da Raíz;
					LEFT(pAux3) = pAux2;
				else
					// Se não, a antiga Raíz possui como Filho da Direita o Filho da Esquerda do Nó a colocar na Raíz (que ainda não está lá);
					// Basta dizer que o Nó já rodado à direita é assim Filho da Direita da Raíz;
					RIGHT(pAux3) = pAux2;
			
			pAux2 = getParent(pBT, DATA(pAux)); // Obtém o novo Pai;
		}
		else
		{
			rotateLeft (&pAux2); // Roda à Esquerda;
			// Como a Árvore não é atualizada, após a rotação à esquerda o antigo Pai (agora o Filho da Esquerda do Nó a colocar na Raíz) possui 2 Pais:
			// O Nó a colocar na Raíz, que assim se tornou depois da Rotação da Árvore;
			// E a antiga Raíz da Árvore, que não foi atualizada;
			// Logo, vamos buscar o Nó Pai do antigo Pai;
			pAux3 = getParent(pBT, DATA(LEFT(pAux2)));
			// Se for nulo, o Nó já está na Raíz;
			if (pAux3 == NULL)
				// Atualiza-se "*pBT";
				*pBT = pAux2;
			else
				// Se não for nulo, existem duas possibilidades;
				// A antiga Raíz (agora representada por pAux3) possui como Filho da Direita o Filho da Esquerda do Nó a colocar na Raíz (que ainda não está lá);
				if (RIGHT(pAux3) == LEFT(pAux2))
					// Basta dizer que o Nó já rodado à esquerda é assim Filho da Direita da Raíz;
					RIGHT(pAux3) = pAux2;
				else
					// Se não, a antiga Raíz possui como Filho da Esquerda o Filho da Direita do Nó a colocar na Raíz (que ainda não está lá);
					// Basta dizer que o Nó já rodado à esquerda é assim Filho da Esquerda da Raíz;
					LEFT(pAux3) = pAux2;

			pAux2 = getParent(pBT, DATA(pAux)); // Obtém o novo Pai;
		}
	}

	return OK;
}
//---------------Eliminar Nó---------------//
STATUS deleteNode (INT_BTREE *pBT, int data)
{
	INT_BTREE_NODE *pTemp = *pBT;
	// Auxiliar para guardar o valor do Nó a eliminar e para guardar o valor do Pai do Nó;
	INT_BTREE_NODE *pAux, *pAux2;

	// Se a Árvore está vazia;
	if (emptyIntBTree(*pBT))
		return ERROR;

	// Procura o valor do Nó a eliminar na Árvore e o valor do seu Pai;
	pAux = searchBST (&pTemp, data);
	pAux2 = getParent (&pTemp, data);

	if (pAux != NULL) // Se encontrou o Nó;
	{
		// Existem 3 casos a considerar para eliminar um Nó:
		// Eliminar um nó sem filhos (folha);
		if (isLeaf(pAux)) // Se o Nó é folha;
		{
			// Se o Nó não possui Pai (ou seja, é a Raíz);
			if (pAux2 == NULL)
			{
				// Os apontadores que estão a apontar para a Raíz da Árvore passam a apontar para NULL;
				*pBT = NULL;
				pTemp = NULL;

				// Liberta a memória de "pAux";
				free(pAux);
				return OK;
			}

			// Se o Nó é Filho da Direita;
			if (RIGHT(pAux2) == pAux)
				RIGHT(pAux2) = NULL; // O Pai deixa de possuir Filho da Direita;
			else
				LEFT(pAux2) = NULL; // O Pai deixa de possuir Filho da Esquerda;
			
			// Liberta a memória de "pAux";
			free(pAux);
		}

		// Eliminar um nó com um filho:
		if (RIGHT(pAux) == NULL && LEFT(pAux) != NULL) 
		{
			// Se o Nó for Filho da Esquerda;
			if (LEFT(pAux2) == pAux)
				// O Filho da Esquerda do Pai passa a ser o Filho da Esquerda do Nó a eliminar;
				LEFT(pAux2) = LEFT(pAux);
			// Se o Nó for Filho da Direita;
			else
				// O Filho da Direita do Pai passa a ser o Filho da Esquerda do Nó a eliminar;
				RIGHT(pAux2) = LEFT(pAux);

			// O Nó a eliminar deixa de apontar para qualquer outro Nó;
			LEFT(pAux) = NULL;
			RIGHT(pAux) = NULL;
			// Liberta a memória de "pAux";
			free (pAux);
		}
		if (RIGHT(pAux) != NULL && LEFT(pAux) == NULL)
		{
			// Se o Nó for Filho da Esquerda;
			if (LEFT(pAux2) == pAux)
				// O Filho da Esquerda do Pai passa a ser o Filho da Esquerda do Nó a eliminar;
				LEFT(pAux2) = RIGHT(pAux);
			// Se o Nó for Filho da Direita;
			else
				// O Filho da Direita do Pai passa a ser o Filho da Direita do Nó a eliminar;
				RIGHT(pAux2) = RIGHT(pAux);

			// O Nó a eliminar deixa de apontar para qualquer outro Nó;
			LEFT(pAux) = NULL;
			RIGHT(pAux) = NULL;
			// Liberta a memória de "pAux";
			free (pAux);
		}

		// Eliminar um nó com dois filhos:
		if (RIGHT(pAux) != NULL && LEFT(pAux) != NULL)
		{
			// Substitui-se pelo seu antecessor ou sucessor (ao percorrer a árvore utilizando o método in-order), eliminando este da sua posição anterior;
		}
	}
	else // Caso contrário;
		return ERROR;

	return OK;
}
//---------------Juntar Duas Árvores Binárias de Inteiros---------------//
STATUS joinBST (INT_BTREE *pBT, INT_BTREE *pBT2)
{
	INT_BTREE_NODE *pTemp2 = *pBT2;

	// Se ambas as Árvores estão vazias;
	if (emptyIntBTree(*pBT) && emptyIntBTree(*pBT2))
		return ERROR;
	
	// Verifica se a segunda Árvore possui valores;
	if (emptyIntBTree(*pBT2))
	{
		// Se a segunda Árvore não possui valores;
		// Apresenta o resultado:
		fprintf (stdout, "\nArvore Resultante:\n");
		printIntBTreeInOrder(*pBT);
		fprintf(stdout, "\nArvore Eliminada:\n");
		printIntBTreeInOrder(*pBT2);
		return OK;
	}
	else
	{
		// Verifica se a primeira Árvore possui valores (contando que a segunda Árvore possui valores);
		if (emptyIntBTree(*pBT))
		{
			// Se a primeira Árvore não possui valores;
			// Troca os apontadores das Árvores;
			*pBT = *pBT2;

			// Destrói a segunda Árvore;
			pTemp2 = NULL;
			*pBT2 = NULL;

			// Apresenta o resultado:
			fprintf (stdout, "\nArvore Resultante:\n");
			printIntBTreeInOrder(*pBT);
			fprintf(stdout, "\nArvore Eliminada:\n");
			printIntBTreeInOrder(*pBT2);
			return OK;
		}
		// Se ambas as Árvores possuem valores;
		else
		{
			// Uso recursivo da função para os Nós à esquerda e direita da segunda Árvore;
			// Insere todos os Nós da segunda Árvore na primeira;
			joinBST(pBT, &LEFT(pTemp2));
			insertIntBST(pBT, DATA(pTemp2));
			joinBST(pBT, &RIGHT(pTemp2));
			
			// Destrói a segunda Árvore;
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
//---------------Obter Profundidade de um Nó---------------//
int getBSTNodeDepth (INT_BTREE *pBT, int data)
{
	INT_BTREE_NODE *pTemp = *pBT;
	// Auxiliar para contar a profundidade;
	int depth = -1;

	// Se a Árvore está vazia, retorna o valor "-1" (o Nó não existe);
	if (emptyIntBTree(*pBT))
		return -1;

	// Enquanto não percorrer a Árvore toda e encontrar o Nó procurado;
	while (pTemp != NULL)
	{
		// Se encontra o Nó na primeira posição:
		if (DATA(pTemp) == data)
		{
			// Incrementa o contador;
			depth++;
			return depth;
		}

		// Incrementa o contador;
		depth++;

		// Como se trata de uma BST, todos os valores maiores que a Raíz estão na parte direita da Árvore, enquanto os menores estão na parte da esquerda;
		// Se o valor do Nó atual for menor que o valor procurado;
		if (data >= DATA(pTemp))
			pTemp = RIGHT(pTemp); // Procura-se no lado direito da Árvore;
		else
			pTemp = LEFT(pTemp); // Procura-se no lado esquerdo da Árvore;
	}

	// Se no fim do ciclo o valor for 0, quer dizer que o Nó não existe;
	if (depth == 0)
	{
		depth = -2;
		return depth;
	}

	return depth;
}