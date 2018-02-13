/***
    @author: Caio Eduardo C de Oliveira e Raul S. Menezes
      @nome: encontraPlagio.c
      @matricula: Caio: 16/0003679    Raul: 16/0017327
 
      Programa visa simular um aeroporto, com três pistas para atender aterrissagens e decolagens .
      A técnica requerida é o uso de filas para armazenar os voos criados e atendê-los na estratégia de fila, ou seja o primeiro elemento é o primeiro a ser atendido.
      Obs: A terceira pista atende apensas emergências. ||||||
      obs2: Em caso de emergências em posições anteriores ao primeiro da fila, esses voos de emergência "furam a fila" e são atendidos primeiro.
***/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define AproxMAX 28
#define DecMAX 28
#define true 1
#define false 0

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
struct tm*timeinfo;
//typedef struct tm * timeinfo;
typedef struct fila FILA;
void atendimento(FILA *filaAterri, FILA *filaDec);
int checaPrioridade(FILA* filaAterri);
FILA* criaFila();
int estaVazia(FILA* ptrFila);
Voo* geraDadosVoo(FILA* fi, char C);
void diminuiGas(FILA* filaAterri);
Voo* EnderecoPrioridade(FILA* filaAterri);
int geraAterrisagem(FILA* fi);
int geraDec(FILA* fi);
int geraRand(int min, int max);
void liberaFila(FILA *fi);
void mostraDados(Voo* v, int contPistas);
void mostraFila(FILA *fi);
void removeDaFila(FILA *fi);
//void removeUrgencia(Voo* ptrEmerge, Voo* ptrAnterior);
void removeElemento(Voo* ptrAnteriorEmerg, FILA* fila, int reservaPista);


int main ()
{
	srand(time(NULL));
	time_t rawtime=time(NULL);
  	time ( &rawtime );


	FILA *filaAterri, *filaDec;
	int nAprox, nDec;
	FILE* resultadoAtendimento;
	resultadoAtendimento = fopen("Atendimentos.txt", "w+");//Cria o arquivo ou apaga tudo que havia num arquivo com mesmo nome criado anteriormente
	if (resultadoAtendimento==NULL)
	{
		printf("Nao foi possivel gerar arquivo para armazenar os dados de atendimento!!!\nSair do programa\n");
		exit(1);
	}
	//Aterrissagens e Decolagens
	filaAterri = criaFila();
	nAprox = geraRand(0, AproxMAX);
	filaDec = criaFila();
	nDec = geraRand(0, DecMAX);

	rawtime = time(NULL);
	timeinfo = localtime(&rawtime);
	printf("			Aeroporto Internacional de Gotham City.\n");
	printf("Horario local:		%s", asctime(timeinfo));
	printf("Numero de voos:		%d\n", nAprox+nDec);
	printf("Quantidade de aproximaçoes:		%d\n", nAprox);
	printf("Quantidade de decolagens:		%d\n", nDec);
	while(nAprox>0 && (geraAterrisagem(filaAterri)))//Verifica se conseguiu inserir um voo aleatório na fila
		nAprox--;
	while(nDec>0 && (geraDec(filaDec)))//Verifica se conseeguiu inserir um voo aleatório na fila
		nDec--;
	//Atendimento das duas filas 
	atendimento(filaAterri, filaDec);
	liberaFila(filaAterri); liberaFila(filaDec); // Libera os ponteiros de fila
	fclose(resultadoAtendimento);//Fecha o arquivo usado para anotar os atendimentos
	return 0;
}
void atendimento(FILA* filaAterri, FILA* filaDec)
{
	int reservaPista, urgencias;
	Voo* ptrAnteriorEmerg;
	while (filaAterri->inicio!=NULL || filaDec->inicio != NULL)
	{
		reservaPista = 0;
		urgencias = checaPrioridade(filaAterri); //retorna quantos valores de prioridade maxima existem
		while(urgencias) //Atende as urgências || Teve urgência, ou seja, a fila não está vazia
		{
			reservaPista++; // Reserva a pista para pouso
			ptrAnteriorEmerg = EnderecoPrioridade(filaAterri); //Encontra onde há emergência e salva o elemento anterior
			removeElemento(ptrAnteriorEmerg, filaAterri, reservaPista);
			urgencias--;
		}
		while (reservaPista<2 && ( !estaVazia(filaDec) || !estaVazia(filaAterri) )) //Enquanto há pistas para usar e voos nas filas para atender, atenda 
		{
			if (!estaVazia(filaDec) && reservaPista<2) //Se tem voos de decolagem para atender e pistas, atende o voo
			{
				reservaPista++; //Reserva a primeira fila para decolagem
				mostraDados(filaDec->inicio, reservaPista); //Mostra os dados do primeiro da fila de decolagem, que sera atendido na pista reservada
				removeDaFila(filaDec);//Atende uma decolagem, remove o primeiro da fila 
			}
			if(!estaVazia(filaAterri) && reservaPista<2) // Se tem pistas e voos de aterrissagem, atende 
			{
				reservaPista++; // Reserva mais uma pista, agora para aterrissagem
				mostraDados(filaAterri->inicio, reservaPista); //Mostra os dados do primeiro da fila de aterrissagem, que sera atendido na pista reservada
				removeDaFila(filaAterri);//Atende uma aterrissagem, já que já atendeu uma decolagem acima. Remove o primeiro da fila 
			}
		}
		diminuiGas(filaAterri);
	}
}
int checaPrioridade(FILA* filaAterri)
{
	int urgencias=0;
	Voo* ptrEmerg = filaAterri->inicio;
	while(ptrEmerg!=NULL)
	{
		if(ptrEmerg->prioridade == 1)
			urgencias++;
		ptrEmerg = ptrEmerg->prox;
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
void diminuiGas(FILA* filaAterri)
{
	if(!estaVazia(filaAterri))
	{
		Voo* aux = filaAterri->inicio; //Auxiliar recebe o primeiro elemento
		while (aux!=NULL) //Enquanto a fila nao acaba 
		{
			aux->prioridade--; //Diminui a prioridade, ou seja, reduz o combustível das aeronaves 
			aux=aux->prox; // Percorre o próximo elemento da fila
		}
	}
}
int estaVazia(FILA* ptrFila)
{
	if(ptrFila->inicio == NULL)
		return true;
	return false;
}
Voo* geraDadosVoo(FILA* fi, char C) // Funcao que gera os dados do novo elemento da fila
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
	else
		v->prioridade = 0;	
	v->prox = NULL; // Elemento recém criado passa a apontar NULL
	return v;
}
Voo* EnderecoPrioridade(FILA* filaAterri)
{
	Voo *ptrAnteriorEmerg = filaAterri->inicio;
	if (filaAterri->inicio->prioridade==1) //Prioridade no começo
		return filaAterri->inicio; //Retorna começo da fila para usar removeDaFila
	while(ptrAnteriorEmerg!=NULL)
	{
		if(ptrAnteriorEmerg->prox->prioridade==1)//Encontrou emergência
			return ptrAnteriorEmerg; //Retorna anterior ao de prioridade máxima
		ptrAnteriorEmerg = ptrAnteriorEmerg->prox; //Aponta para o proximo elemento na fila
	}
	return NULL;
}

int geraAterrisagem(FILA* fi)
{
	Voo* v = geraDadosVoo(fi, 'A'); // Coloca-se os dados de voo na strcut atraves do ponteiro 
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
	Voo* dec = geraDadosVoo(fi, 'D'); // Coloca-se os dados de voo na strcut atraves do ponteiro
	if(fi->fim == NULL) //Fila vazia
		fi->inicio = dec;
	else
		fi->fim->prox = dec; //Ultimo elemento passa a apontar para o novo elemento inserido
	fi->fim = dec; //Fim da fila passa a apontar para o elemento criado
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
	sleep(2);
	time_t rawtime = time(NULL);
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	FILE* resultadoAtendimento;
	resultadoAtendimento = fopen("Atendimentos.txt", "a+");
	if (resultadoAtendimento==NULL)
	{
		printf("Nao foi possivel gerar arquivo para armazenar os dados de atendimento!!!\nSair do programa\n");
		exit(1);
	}
	if(reservaPista<=3) //Atendimento no nosso aeroporto
	{
		//Imprime no terminal
		printf("\t\tAtendido o voo:%s Tipo: %c\tVoo previsto para: %s", v->nome, v->AorD, asctime(timeinfo));
		printf("Prioridade: %d\tNa pista: %d||\n", v->prioridade, reservaPista);
		//Imprime no arquivo 
		fprintf(resultadoAtendimento, "||Atendido o voo:%s Tipo: %cVoo previsto para: %s\t", v->nome, v->AorD, asctime(timeinfo));
		fprintf(resultadoAtendimento, "Prioridade: %d\tNa pista: %d\n", v->prioridade, reservaPista);
	}
	else //Desvio de aeronave, as três pistas já foram ocupadas 
	{
		//Imprime no terminal
		printf("============================================================\n");
		printf("||          ALERTA GERAL DE DESVIO DE AERONAVE            ||\n");
		printf("||       Voo desviado:  %s\t  do Tipo:    %c\t   \t||\n", v->nome, v->AorD);
		printf("||       Horario do voo: %s\n", asctime(timeinfo));
		printf("============================================================\n");
		//Imprime no arquivo
		fprintf(resultadoAtendimento, "============================================================\n");
		fprintf(resultadoAtendimento, "||          ALERTA GERAL DE DESVIO DE AERONAVE            ||\n");
		fprintf(resultadoAtendimento, "||       Voo desviado:  %s\t  do Tipo:\t%c\t  \t||\n", v->nome, v->AorD);
		fprintf(resultadoAtendimento, "||       Horario do voo: %s\n", asctime(timeinfo));

		fprintf(resultadoAtendimento, "============================================================\n");
	}
	fclose(resultadoAtendimento); //Fecha o ponteiro que aponta para o arquivo
}
void mostraFila(FILA *fi)
{
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
void removeDaFila(FILA* fi)
{
	if(fi->inicio == NULL) //A lista esta vazia, nao ha como remover
		return;
	Voo* v = fi->inicio;
	fi->inicio = fi->inicio->prox;
 	if(fi->inicio == NULL) //chegou no fim da fila 
 		fi->fim = NULL;//Ultimo elemento nao existe mais
 	free(v); 
}
void removeElemento(Voo* ptrAnteriorEmerg, FILA* fila, int reservaPista)
{
	Voo* removedor;
	if (fila->inicio->prioridade == 1) // anterior == emergencia também
	{
		mostraDados(fila->inicio, reservaPista);
		removeDaFila(fila);
	}
	else
	{
		mostraDados(ptrAnteriorEmerg->prox, reservaPista);
		removedor = ptrAnteriorEmerg->prox; //Removedor recebe a emergencia
		ptrAnteriorEmerg->prox = ptrAnteriorEmerg->prox->prox; //Anterior passa a apontar para o elemento depois do de prioridade maxima 
		free(removedor);
	}
}