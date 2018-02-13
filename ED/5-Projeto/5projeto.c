/*
	  @file:	5projeto.c
	@author:	Caio Eduardo C de Oliveira e Raul Silva Menezes
@matriculas:	Caio: 16/0003679    Raul: 16/0017327

Jogo automatizado de caça-palavras. Busca as palavras contidas num arquivo que salva num dicionario.
Resultado: Imprime em um arquivo a posicao no tabuleiro de cada letra da palavra buscada.
OBS: Soh faz buscas pelas 4 direcoes basicas (Esq->Dire; Dire->Esq; Cima->Baixo, Baixo->Cima)
*/

#include <stdio.h>
#include <stdlib.h>
#include "proj5.h"

#define LINHAS 20
#define COLUNAS 20

int main(){
	arvore* dicionario;
	char** mapa;
	FILE* arquivo;	arquivo = fopen("tabPalavras.txt", "r");
	mapa = LeTabuleiro(arquivo, COLUNAS); imprimeMapa(mapa, LINHAS, COLUNAS);
	fclose(arquivo);
	arquivo = fopen("dicionarioCidades.txt", "r");
	dicionario = novoNo();
	LeDicionario(arquivo, dicionario);
	fclose(arquivo);
	arquivo = fopen("saidaProj5.txt", "w+"); /*criar arquivo limpo*/
	fclose(arquivo);
	resultado(mapa, LINHAS, COLUNAS, dicionario);
	return 0;
}