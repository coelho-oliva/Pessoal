//Biblioteca de listas.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct item
{
	char letra;
	int valor;
	struct item* prox;
}celula;

celula* criaLista();
celula* ListaNsimoItem(celula* ptrLista, int posicao);
celula* ListaIncluiComeco(celula* ptrLista);
int 	ListaTamanho(celula* ptrLista);
celula* ListaOrdenaDecrescente(celula *ptrLista);
celula* ListaOrdenaCrescente(celula* ptrLista);

//Definicao 
celula* ListaCria()
{
	celula* ptrLista;
	ptrLista = (celula*) malloc(sizeof(celula));
	ptrLista->prox = NULL; //fim da lista
	return ptrLista;
}
celula* ListaIncluiComeco(celula* ptrLista)
{
	celula* novo;
	novo = (celula*)malloc(sizeof(celula));
	novo->prox = (celula*) ptrLista;
	ptrLista = novo;
	return ptrLista;
}
/* celula* incluiFinal(celula* ptrLista)
{
 	celula* novo;
 	novo = (celula*)malloc(sizeof(celula));
 }
*/
int ListaTamanho(celula* ptrLista)
{
	int contador=0;
	while(ptrLista!=NULL){
		contador++;
		ptrLista = ptrLista->prox;
	}
	return contador;
}
celula* ListaNsimoItem(celula* ptrLista, int posicao){
	celula* aux;
	aux = ptrLista;
	if(posicao <= 0){
		return aux;
	}
	while(((posicao-1) != 0) && (ptrLista != NULL)){
		aux = ptrLista->prox;
		posicao--;
	}
	return aux;
}

celula* ListaOrdenaDecrescente(celula* ptrLista) 
{
	if(ptrLista == NULL)
	    return ptrLista; // the list is sorted.
	//1- find largest node. 
	celula *curr, *largest, *largestPrev, *prev;
	curr = ptrLista;
	largest = ptrLista;
	prev = ptrLista;
	largestPrev = ptrLista;
	while(curr != NULL) {
        if(curr->valor > largest->valor) {
            largestPrev = prev;
            largest = curr;
        }
        prev = curr;
        curr = curr->prox;
    }
	//2- switching first node and largest node : 
	celula* tmp;
	if(largest != ptrLista)
	{
	    largestPrev->prox = ptrLista;
	    tmp = ptrLista->prox;
	    ptrLista->prox = largest->prox;
	    largest->prox = tmp;
	}

	// now largest is the first node of the list.

	// calling the function again with the sub list;
	//            list minus its first node.
	largest->prox = ListaOrdenaDecrescente(largest->prox);


	return largest;
}
celula* ListaOrdenaCrescente(celula* ptrLista) 
{
	if(ptrLista == NULL)
	    return ptrLista; // the list is sorted.
	//1- find lowest node. 
	celula *curr, *lowest, *lowestPrev, *prev;
	curr = ptrLista;
	lowest = ptrLista;
	prev = ptrLista;
	lowestPrev = ptrLista;
	while(curr != NULL) {
        if(curr->valor < lowest->valor) {
            lowestPrev = prev;
            lowest = curr;
        }
        prev = curr;
        curr = curr->prox;
    }
	//2- switching first node and lowest node : 
	celula* tmp;
	if(lowest != ptrLista)
	{
	    lowestPrev->prox = ptrLista;
	    tmp = ptrLista->prox;
	    ptrLista->prox = lowest->prox;
	    lowest->prox = tmp;
	}

	// now lowest is the first node of the list.

	// calling the function again with the sub list;
	//            list minus its first node.
	lowest->prox = ListaOrdenaCrescente(lowest->prox);


	return lowest;
}