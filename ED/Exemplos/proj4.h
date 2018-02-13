#include <stdio.h>
#include <stdlib.h>
typedef struct item
{
    int indice;
    int valor;
    struct item* prox;
}celula;
typedef struct posicao
{
	int primo;
	int linha;
	int coluna;
}posicao;
typedef struct fila
{
	celula* primeiro;
	celula* ultimo;
}fila;
typedef struct arvore
{
	posicao * posPrimo;
	struct arvore* pai;
	struct arvore* filho;
	struct arvore* irmao;
}arvore;
posicao* achaMenor(int **mapa, int tamanho);
int achaPrimo(int primo_anterior);
int** alocarMatriz(int Linhas,int Colunas);
void criaArv(char opcao, arvore* pai_ou_irmao);
fila* FilaCria();
void FilaInclui(fila* ptrFila, int info, int indice);
void FilaPrimos(int tamanho, fila* filaPrimos, int** mapa);
void imprimeMapa(int **mapa, int tamanho);
void imprimeFila();
void insereArv(char opcao, arvore* pai_ou_irmao, arvore* novo);
void insereNoh(arvore* arv, posicao* info, arvore* filho, arvore* irmao);
int IsPrime(int number);
int ** LeArquivo(FILE* arquivo, int* tamanho_mapa);
celula* ListaCria();
void ListaLibera(celula* ptrLista);
void removeDaFila(fila* fila);
void removeElemento(fila* fila, int info);
int * vetorPrimos(int tamanho);

//Definicao
celula* ListaCria()
{
    celula* ptrLista;
    ptrLista = (celula*) malloc(sizeof(celula));
    ptrLista->prox = NULL; //fim da lista
    return ptrLista;
}

void ListaLibera(celula* ptrLista)
{
    if(ptrLista!=NULL)
        ListaLibera(ptrLista->prox);
    free(ptrLista);
}

posicao* achaMenor(int **mapa, int tamanho)
{
	int i, j;
	posicao* pos;
	pos = (posicao*)malloc(sizeof(posicao));
	if (pos == NULL){
		printf("Falta de memoria para executar o programa\n");
		exit(1);
	}
	pos->primo = 40000; //Numero grande soh para comeacar a busca 
	for(i=0; i<tamanho; i++)
	{
		for(j=0; j<tamanho; j++)
		{
			if (mapa[i][j]!=0){
				if(mapa[i][j] < pos->primo){
					pos->linha = i; pos->coluna = j; pos->primo = mapa[i][j];				
				}
			}
		}
	}
	return pos;
}

int achaPrimo(int primo_anterior)
{
	int proxPrimo;
	proxPrimo = primo_anterior + 2;
	while(!IsPrime(proxPrimo))
		proxPrimo +=2;
	return proxPrimo;
}

int** alocarMatriz(int Linhas,int Colunas)
{
  int i,j;
  int **matriz = (int**)malloc(Linhas * sizeof(int*));
  if(matriz == NULL){
  	printf("Falta memoria para executar o programa\n");
  	exit(1);
  }
  for (i = 0; i < Linhas; i++){
       matriz[i] = (int*) malloc(Colunas * sizeof(int));
       for (j = 0; j < Colunas; j++){
            matriz[i][j] = 0;
       }
  }
  return matriz;
}
arvore* ArvCria()
{
	arvore* novo = (arvore*)malloc(sizeof(arvore));
	novo->irmao = NULL; novo->filho = NULL;
	return novo;
}
void insereArv(char opcao, arvore* pai_ou_irmao, arvore* novo)
{
	if(opcao=='P'){
		pai_ou_irmao->filho = novo;
		novo->pai = pai_ou_irmao;
	}
	else if (opcao=='I')
		pai_ou_irmao->irmao = novo;
	novo->filho = NULL; novo->irmao = NULL;
}

fila* FilaCria()
{
	fila* fi = (fila*)malloc(sizeof(fila));
	fi->primeiro = fi->ultimo = NULL;
	return fi;
}

void FilaInclui(fila* ptrFila, int info, int indice)
{
    celula* novo, *auxFila;
    novo = ListaCria(); auxFila = ListaCria();
    novo->valor = info; novo->indice = indice;
    if(ptrFila->primeiro==NULL){
    	ptrFila->primeiro = novo;
    	ptrFila->ultimo = novo;
    }
    else
    {
	    auxFila = ptrFila->primeiro;
	    while(auxFila->prox!=NULL){
	        auxFila = auxFila->prox;
	    }
	    auxFila->prox = novo;
	    ptrFila->ultimo = novo;
    }
}
void FilaPrimos(int tamanho, fila* filaPrimos, int** mapa)
{
	int n, i, j, indice=2; n = (tamanho*tamanho)-2;
	while(n--){
		indice++;
		FilaInclui(filaPrimos, achaPrimo(filaPrimos->ultimo->valor), indice);
	}
	for(i=0; i<tamanho; i++)
		for(j=0; j<tamanho; j++)
			if(mapa[i][j]!=0)
				removeElemento(filaPrimos, mapa[i][j]);
}
void insereNoh(arvore* arv, posicao* info, arvore* filho, arvore* irmao)
{
	arv->posPrimo = info;
	arv->filho = filho;
	arv->irmao = irmao;
}
void imprimeFila(celula* elemento)
{
	printf("||Lista de primos = %d\t||Indice: %d\n", elemento->valor, elemento->indice);
	if(elemento->prox!=NULL)
		imprimeFila(elemento->prox);
}
void imprimeMapa(int **mapa, int tamanho)
{
	int i, j;
	for(i=0; i<tamanho; i++){
		for(j=0; j<tamanho; j++)
			printf(" %d ", mapa[i][j]);
		printf("\n");
	}
}
int IsPrime(int num) {
    int i;
    for (i=3; i*i<=num; i+=2) // A verificacao ja comeca em tres porque 1 e 2 ja sao declarados no vetor de primos
        if (num % i == 0) return 0;
    return 1;
}
int ** LeArquivo(FILE* arquivo, int* ptr_tamanho)
{
	int tamanho_mapa, n=0, m;
	int ** mapa;
	fscanf(arquivo, "%d\n", &tamanho_mapa);
	*ptr_tamanho = tamanho_mapa;
	//Fazer a verificação dos primos: -Ver se tem dois; Ver se estao na ordem; //SALVAR POSiCAO DO MENOR PRIMO, E SO DEPOIS VERIFICAR CONTINUIDADE
	mapa = alocarMatriz(tamanho_mapa, tamanho_mapa);
	while(n<tamanho_mapa)
	{
		m = 0;
		while(m<tamanho_mapa)
		{
			fscanf(arquivo, "%d", &mapa[n][m]);
			if(mapa[n][m]!=0 && !IsPrime(mapa[n][m])){
				printf("ENTRADA FORNECIDA NAO POSSUI SOLUCAO\n");
				exit(1);
			}
			m++;
		}
		fscanf(arquivo, "\n");
		n++;
	}
	return mapa;
}
int* vetorPrimos(int tamanho)
{
	int *vetor = (int*)malloc(tamanho*tamanho*sizeof(int));
	int i;
	vetor[0] = 2; vetor[1] = 3;
	for(i=2; i<tamanho*tamanho; i++)
		vetor[i] = achaPrimo(vetor[i-1]);
	return vetor;
}
void removeElemento(fila* ptrFila, int info)
{
	celula* removedor, *aux; removedor = ListaCria(); aux = ListaCria();
	aux = ptrFila->primeiro;
	if (ptrFila->primeiro->valor == info)
		removeDaFila(ptrFila);
	else
	{
		while(aux->prox->valor!=info)
		{
			aux = aux->prox;
		}
		removedor = aux->prox; //Removedor recebe a emergencia
		aux->prox = aux->prox->prox;
		while(aux->prox!=NULL)
			aux = aux->prox;
		ptrFila->ultimo = aux;
		free(removedor);
	}
}
void removeDaFila(fila* ptrFila)
{
	if(ptrFila->primeiro == NULL) //A lista esta vazia, nao ha como remover
		return;
	celula* removedor; removedor = ListaCria();
	removedor = ptrFila->primeiro;
	ptrFila->primeiro = ptrFila->primeiro->prox;
 	if(ptrFila->primeiro == NULL) //chegou no ultimo da ptrFila 
 		ptrFila->ultimo = NULL;//Ultimo elemento nao existe mais
 	free(removedor); 
}
