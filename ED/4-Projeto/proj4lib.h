#include <stdio.h>
#include <stdlib.h>
typedef struct posicao
{
	int indice;
	int primo;
	int linha;
	int coluna;
}posicao;
typedef struct celula
{
	posicao* posPrimo;
    struct celula* prox;
}celula;
typedef struct fila
{
	celula* primeiro;
	celula* ultimo;
}fila;
typedef struct arvore
{
	char jahPassou;
	posicao * posPrimo;
	struct arvore* direita;
	struct arvore* esquerda;
	struct arvore* cima;
	struct arvore* baixo;
}arvore;
posicao* achaMenor(int **mapa, int tamanho, celula* elemento);
int achaPrimo(int primo_anterior);
int** alocarMatriz(int Linhas,int Colunas);
void criaArv(char opcao, arvore* pai_ou_irmao);
void caminhosPossiveis(arvore* caminho, fila* filaPrimos, int** mapa, int tamanho);
fila* FilaCria();
void FilaInclui(fila* ptrFila, int info, int indice);
void FilaPrimos(int tamanho, fila* filaPrimos, int** mapa);
void imprimeMapa(int **mapa, int tamanho);
void imprimeFila(celula* elemento);
void insereArv(arvore* raiz, arvore* caminho, char escolha);
void insereInfo(arvore* arv, posicao* info);
int EhPrimo(int number);
int ** LeArquivo(FILE* arquivo, int* tamanho_mapa);
celula* ListaCria();
void ListaLibera(celula* ptrLista);
void mudaMapa(int** mapa, int tamanho, celula* PrimoDaFila);
void removeDaFila(fila* fila);
void removeElemento(fila* fila, int info);
void soluciona(arvore* caminho, fila* filaPrimos, int** mapa, int tamanho, int QtdPreenchidos);
int * vetorPrimos(int tamanho);

//Definicao
posicao* achaMenor(int **mapa, int tamanho, celula* elemen)
{
	int i, j;
	posicao* pos; pos = (posicao*)malloc(sizeof(posicao));
	if (pos == NULL){
		printf("Falta de memoria para executar o programa\n");
		exit(1);
	}
	pos->primo = 40000; //Numero grande soh para comeacar a busca 
	for(i=0; i<tamanho; i++){
		for(j=0; j<tamanho; j++){
			if (mapa[i][j]!=0){
				if(mapa[i][j] < pos->primo){
					pos->linha = i; pos->coluna = j; pos->primo = mapa[i][j];				
				}
			}
		}
	}
	while(elemen->posPrimo->primo!=pos->primo)
		elemen = elemen->prox;
	pos->indice = elemen->posPrimo->indice;
	return pos;
}

int achaPrimo(int primo_anterior)
{
	int proxPrimo;
	proxPrimo = primo_anterior + 2;
	while(!EhPrimo(proxPrimo))
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
       matriz[i] = (int*) malloc(Colunas*sizeof(int));
       for (j = 0; j < Colunas; j++){
            matriz[i][j] = 0;
       }
  }
  return matriz;
}
arvore* ArvCria()
{
	arvore* novo = (arvore*)malloc(sizeof(arvore));
	novo->esquerda = novo->direita = novo->cima = novo->baixo = NULL; novo->jahPassou = 'n';
	return novo;
}
void insereArv(arvore* raiz, arvore* caminho, char escolha)
{
	if(escolha=='d'){raiz->direita = caminho;}
	if(escolha=='e'){ raiz->esquerda = caminho;}
	if(escolha=='c'){raiz->cima = caminho;}
	if(escolha=='b'){raiz->baixo = caminho;}
}
void insereInfo(arvore* arv, posicao* info)
{
	arv->posPrimo = info;
}
int EhPrimo(int num) {
    int i;
    for (i=3; i*i<=num; i+=2) // A verificacao ja comeca em tres porque 1 e 2 ja sao declarados no vetor de primos
        if (num % i == 0) return 0;
    return 1;
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
    novo->posPrimo->primo = info; novo->posPrimo->indice = indice;
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
	int n, indice=2; n = (tamanho*tamanho)-2;
	while(n--){
		indice++;
		FilaInclui(filaPrimos, achaPrimo(filaPrimos->ultimo->posPrimo->primo), indice);
	}
}
void FilaRemoveRepetidos(fila *filaPrimos, int** mapa, int tamanho)
{
	int i, j;
	for(i=0; i<tamanho; i++)
		for(j=0; j<tamanho; j++)
			if(mapa[i][j]!=0)
				removeElemento(filaPrimos, mapa[i][j]);
}
void imprimeFila(celula* elemento)
{
	printf("||Lista de primos = %d\t||Indice: %d||\n", elemento->posPrimo->primo, elemento->posPrimo->indice);
	if(elemento->prox!=NULL)
		imprimeFila(elemento->prox);
}
void imprimeMapa(int **mapa, int tamanho)
{
	int i, j;
	for(i=0; i<tamanho; i++){
		for(j=0; j<tamanho; j++)
			printf(" %.2d ", mapa[i][j]);
		printf("\n");
	}
}
celula* ListaCria()
{
    celula* ptrLista;
    ptrLista = (celula*) malloc(sizeof(celula)); posicao* pos = (posicao*)malloc(sizeof(posicao));
    pos->linha = pos->coluna = pos->indice = pos->primo = 0;
    ptrLista->posPrimo = pos; ptrLista->prox = NULL; //fim da lista
    return ptrLista;
}
void ListaLibera(celula* ptrLista)
{
    if(ptrLista!=NULL)
        ListaLibera(ptrLista->prox);
    free(ptrLista);
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
			if(mapa[n][m]!=0 && !EhPrimo(mapa[n][m])){
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
void mudaMapa(int** mapa, int tamanho, celula* PrimoDaFila)
{
	int i, j;
	for(i=0; i<tamanho; i++){
		for(j=0; j<tamanho; j++){
			if(mapa[i][j]!=0){
				while(PrimoDaFila->posPrimo->primo!=mapa[i][j]){PrimoDaFila = PrimoDaFila->prox;}
				mapa[i][j] = PrimoDaFila->posPrimo->indice;
			}
		}
	}
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
	if (ptrFila->primeiro->posPrimo->primo == info || ptrFila->primeiro->posPrimo->indice)
		removeDaFila(ptrFila);
	else
	{
		while(aux->prox->posPrimo->primo!=info || aux->prox->posPrimo->indice!=info)
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
pilha* Solucao(arvore* ptrArvore, int** mapa)
{
	pilha* ptrPilha = CriaPilha();
	putOnStack(ptrPilha, ptrArvore);
	while(ptrPilha!=NULL)
	{
		if(IsLeaf(ptrArvore)){
			if(Solves(ptrArvore))
				return ptrPilha;
			else	return NULL;
		}
		if(HasUntriedChild(ptrArvore)){
			child = GivesUntriedChild(ptrArvore);
			putOnStack(child);
		}
		else
			popOffStack(ptrArvore);
	}
	return NULL; //there is no way to the solution
}
// void soluciona(arvore* caminho, fila* filaPrimos, int** mapa, int tamanho, int QtdPreenchidos)
// {
// 	int i, j;
// 	caminhosPossiveis(caminho, filaPrimos, mapa, tamanho); QtdPreenchidos++;
// 	printf("Banana %d|| Maca: %d\n", QtdPreenchidos, tamanho*tamanho);
// 	i = caminho->posPrimo->linha; j = caminho->posPrimo->coluna;
// 	mapa[i][j] = caminho->posPrimo->indice;
// 	if (QtdPreenchidos<(tamanho*tamanho)){
// 		if(caminho->direita!=NULL /*&& caminho->jahPassou == 'n'*/){
// 			soluciona(caminho->direita, filaPrimos, mapa, tamanho, QtdPreenchidos);
// 		}
// 		/*else if(caminho->jahPassou=='s'){
// 			QtdPreenchidos--;
// 			return;
// 		}*/
// 		if(caminho->esquerda!=NULL /*&& caminho->jahPassou == 'n'*/){
// 			soluciona(caminho->esquerda, filaPrimos, mapa, tamanho, QtdPreenchidos);
// 		}
// 		/*else if (caminho->jahPassou == 's'){
// 			QtdPreenchidos--;
// 			return;
// 		}*/
// 		if(caminho->baixo!=NULL /*&& caminho->jahPassou == 'n'*/){
// 			soluciona(caminho->baixo, filaPrimos, mapa, tamanho, QtdPreenchidos);
// 		}
// 		/*else if(caminho->jahPassou == 's'){
// 			QtdPreenchidos--;
// 			return;
// 		}*/
// 		if(caminho->cima!=NULL /*&& caminho->jahPassou == 'n'*/){
// 			soluciona(caminho->cima, filaPrimos, mapa, tamanho, QtdPreenchidos);
// 		}
// 		/*else if(caminho->jahPassou == 's'){
// 			QtdPreenchidos--;
// 			return;
// 		}*/
// 	}
// }

/*
void direita(arvore *anterior, int linha, int coluna, celula* preenchimento)
{
	arvore *dir; dir = ArvCria();
	preenchimento->posPrimo->linha = linha; preenchimento->posPrimo->coluna = coluna;
	dir->posPrimo = preenchimento->posPrimo; dir->jahPassou = 's';
	insereArv(anterior, dir, 'd');
}
void esquerda(arvore *anterior, int linha, int coluna, celula* preenchimento)
{
	arvore *dir; dir = ArvCria();
	preenchimento->posPrimo->linha = linha; preenchimento->posPrimo->coluna = coluna;
	dir->posPrimo = preenchimento->posPrimo; dir->jahPassou = 's';
	insereArv(anterior, dir, 'e');
}
void emCima(arvore *anterior, int linha, int coluna, celula* preenchimento)
{
	arvore *dir; dir = ArvCria();
	preenchimento->posPrimo->linha = linha; preenchimento->posPrimo->coluna = coluna;
	dir->posPrimo = preenchimento->posPrimo; dir->jahPassou = 's';
	insereArv(anterior, dir, 'c');
}
void emBaixo(arvore *anterior, int linha, int coluna, celula* preenchimento)
{
	arvore *dir; dir = ArvCria();
	preenchimento->posPrimo->linha = linha; preenchimento->posPrimo->coluna = coluna;
	dir->posPrimo = preenchimento->posPrimo; dir->jahPassou = 's';
	insereArv(anterior, dir, 'b');
}
void caminhosPossiveis(arvore* caminho, fila* filaPrimos, int** mapa, int tamanho)
{
	int i, j;
	i = caminho->posPrimo->linha; j = caminho->posPrimo->coluna;
	if (i!=0 && i<(tamanho-1) && j!=0 && j<(tamanho-1	)){// Tenho todas as possibilidades
		if(mapa[i][j+1]==0) // Direita livre
			direita(caminho, i, j+1, filaPrimos->primeiro);//Cria no que vai para a direita
		if(mapa[i][j-1]==0) // Esquerda livre
			esquerda(caminho, i, j+1, filaPrimos->primeiro);
		if(mapa[i-1][j]==0) // Em cima livre
			emCima(caminho, i, j+1, filaPrimos->primeiro);
		if(mapa[i+1][j]==0) // Em baixo livre
			emBaixo(caminho, i, j+1, filaPrimos->primeiro);
	}
	else // Casos de bordo
	{
		if(i==0)
		{
			if(j==0)//Canto superior esquerdo (1º elemento)
			{
				if(mapa[i][j+1]==0) // Direita livre
					direita(caminho, i, j+1, filaPrimos->primeiro);
				if(mapa[i+1][j]==0) // Baixo livre
					emBaixo(caminho, i, j+1, filaPrimos->primeiro);
			}
			else if(j==(tamanho-1))// Canto superior direito
			{
				if(mapa[i][j-1]==0) // Esquerda livre
					esquerda(caminho, i, j-1, filaPrimos->primeiro);
				if(mapa[i+1][j]==0) // Baixo livre
					emBaixo(caminho, i+1, j, filaPrimos->primeiro);
			}
			else
			{
				if(mapa[i+1][j]==0)
					emBaixo(caminho, i+1, j, filaPrimos->primeiro);
				if(mapa[i][j+1]==0)
					direita(caminho, i, j+1, filaPrimos->primeiro);
				if(mapa[i][j-1]==0)
					esquerda(caminho, i, j-1, filaPrimos->primeiro);
			}
		}
		else if(i==(tamanho-1))
		{
			if(j==0)// Canto inferior esquerdo
			{
				if(mapa[i][j+1]==0) // Direita livre
					direita(caminho, i, j+1, filaPrimos->primeiro);
				if(mapa[i-1][j]==0) // Em cima livre
					emCima(caminho, i-1, j, filaPrimos->primeiro);	
			}
			else if(j==(tamanho-1))//Canto inferior direito (ultimo elemento)
			{
				if(mapa[i][j-1]==0) // Esquerda livre
					esquerda(caminho, i, j-1, filaPrimos->primeiro);
				if(mapa[i-1][j]) // Em cima livre
					emCima(caminho, (i-1), j, filaPrimos->primeiro);
			}
			else
			{
				if(mapa[i][j+1]==0)
					direita(caminho, i, j+1, filaPrimos->primeiro);
				if(mapa[i][j-1]==0)
					esquerda(caminho, i, (j-1), filaPrimos->primeiro);
				if(mapa[i-1][j]==0)
					emCima(caminho, (i-1), j, filaPrimos->primeiro);
			}
		}
		else if(j==0)
		{
			if(mapa[i][j+1]==0)
				direita(caminho, i, j+1, filaPrimos->primeiro);
			if(mapa[i-1][j]==0)
				emCima(caminho, (i-1), j, filaPrimos->primeiro);
			if(mapa[i+1][j]==0)
				emBaixo(caminho, i+1, j, filaPrimos->primeiro);
		}
		else if(j==(tamanho-1))
		{

			if(mapa[i][j-1]==0)
				esquerda(caminho, i, j-1, filaPrimos->primeiro);
			if(mapa[i-1][j]==0)
				emCima(caminho, (i-1), j, filaPrimos->primeiro);
			if(mapa[i+1][j]==0)
				emBaixo(caminho, i+1, j, filaPrimos->primeiro);
		}
	}
}*/
void imprimeArv(arvore *raiz)
{
	if(raiz == NULL)
		return;
	imprimeArv(raiz -> direita);
	printf("|| Indice olhado no momento: %d|| Jah Passou : %c||Primo: %d\n",raiz->posPrimo->indice, raiz->jahPassou, raiz->posPrimo->primo);
	printf("||Endereco atual %p||Endereco baixo: %p||Endereco cima: %p||Endereco dir: %p||Endereco esq: %p\n", raiz, raiz->baixo, raiz->cima, raiz->direita, raiz->esquerda);
	imprimeArv(raiz->esquerda);
	imprimeArv(raiz->baixo);
	imprimeArv(raiz->cima);
}