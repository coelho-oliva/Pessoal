#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define AterriMax 7
#define DecolMax 28
#define nVoosMax 42

typedef struct voo
{
	char AorD;
	int prioridade;
	char nome[7];
	struct voo* prox;
}Voo;
typedef struct fila
{
	Voo *inicio; /*Primeiro elemento da lista*/
	Voo *fim;/*último elemento lista*/
}FILA;
FILA* criaFila();
Voo* dadosVoo(FILA* ptrFila, char C);
int geraRand(int min, int max);
int geraAterrisagem(FILA* ptrFila);
int geraDecol(FILA* fi);
// void tempo();
void liberaFila(FILA *ptrFila);
void mostraLista(Voo* ptrLista);
Voo* OrdenaCrescente(Voo* ptrLista);
int removeDaFila(FILA* fi);



int main ()
{
	srand(time(NULL));
	FILA* ptrFilaAterrisagem;
	FILA* ptrFilaDecolagem;
	ptrFilaAterrisagem = criaFila();
	ptrFilaDecolagem = criaFila();
	if(ptrFilaAterrisagem == NULL || ptrFilaDecolagem == NULL)
	{
		printf("Erro. Nao foi possivel criar a fila.\n");
		return EXIT_FAILURE;
	}

	int qtdAterri = geraRand(1,AterriMax);
	int qtdDecol  = geraRand(1,DecolMax);
	printf("Quantidade de aterrisagens em espera: %d\nQuantidade de decolagens em espera: %d\n", qtdAterri, qtdDecol);

	//Cria lista para Aterrisagens
	while(geraAterrisagem(ptrFilaAterrisagem) &&  qtdAterri-1!=0)
	{
		qtdAterri--;
	}
	ptrFilaAterrisagem->inicio = OrdenaCrescente(ptrFilaAterrisagem->inicio);
	Voo* ptrAux;
	ptrAux = ptrFilaAterrisagem->inicio;
	while(ptrAux!=NULL) //Encontra o fim da lista
	{
		ptrFilaAterrisagem->fim = ptrAux;
		ptrAux=ptrAux->prox;
	}
	//mostra a lista de aterrisagens ordenada
	printf("LISTA ATERRISAGEM ORDENADA --------------------------\n");
	ptrAux = ptrFilaAterrisagem->inicio;
	mostraLista(ptrAux);

	//Cria lista de decolagens
	while(geraDecol(ptrFilaDecolagem) &&  qtdDecol-1!=0)
	{
		qtdDecol--;
	}
	ptrFilaDecolagem->inicio = OrdenaCrescente(ptrFilaDecolagem->inicio);
	ptrAux = ptrFilaDecolagem->inicio;
	while(ptrAux!=NULL) //Encontra o fim da lista
	{
		ptrFilaDecolagem->fim = ptrAux;
		ptrAux=ptrAux->prox;
	}
	//mostra lista de decolagens ordenada
	printf("LISTA DECOLAGEM ORDENADA --------------------------\n");
	ptrAux = ptrFilaDecolagem->inicio;
	mostraLista(ptrAux);

	liberaFila(ptrFilaAterrisagem);
	liberaFila(ptrFilaDecolagem);
	return 0;
}

//lib.
FILA* criaFila()
{
	FILA *fi = (FILA*) malloc(sizeof(FILA));
	if(fi==NULL)
		return NULL;
	
	fi->inicio = NULL;
	fi->fim = NULL;
	return fi;
}
Voo* dadosVoo(FILA* fi, char C) // Funcao que gera os dados do novo elemento da lista
{
	if(fi == NULL){ //Verifica se a fila existe
		printf("Houve um problema com a fila\n");
		exit(1); //Se não existe, o programa acaba
	}
	//Daqui pra frente, vai-se gerar os dados aleatórios do Voo de aterrisagem
	int i = 2;
	Voo* v = (Voo*)malloc(sizeof(Voo));
	if (v==NULL) //Verifica se foi possível alocar espaço para os dados de Voo
	{
		printf("Nao ha espaco de memoria para contiunar o programa\n");
		exit(1);// Se nao, sai do programa
	}
	v->nome[0] = ('A' + (char)(rand()%26));v->nome[1] =(char)geraRand('A', 'Z');//Gera caracter maiusculo aleatorio segundo tabela ASCII
	while(i<6)
	{
		v->nome[i]=('0' + (char)(rand()%10));//Gera numero do código de vôo
		i++;
	}
	v->nome[6] = '\0';
	v->AorD = C; //Especifica se é um vôo de aterrisagem ou decolagem
	if(C == 'A')
		v->prioridade = geraRand(1, 13);//Escolhe aleatoriamente a prioridade de voo
	v->prox = NULL; // Elemento recém criado passa a apontar NULL
	return v;
}

int geraAterrisagem(FILA* ptrFila)
{
	Voo* aterrisagem = dadosVoo(ptrFila, 'A'); // Coloca-se os dados de voo na struct atraves do ponteiro
	if(ptrFila->fim == NULL) //Fila vazia
		ptrFila->inicio = aterrisagem;
	else
		ptrFila->fim->prox = aterrisagem; //Ultimo elemento passa a apontar para o novo elemento inserido
	ptrFila->fim = aterrisagem; //Novo elemento criado passa a ser o fim da fila
	return 1; //Não houve problemas na incersão de elemento
}
int geraRand(int min, int max)
{
 	int r;
 	r=min+rand()%(max-min+1);
	return r;
}
int geraDecol(FILA* fi)
{
	Voo* decolagem = dadosVoo(fi, 'D'); // Coloca-se os dados de voo na strcut atraves do ponteiro
	if(fi->fim == NULL) //Fila vazia
		fi->inicio = decolagem;
	else
		fi->fim->prox = decolagem; //Ultimo elemento passa a apontar para o novo elemento inserido
	fi->fim = decolagem; //Novo elemento criado passa a ser o fim da fila
	return 1; //Não houve problemas na incersão de elemento
}
void liberaFila(FILA *ptrFila)
{
	if (ptrFila!=NULL)
	{
		Voo* no;
		while (ptrFila->inicio != NULL)
		{
			no = ptrFila->inicio;
			ptrFila->inicio = ptrFila->inicio->prox;
			free(no);
		}
		free (ptrFila);
	}
}
void mostraLista(Voo* ptrLista){
	while(ptrLista!=NULL){
		printf("Codigo do voo: %s\n", ptrLista->nome);
		printf("Prioridade:	%d\n", ptrLista->prioridade);
		ptrLista=ptrLista->prox;
	}
}
Voo* OrdenaCrescente(Voo* ptrLista) 
{
	if(ptrLista == NULL)
	    return ptrLista; // the list is sorted.
	//1- find lowest node. 
	Voo *curr, *lowest, *lowestPrev, *prev;
	curr = ptrLista;
	lowest = ptrLista;
	prev = ptrLista;
	lowestPrev = ptrLista;
	while(curr != NULL) {
        if(curr->prioridade < lowest->prioridade) {
            lowestPrev = prev;
            lowest = curr;
        }
        prev = curr;
        curr = curr->prox;
    }
	//2- switching first node and lowest node : 
	Voo* tmp;
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
	lowest->prox = OrdenaCrescente(lowest->prox);


	return lowest;
}
int removeDaFila(FILA* fi)
{
	if(fi==NULL) return 0; //Não ha fila
	if(fi->inicio == NULL) //A lista esta vazia, nao ha como remover
		return 0;
	Voo* v = fi->inicio;
	fi->inicio = fi->inicio->prox;
	if(fi->inicio == NULL) //chegou no fim da fila 
		fi->fim = NULL;//Ultimo elemento nao existe mais
	free(v);
	return 1; //A remocao foi bem sucedida  
}
