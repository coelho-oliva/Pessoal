/*
Exercicio de lista encadeada simples.

	Listas sao arranjos de ponteiros de estruturas. Em uma lista simples, cada estrutura possui um ponteiro que aponta para
	a proxima. O ultimo elemento sempre aponta para NULL.
    Uma desvantagem de se usar lista e´ que voce nao pode acessa´-la de maneira aleatoria(Random Access Memory).
    E´ necessario passar por todo o arranjo ate´ chegar ao elemento desejado. 
    Uma vantagem e´ que e´ possi´vel eliminar suas celulas, mesmo que do meio, o que pode evitar disperdicio de memoria. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "listalib.h"

int main()
{
	srand(time(0));
	int itensXtra = 5;
	celula* ptrLista, *ptrAux;
	ptrLista = ListaCria();
	while(itensXtra)
	{
		ptrLista->valor = rand()%249;
		ptrLista = ListaIncluiComeco(ptrLista);
		itensXtra--;
	}
	printf("tamanho da Lista = %d\n", ListaTamanho(ptrLista));
	printf("Ordem decrescente:\n");
	ptrAux = ListaOrdenaDecrescente(ptrLista);
	ptrLista = ptrAux;
	while(ptrAux != NULL){
		printf("Valores na ordem decrescente da lista:	%d\n", ptrAux->valor);
		ptrAux = ptrAux->prox;
	}
	ptrAux = ListaOrdenaCrescente(ptrLista);
	printf("\nOrdem crescente:\n");
	while(ptrAux != NULL){
		printf("Valores na ordem crescente da lista:	%d\n", ptrAux->valor);
		ptrAux = ptrAux->prox;
	}
	return 0;
}
	