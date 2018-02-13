/*	@autores:	Caio Eduardo Coelho de Oliveira e Raul Silva Menezes
 @matriculas:	16/0003679 e 16/0017327;
  @descriçao:	O programa visa ler um arquivo, salva-lo em uma matriz, mapa, e tentar resolver o tabuleiro atraves de uma arvore generica.
  @problemas:	Nao conseguimos implementar uma arvore que contivesse as possibilidades de jogada. A dificuldade foi em nao conseguir definir criterios
  que abrangessem todas as situaçoes do jogo.
 */
#include <stdio.h>
#include <stdlib.h>
#include "proj4lib.h"

int main ()
{
	int ** mapa, tamanho;
	FILE* entrada;	posicao* posPrimeiro;	posPrimeiro = (posicao*)malloc(sizeof(posicao));
	arvore* raiz = ArvCria();
	fila* filaPrimos; filaPrimos = FilaCria();
	if(posPrimeiro==NULL || raiz==NULL || filaPrimos==NULL){
		printf("Falta memoria para executar o programa");
		return 1;
	}
	entrada = fopen("entradaProj4.txt", "r");
	if(entrada == NULL){
		printf("Erro no arquivo de entrada\n");
		return 1;
	}
	mapa = LeArquivo(entrada, &tamanho); imprimeMapa(mapa, tamanho);
	fclose(entrada);
	FilaInclui(filaPrimos, 2, 1);	FilaInclui(filaPrimos, 3, 2);
	FilaPrimos(tamanho, filaPrimos, mapa);
	posPrimeiro = achaMenor(mapa, tamanho, filaPrimos->primeiro);
	insereInfo(raiz, posPrimeiro);
	printf("Primo: %d\t||Posicao linha: %d \t Posicao coluna: %d\t||\tIndice:%d\n", raiz->posPrimo->primo, raiz->posPrimo->linha, raiz->posPrimo->coluna, raiz->posPrimo->indice);
	printf("Endereco filho: %p\t\t||\tEndereco irmao:%p\t||\n", raiz->direita, raiz->esquerda);
	//mudaMapa(mapa, tamanho, filaPrimos->primeiro); 
	//imprimeMapa(mapa, tamanho);
	//FilaRemoveRepetidos(filaPrimos, mapa, tamanho); imprimeFila(filaPrimos->primeiro);
	//soluciona(raiz, filaPrimos, mapa, tamanho, 0); imprimeArv(raiz);
	imprimeMapa(mapa, tamanho);
	FILE* saida;
	saida = fopen("solucaoProj4.txt", "w+");
	fprintf(saida, "Mapa resultante do processamento.\n");
	int i, j;

	for(i=0; i<tamanho;i++){
		for(j=0;j<tamanho;j++)
			fprintf(saida, "%.2d   ", mapa[i][j]);
		fprintf(saida, "\n");
	}
	fclose(saida);
	ListaLibera(filaPrimos->primeiro); free(filaPrimos); free(mapa);

	return 0;
}		