#include <stdio.h>
#include <stdlib.h>

typedef struct posPalavra
{
	char letra;
	int linha;
	int coluna;
}posPalavra;
typedef struct arvore
{
	char letra;
	struct lista* listaFilhos;
}arvore;
typedef struct lista
{
	arvore* filho;
	struct lista *prox;
}lista;


char** 		alocarMatriz(int Linhas,int Colunas);
arvore* 	encontra(arvore* dicionario, char letra);
void 		imprimeMapa(char **mapa, int linhas, int colunas);
arvore*		insereArv(lista* listaFilhos, char letra);
void 		LeDicionario(FILE* arquivo, arvore* ptrArvore);
char **	    LeTabuleiro(FILE* arquivo, int tamanhoMapa);
void 		listaLibera(lista* ptrLista);
lista* 		novaLista();
arvore* 	novoNo();
posPalavra* novaPosicao();
posPalavra* resolve(char caminho, arvore* galho, char **mapa, int i, int j, int tamanhoMapa);
void 		resultado(char** mapa, int linha, int coluna, arvore* dicionario);
void 		salvaResultado(char direcao, posPalavra *PrimeiraLetra, posPalavra *UltimaLetra, char** mapa);

char** alocarMatriz(int Linhas,int Colunas)
{
  int i,j;
  char **matriz = (char**)malloc(Linhas*sizeof(char*));
  if(matriz == NULL){
  	printf("Falta memoria para executar o programa\n");
  	exit(1);
  }
  for (i = 0; i < Linhas; i++){
       matriz[i] = (char*) malloc(Colunas*sizeof(char));
       for (j = 0; j < Colunas; j++){
            matriz[i][j] = '0';
       }
  }
  return matriz;
}

void imprimeMapa(char **mapa, int linhas, int colunas)
{
	int i, j;
	for(i=0; i<linhas; i++){
		for(j=0; j<colunas; j++)
			printf(" %c ", mapa[i][j]);
		printf("\n");
	}
}

arvore* insereArv(lista* FilhosNaLista, char letra)
{	
 	if(FilhosNaLista->filho == NULL)
 	{
 		FilhosNaLista->filho = novoNo();
 		FilhosNaLista->filho->letra = letra;
		return FilhosNaLista->filho;
 	}
	if(FilhosNaLista->filho->letra == letra)
		return FilhosNaLista->filho;
	else if (FilhosNaLista->prox!=NULL)
		insereArv(FilhosNaLista->prox, letra);
	else
	{
		FilhosNaLista->prox = novaLista(); FilhosNaLista = FilhosNaLista->prox;
		FilhosNaLista->filho = novoNo(); FilhosNaLista->filho->letra = letra;
		return FilhosNaLista->filho;
	}
}
void listaLibera(lista* ptrLista)
{
    if(ptrLista!=NULL)
        listaLibera(ptrLista->prox);
    free(ptrLista);
}
void LeDicionario(FILE* arquivo, arvore* ptrArvore)
{
	arvore* ptrRaiz = ptrArvore;
	char letra;
	while(!feof(arquivo))
	{
		while(fscanf(arquivo, "%c", &letra)==1)
		{
			if(letra >= 'A' && letra <= 'Z'){
				ptrArvore = insereArv(ptrArvore->listaFilhos, letra);
			}
			else if(letra == '\n'){
				ptrArvore = ptrRaiz;
				break;
			}
		}
	}
}
char** LeTabuleiro(FILE* arquivo, int tamanhoMapa)
{
	int n, m=0;
	char **mapa, letra;
	mapa = alocarMatriz(tamanhoMapa, tamanhoMapa);
	imprimeMapa(mapa, tamanhoMapa, tamanhoMapa);
	for(n=0; n<tamanhoMapa; n++){
		for(m=0; m<tamanhoMapa; m++)
		{
			if(letra >='A' && letra <= 'Z')
				mapa[n][m] = letra;
			else	m--;
			letra = fgetc(arquivo);
		}
	}
	printf("\n\n");
	return mapa;
}
lista* novaLista()
{
    lista* ptrLista;
    ptrLista = (lista*) malloc(sizeof(lista));
    ptrLista->filho = NULL; ptrLista->prox = NULL;
    return ptrLista;
}
arvore* novoNo()
{
	arvore* novo = (arvore*)malloc(sizeof(arvore));
	lista* filhos = novaLista();
	novo->letra = '0';
	novo->listaFilhos = filhos;
	return novo;
}
posPalavra* novaPosicao()
{
	posPalavra* pos = (posPalavra*)malloc(sizeof(posPalavra));
	pos->letra = 'a'; pos->linha = pos->coluna = -1;
	return pos;
}
arvore* encontra(arvore* dicionario, char letra)
{
	lista* aux = dicionario->listaFilhos;
	while(aux!=NULL)
	{
		if(aux->filho->letra==letra)
			return aux->filho;
		aux = aux->prox;
	}
	return NULL;
}
void resultado(char** mapa, int linha, int coluna, arvore* dicionario)
{
	int i, j;
	posPalavra *PrimeiraLetra = NULL, *UltimaLetra = NULL; PrimeiraLetra = novaPosicao();
	arvore *galho = NULL;
	for(i=0; i<linha; i++)
	{
		for(j=0; j<coluna; j++)
		{
			galho = encontra(dicionario, mapa[i][j]);
			if(galho!=NULL)
			{
				PrimeiraLetra->linha = i; PrimeiraLetra->coluna = j; PrimeiraLetra->letra = mapa[i][j];
				/*Caminho direita*/
				UltimaLetra = resolve('d', galho, mapa, i, j, coluna);
				if(UltimaLetra!=NULL){ 
					salvaResultado('d', PrimeiraLetra, UltimaLetra, mapa);
				}
				/*Caminho esquerda*/
				UltimaLetra = resolve('e', galho, mapa, i, j, coluna);
				if(UltimaLetra!=NULL)
				{ 
					salvaResultado('e', PrimeiraLetra, UltimaLetra, mapa);
				}
				/*Caminho cima*/
				UltimaLetra = resolve('c', galho, mapa, i, j, linha);
				if(UltimaLetra!=NULL)
				{
					salvaResultado('c', PrimeiraLetra, UltimaLetra, mapa); 
				}
				/*Caminho baixo*/
				UltimaLetra = resolve('b', galho, mapa, i, j, linha);
				if(UltimaLetra!=NULL){ 
					salvaResultado('b', PrimeiraLetra, UltimaLetra, mapa);
				}
			}
		}
	}
}
posPalavra* resolve(char caminho, arvore* galho, char **mapa, int i, int j, int tamanhoMapa)
{
	arvore* aux = galho; 
	if(caminho=='d')
	{
		if((j+1)<tamanhoMapa)
		{
			aux = encontra(galho, mapa[i][j+1]);
			if(aux!=NULL)
			{ 
				if(aux->listaFilhos->filho == NULL)
				{
					posPalavra* UltimaLetra = novaPosicao();
					UltimaLetra->letra = mapa[i][j+1];
					UltimaLetra->linha = i; UltimaLetra->coluna = (j+1);
					return UltimaLetra; 
				}
				return resolve('d', aux, mapa, i, (j+1), tamanhoMapa);
			}
		}
	}
	if(caminho=='e')
	{
		if((j-1)>=0)
		{
			aux = encontra(galho, mapa[i][j-1]);
			if(aux!=NULL){
				if(aux->listaFilhos->filho == NULL)
				{
					posPalavra* UltimaLetra = novaPosicao();
					UltimaLetra->letra = mapa[i][j-1];
					UltimaLetra->linha = i; UltimaLetra->coluna = (j-1); 
					return UltimaLetra; 
				}
				return resolve('e', aux, mapa, i, (j-1), tamanhoMapa);
			}
		}
	}
	if(caminho=='c')
	{
		if((i-1)>=0)
		{
			aux = encontra(galho, mapa[i-1][j]);
			if(aux!=NULL){
				if(aux->listaFilhos->filho == NULL) 
				{
					posPalavra* UltimaLetra = novaPosicao();
					UltimaLetra->letra = mapa[i-1][j];
					UltimaLetra->linha = (i-1); UltimaLetra->coluna = j; 
					return UltimaLetra; 
				}
				return resolve('c', aux, mapa, (i-1), j, tamanhoMapa);
			}
		}
	}
	if(caminho=='b')
	{
		if((i+1)<tamanhoMapa)
		{
			aux = encontra(galho, mapa[i+1][j]);
			if(aux!=NULL){
				if(aux->listaFilhos->filho == NULL)
				{
					posPalavra* UltimaLetra = novaPosicao();
					UltimaLetra->letra = mapa[i+1][j];
					UltimaLetra->linha = (i+1); UltimaLetra->coluna = j;
					return UltimaLetra; 
				}
				return resolve('b', aux, mapa, (i+1), j, tamanhoMapa);
			}
		}
	}
	return NULL;
}
void salvaResultado(char direcao, posPalavra *PrimeiraLetra, posPalavra *UltimaLetra, char** mapa)
{
	int xi, xf, yi, yf;
	xi = PrimeiraLetra->linha;  xf = UltimaLetra->linha;
	yi = PrimeiraLetra->coluna;	yf = UltimaLetra->coluna;
	FILE* fp = fopen("saidaProj5.txt", "a+");
	fprintf(fp, "\n\n\n\n==================================\n\n\n");
	if(direcao == 'd')
	{
		fprintf(fp, "Letras:\t\tCoordenadas:\n");
		while(yi <= yf)
		{
			fprintf(fp, "%c\t\t[%d][%d]\n", mapa[xi][yi], xi, yi);
			yi++;
		}
	}
	if(direcao == 'e')
	{
		fprintf(fp, "Letras:\t\tCoordenadas:\n");
		while(yi >= yf)
		{
			fprintf(fp, "%c\t\t[%d][%d]\n", mapa[xi][yi], xi, yi);
			yi--;
		}
	}
	if(direcao == 'c')
	{
		fprintf(fp, "Letras:\t\tCoordenadas:\n");
		while(xi >= xf)
		{
			fprintf(fp, "%c\t\t[%d][%d]\n", mapa[xi][yi], xi, yi);
			xi--;
		}
	}
	if(direcao == 'b')
	{
		fprintf(fp, "Letras:\t\tCoordenadas:\n");
		while(xi <= xf)
		{
			fprintf(fp, "%c\t\t[%d][%d]\n", mapa[xi][yi], xi, yi);
			xi++;
		}
	}
	fclose(fp);	
}