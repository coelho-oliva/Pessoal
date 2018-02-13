/*
Falta:
1.	Atendimentos
2.	Previsoes
3.	Relogio
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define AproxMAX 6
#define DecMAX 6
#define OK 1
#define ERRO 0

typedef struct Voo
{
	char AorD;
	int prioridade;
	char nome[7];
	struct Voo* prox;
}Voo;

struct fila
{
	Voo *inicio; /*Primeiro elemento da lista*/
	Voo *fim;/*último elemento lista*/
};

typedef struct fila FILA;
void atendimentoAterr(FILA *filaAterri, FILA *filaDec);
int checaPrioridade(FILA* filaAterri);
FILA* criaFila();
Voo* dadosVoo(FILA* fi, char C);
void diminuiGas(FILA* filaAterri);
Voo* EnderecoPrioridade(FILA* filaAterri, Voo* ptrAnterior);
int geraAterrisagem(FILA* fi);
int geraDec(FILA* fi);
int geraRand(int min, int max);
void liberaFila(FILA *fi);
void mostraDados(Voo* v, int contPistas);
void mostraFila(FILA *fi);
int removeDaFila(FILA *fi);
void removeUrgencia(FILA* filaAterri, Voo* ptrEmerge, Voo* ptrAnterior);

int main ()
{
	srand(time(NULL));
	FILA *filaAterri, *filaDec;
	int nAprox, nDec;
	//Fila de aterrissagens
	filaAterri = criaFila();
	nAprox = geraRand(0, AproxMAX);
	printf("--------------------------------------------\n");
	printf("Numero de elementos na fila de aterrissagens:%d\n\n\n", nAprox);
	while(nAprox>0 && (geraAterrisagem(filaAterri)))//Verifica se conseeguiu inserir um voo aleatório na fila
		nAprox--;
	printf("Fila de aterrissagens:\n");
	mostraFila(filaAterri);
	//Fila de decolagens 
	filaDec = criaFila();
	nDec = geraRand(0, DecMAX);
	printf("--------------------------------------------\n");
	printf("Numero de elementos na fila de decolagens:%d\n\n\n", nDec);
	while(nDec>0 && (geraDec(filaDec)))//Verifica se conseeguiu inserir um voo aleatório na fila
		nDec--;
	printf("Fila de decolagens:\n");
	mostraFila(filaDec);
	atendimentoAterr(filaAterri, filaDec);
	liberaFila(filaAterri);
	liberaFila(filaDec);
	return 0;
}

void diminuiGas(FILA* filaAterri)
{
	Voo* aux = filaAterri->inicio; //Auxiliar recebe o primeiro elemento
	while (aux!=NULL) //Enquanto a fila nao acaba 
	{
		aux->prioridade--; //Diminui a prioridade, ou seja, reduz o combustível das aeronaves 
		aux=aux->prox; // Percorre o próximo elemento da fila
	}
}
void atendimentoAterr(FILA* filaAterri, FILA* filaDec)
{
	/*Ola, Raul. Olá Cadu.
	0.  Preciso de férias;
	1.  Quantos voos P = 1 existem; OK
	2.  Saber o endereço de cada um deles; OK
	3.  Administrar as urgencias; OK
	
	3.1.Alerta geral para mais de 3;
	4.  Adminitrar as decolagens;
	5.  Administrar aterrisagens na ordem de chegada;
	*/
	int reservaPista, pistaLivre, urgencias=0;
	while(1)//deve parar qnd todos os voos forem atendidos.
	{	
		reservaPista=0; //A cada unidade de tempo, as pistas sao liberadas.

		//Primeiro administra todas as urgencias
		urgencias = checaPrioridade(filaAterri); //retorna quantos valores de prioridade maxima existem
		printf("Existem %d voos com prioridade 1\n", urgencias);
		//Trata com as urgencias.
		if(urgencias>3){
			printf("Negada, deu ruim, tem %d avioes prestes a cair.\n", urgencias);
		}
		else
		{
			Voo *ptrAux, *ptrAnterior;
			printf("\nNumero de urgencias: %d\n", urgencias);
			while(urgencias)
			{
				reservaPista++;
				ptrAux = EnderecoPrioridade(filaAterri, ptrAnterior);
				mostraDados(ptrAux, reservaPista);
				removeUrgencia(filaAterri, ptrAnterior, ptrAux);
				urgencias--;
				sleep(2);//Senator soaps. Elegance.
			}
		}
		//Nenhuma pista livre.
		if(reservaPista>=2)
		{
			printf("Time goes on...\n");
			sleep(5);
			continue;
		}
		//Administra as decolagens(pistas 1 ou 2)
		else
		{
			pistaLivre=2-reservaPista;
			printf("Pistas livres: %d\n", pistaLivre);
			//while(pistaLivre)
			//{
		//		
		//	}
		}
	}
}
int checaPrioridade(FILA* filaAterri)
{
	int urgencias=0;
	Voo* ptrAux = filaAterri->inicio;
	while(ptrAux!=NULL)
	{
		if(ptrAux->prioridade == 1)
			urgencias++;
		ptrAux = ptrAux->prox;
	}
	return urgencias;
}
FILA* criaFila()
{
	FILA *fi = (FILA*) malloc(sizeof(FILA));
	if (fi!=NULL){
		fi->inicio = NULL;
		fi->fim = NULL;
	}
	return fi;
}
Voo* dadosVoo(FILA* fi, char C) // Funcao que gera os dados do novo elemento da fila
{
	if(fi == NULL){ //Verifica se a fila existe
		printf("Houve um problema com a fila\n");
		exit(1); //Se não existe, o programa acaba
	}
	//Daqui pra frente, vai-se gerar os dados aleatórios do Voo de aterrisagem
	Voo* v = (Voo*)malloc(sizeof(Voo));
	if (v==NULL) //Verifica se foi possível alocar espaço para os dados de Voo
	{
		printf("Nao ha espaco de memoria para contiunar o programa\n");
		exit(1);// Se nao, sai do programa
	}
	v->nome[0] = ('A' + (char)(rand()%26));v->nome[1] =(char)geraRand('A', 'Z');//Gera caracter maiusculo aleatorio segundo tabela ASCII
	int i = 2;
	while(i<6)
	{
		v->nome[i]=('0' + (char)(rand()%10));//Gera numero do código de vôo
		i++;
	}
	v->nome[6] = '\0';
	v->AorD = C; //Especifica se é um vôo de aterrisagem ou decolagem
	if(C == 'A')
		v->prioridade = geraRand(1, 4);//Escolhe aleatoriamente a prioridade de voo
	
	v->prox = NULL; // Elemento recém criado passa a apontar NULL
	return v;
}
Voo* EnderecoPrioridade(FILA* filaAterri, Voo* ptrAnterior)
{
	Voo* ptrAux = filaAterri->inicio;
	while(ptrAux!=NULL)
	{
		ptrAnterior=ptrAux;
		if(ptrAux->prioridade==1)
			return ptrAux;
		ptrAux=ptrAux->prox;
	}
	return ptrAux;
}
int geraAterrisagem(FILA* fi)
{
	Voo* v = dadosVoo(fi, 'A'); // Coloca-se os dados de voo na strcut atraves do ponteiro 
	if(fi->fim == NULL) //Fila vazia
	{
		fi->inicio = v;
		fi->fim = v;
	}
	else
		fi->fim->prox = v; //Ultimo elemento passa a apontar para o novo elemento inserido
	fi->fim = v; //Novo elemento criado passa a ser o fim da fila
	return 1; //Não houve problemas na incersão de elemento
}
int geraDec(FILA* fi)
{
	Voo* dec = dadosVoo(fi, 'D'); // Coloca-se os dados de voo na strcut atraves do ponteiro
	if(fi->fim == NULL) //Fila vazia
		fi->inicio = dec;
	else
		fi->fim->prox = dec; //Ultimo elemento passa a apontar para o novo elemento inserido
	fi->fim = dec; //Novo elemento criado passa a ser o fim da fila
	return 1; //Não houve problemas na incersão de elemento
}
int geraRand(int min, int max)
{
	int r;
	r=min+rand()%(max-min+1);
	return r;
}
void liberaFila(FILA *fi)
{
	if(fi==NULL)
		return;
	Voo* no;
	while (fi->inicio != NULL)
	{
		no = fi->inicio;
		fi->inicio = fi->inicio->prox;
		free(no);
	}
	free (fi);
}
void mostraDados(Voo* v, int reservaPista)
{
	printf("=======================================================================\n");
	printf("||Atendido o voo:%s tipo: %c\t", v->nome, v->AorD);
	printf("Prioridade: %d\tNa pista: %d||\n", v->prioridade, reservaPista);
	printf("=======================================================================\n");
}
void mostraFila(FILA *fi)
{
	//mostra a lista
    Voo* aux;
	aux = fi->inicio;//auxiliar recebe o comeco da fila
    while(aux != NULL){
        printf("Voo: %s\n", aux->nome);
        printf("Prioridade: %d\n", aux->prioridade);   
        printf("Tipo de Voo: %c\n", aux->AorD);
        printf("Endereco: %p\n", aux);
        aux = aux->prox;
    }
}
int removeDaFila(FILA* fi) //Remove na ordem de fila
{
	if(fi->inicio == NULL) //A lista esta vazia, nao ha como remover
		return ERRO;
	Voo* v = fi->inicio;
 	fi->inicio = fi->inicio->prox;
 	if(fi->inicio == NULL) //chegou no fim da fila 
 		fi->fim = NULL;//Ultimo elemento nao existe mais
 	free(v);
 	return OK; //A remocao foi bem sucedida  
}
void removeUrgencia(FILA* filaAterri, Voo* ptrEmerge, Voo* ptrAnterior)
{
	Voo* removedor;
	if(ptrAnterior->prioridade==1) //Quer dizer que ele foi o escolhido
	{
		filaAterri->inicio = ptrAnterior->prox;
	}
	ptrAnterior->prox = ptrEmerge->prox; //Prox do Anterior passa a apontar para o elemento depois do que vai ser eliminado
	removedor = ptrEmerge; //Removedor recebe o elemento a ser removido 
	free(removedor);
}