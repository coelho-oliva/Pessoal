#include <stdio.h>
#include <stdlib.h>
#include "proj4.h"

void banana(int n, arvore* pai);
void imprimeArv(arvore* arv);

int main()
{
	fila* filaPrimos; filaPrimos = FilaCria();
	arvore* raiz; raiz = ArvCria();
	int n=10, indice=2;
	FilaInclui(filaPrimos, 2, 1);	FilaInclui(filaPrimos, 3, 2);
	while(n--){
		indice++;
		FilaInclui(filaPrimos, achaPrimo(filaPrimos->ultimo->valor), indice);
	}
	posicao* pos = (posicao*)malloc(sizeof(posicao));
	pos->coluna = pos->linha = pos->primo = 1;	
	insereNoh(raiz, pos, NULL, NULL);
	banana(10, raiz);
	imprimeArv(raiz);
	imprimeFila(filaPrimos->primeiro);
	ListaLibera(filaPrimos->primeiro);
	free(filaPrimos);
	return 0;
}

void banana(int n, arvore* pai)
{
	if(n>0){
		arvore *arv; arv = ArvCria();
		posicao* pos = (posicao*)malloc(sizeof(posicao));
		pos->coluna = pos->linha = pos->primo = 1;
		insereNoh(pai, pos, arv, NULL);
		banana(n-1, arv);
	}
}

void imprimeArv(arvore* arv)
{
	printf("Primo: %d\t||Posicao linha: %d \t Posicao coluna: %d\t||\n", arv->posPrimo->primo, arv->posPrimo->linha, arv->posPrimo->coluna);
	//printf("Endereco filho: %p\t\t||\tEndereco irmao:%p\t||\n", arv->irmao);
	if(arv->filho!=NULL){
		imprimeArv(arv->filho);
	}
}
void liberaArv(arvore* arv);