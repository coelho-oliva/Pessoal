/*
	   @authors:	Caio Eduardo Coelho de Oliveira e Raul Silva Menezes
	@matriculas:	16/0003679	e 	16/0017327
		 @flags:	gcc -Wall
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define d 0.85
#define KGRN  "\x1B[32m"
#define KNRM  "\x1B[0m"
#define KBLU  "\x1B[36m"
#define KRED  "\x1B[31m"

typedef char NOME[50];

typedef struct NODE
{
	NOME nome;
	float rank; int qtdAmigos;
	struct listaAmigos* links, *backlinks; // Quem o noh aponta
	struct NODE *prox;
}NODE;

typedef struct listaAmigos
{
	NODE *amigo;
	struct listaAmigos *prox;
}listaAmigos;

void 			achaBackLinks(NODE* node);
void 			calcPR(NODE* node);
listaAmigos* 	criaAmigo();
NODE* 			criaLista();
void 			encontraNovaLinha(FILE *fp);
void 			imprimeGrafo(NODE* node);
void 			interacaoUsuario(NODE* node);
NODE* 			leArquivo();
void 			leTeclado();
void		 	liberaGrafo(NODE* node);
NODE* 			ordenaNos(NODE* ptrGrafo);
int 			pega1Palavra(FILE *fp, NOME aux);
NODE* 			rankeia(NODE* node);
void			removeLIXO(NODE* node);
void 			RemoveNonAlpha(char* source);

void achaBackLinks(NODE* node)
{
	NODE* aux, *aux2;
	aux = node;
	listaAmigos *finder, *AuxBacklinks;
	while(aux->prox!=NULL)
	{
		aux2 = node; AuxBacklinks = aux->backlinks;
		while(aux2!=NULL)
		{
			finder = aux2->links;
			while(finder!=NULL){
				if(aux==finder->amigo){
					AuxBacklinks->amigo = aux2;
					AuxBacklinks->prox = criaAmigo();
					AuxBacklinks = AuxBacklinks->prox;
					break;
				}
				finder = finder->prox;
			}
			aux2 = aux2->prox;
		}
		aux = aux->prox;
	}
}
void calcPR(NODE* node)
{
	NODE* aux;
	aux = node;
	listaAmigos *backlinks;
	float SUM;
	while(aux->prox!=NULL) //Vai calcular o PR de todos ate o fim da lista
	{
		SUM = 0;
		backlinks = aux->backlinks;
		while(backlinks->prox!=NULL){
			SUM += ((backlinks->amigo->rank)/(1.0*(backlinks->amigo->qtdAmigos)));
			backlinks = backlinks->prox;
		}
		aux->rank = ((1-d) + d*(SUM));
		aux = aux->prox;
	}
}
NODE* criaLista()
{
	NODE* node;
    node = (NODE*) malloc(sizeof(NODE));
    node->links = criaAmigo();
    node->backlinks = criaAmigo();
    node->rank = 1; node->qtdAmigos = 0; node->prox = NULL;
	return node;
}
listaAmigos* criaAmigo()
{
	listaAmigos* bro = (listaAmigos*)malloc(sizeof(listaAmigos));
	bro->amigo = NULL;
	bro->prox = NULL;
	return bro;
}
int pega1Palavra(FILE *fp, NOME aux)
{
	int i; char c = '*';aux[0] = '\0';
	int ultimo = 0;
	for (i=0; i<50; i++)
	{
		if(feof(fp)){
			if(isalpha(aux[0])){
				ultimo=1;
				break;
			} 
			else
				return 0;
		}
		c = fgetc(fp);
		if(c == ':' || c == ',')
			break;
		if(c == '\n'){
			if(isalpha(aux[0])){
				ultimo=1;
				break;
			} 
			else
				return 0;
		}
		aux[i] = c;
		if(c == ' ')
			i--;
	}
	aux[i] = '\0';
	RemoveNonAlpha(aux);
	if(ultimo)
		return 2;
	return 1;
}
void encontraNovaLinha(FILE *fp)
{
	char c;
	while(1)
	{
		if(feof(fp)){
			break;
		}
		c = fgetc(fp);
		if(c == '\n')
			break;
	}
}
void imprimeGrafo(NODE* node)
{
	NODE *auxNode = node;
	listaAmigos *auxLis;
	while(auxNode!=NULL)
	{
		auxLis = auxNode->links;
		printf(KBLU "|%s: " KNRM, auxNode->nome);
		printf("Numero de Amigos = %d\tPage Rank: %.5f\nAmigos:", auxNode->qtdAmigos, auxNode->rank);
		while(auxLis!=NULL){
			printf(", %s", auxLis->amigo->nome);
			auxLis = auxLis->prox;
		}
		printf("\nBacklinks:");
		auxLis = auxNode->backlinks;
		while(auxLis!=NULL){
			printf("-> %s ", auxLis->amigo->nome);
			auxLis = auxLis->prox;
		} printf("|\n");
		if(auxNode->prox!=NULL)
			printf("\n");
		auxNode = auxNode->prox;
	}
}
void interacaoUsuario(NODE* node)
{
	int verifica;
	FILE* fp;
	do{
		printf(KGRN "Voce deseja que o programa crie a rede de amigos pelo teclado ou por um arquivo?\n" KNRM);
		printf("(1) TECLADO\n(2) ARQUIVO\n");
		setbuf(stdin, NULL);
		scanf("%d", &verifica); 
		switch(verifica){
			case 1 :
				leTeclado();
				fp = fopen("UserEntry.txt", "r");
				node = leArquivo(fp);
				achaBackLinks(node);
				printf(KBLU "Lista de todas as pessoas na rede.\n");
				imprimeGrafo(node);
				printf(KGRN "Calculando Page Ranks...\n");
				sleep(2);
				removeLIXO(node);
				node = rankeia(node);
				printf(KBLU "Lista ordenada por ordem decrescente de PRs.\n");
				imprimeGrafo(node);
				break;
			case 2 :
				printf("Digite o nome do arquivo.\nEx.: entProj7ED20171.txt\n");
				NOME arquivo;	scanf("%s", arquivo);
				fp = fopen(arquivo, "r");	
				node = leArquivo(fp);
				achaBackLinks(node);
				printf(KBLU "Lista de todas as pessoas na rede.\n");
				imprimeGrafo(node);
				printf(KGRN "Calculando Page Ranks...\n");
				sleep(2);
				removeLIXO(node);
				node = rankeia(node);
				printf(KBLU "Lista ordenada por ordem decrescente de PRs.\n");
				imprimeGrafo(node);
				break;
			default :
				printf(KRED "Opcao invalida\n");
		}
	}while(verifica!=1 && verifica!=2);
}
NODE* leArquivo(FILE *fp)
{
	NODE *aux, *node = criaLista();
	NOME amigo;
	aux = node; 
	while(!feof(fp)) //Le os primeiros nomes
	{
		if(!pega1Palavra(fp, amigo)){
			continue;
		}
		strcpy(aux->nome, amigo);
		if(!feof(fp)){
			encontraNovaLinha(fp);
		}
		else
			break;
		aux->prox = criaLista();
		aux = aux->prox;
	}
	// Salva adjacencias
	fseek(fp, 0, SEEK_SET); //Volta para o comeco do arquivo
	NODE *aux2;
	aux = aux2 = node;
	listaAmigos *AuxLinks; int continua;
	while(!feof(fp))
	{
		pega1Palavra(fp, amigo); //Percorre até os dois pontos
		AuxLinks = aux->links; //Inicializa a lista de amigos com o endereco da lista de amigos do no atual
		//Percorre até a próxima linha, salvando o nome dos amigos
		continua = pega1Palavra(fp, amigo);
		while(continua!=0) //Caso pegue um nome, há um amigo, retorna 1; Else-> retorna 0
		{
			aux2 = node; //Auxiliar recebe o comeco da lista
			aux->qtdAmigos++;//Encontrou um amigo o valor de Cn(Tn) (aka qtdAmigos) aumenta
			while(1)
			{
				if((strcmp(amigo, aux2->nome)!=0)){ //Encontra no amigo
					aux2 = aux2->prox; //Encontra noh que tem o nome do amigo
					if(aux2==NULL)
						break;
				}
				else{
					AuxLinks->amigo = aux2;
					AuxLinks->prox = criaAmigo();
					AuxLinks = AuxLinks->prox;
					break;
				}
			}
			if(continua==2)
				break;
			continua = pega1Palavra(fp, amigo);
		}
		aux = aux->prox; //Percorre linearmente a lista
	}
	aux = NULL; fclose(fp);
	return node;
}
void leTeclado()
{
	char fimAmigos, TerminaNomes;
	int PrimeiroAmigo, verifica = 1;
	FILE *fp = fopen("UserEntry.txt", "w+"); fclose(fp);
	fp = fopen("UserEntry.txt", "a+");
	NOME nome;
	fimAmigos = TerminaNomes = 'n';
	do{
		printf("Digite o nome da pessoa:\n"); 
		printf(KBLU "Obs.: Para que o programa funcione corretamente, e´ necessario que sejam criados espacos para todas as pessoas que estao na rede.\n");
		setbuf(stdin, NULL);
		scanf("%[a-z A-Z]s", nome);	//Assim, lera tudo o que for letra ou espaco 
		fprintf(fp, "%s:", nome);
		//Le os amigos da pessoa
		PrimeiroAmigo = 1;
		do{
			do{
				//Verifica se a pessoa ainda tem amigos
				printf(KNRM "Tem amigo(s) para adicionar??\n(1) Sim\n(2) Nao\n");
				setbuf(stdin, NULL);
				scanf("%d", &verifica);
				switch(verifica)
				{
					case 1 :
						fimAmigos = 'n';
						if(PrimeiroAmigo)
						{
							fprintf(fp, " ");
							PrimeiroAmigo = 0;
						}
						else
							fprintf(fp, ", ");
						break;
					case 2 :
						fimAmigos = 's';
						fprintf(fp, "\n");
						break;
					default :
						printf(KRED "Opcao invalida\n");
				}
			}while(verifica!=1 && verifica!=2);
			if(fimAmigos=='s')
				break;
			printf("Digite o nome do amigo dessa pessoa:\n");
			setbuf(stdin, NULL);//Le o nome do amigo
			scanf("%[a-z A-Z]s", nome); 
			fprintf(fp, "%s", nome); //Escreve esse nome no arquivo
		}while(fimAmigos=='n');
		// Verifica se o usuario ainda quer adicionar mais nomes
		do{
			printf("Faltam nomes para adicionar na lista??\n(1) Sim\n(2) Nao\n");
			setbuf(stdin, NULL);
			scanf("%d", &verifica);
			switch(verifica){
				case 1 :
					TerminaNomes = 'n';
					break;
				case 2 :
					TerminaNomes = 's';
					break;
				default :
					printf(KRED "Opcao invalida\n");
			}
		}while(verifica!=1 && verifica!=2);
	}while(TerminaNomes=='n');
	fclose(fp);
}
void liberaGrafo(NODE* node)
{
	if(node!=NULL)
		liberaGrafo(node->prox);
	free(node);
}
NODE* ordenaNos(NODE* ptrGrafo)
{
	if(ptrGrafo->prox->prox == NULL)
        return ptrGrafo;
    NODE *curr, *largest, *largestPrev, *prev;
    curr = ptrGrafo;
    largest = ptrGrafo;
    prev = ptrGrafo;
    largestPrev = ptrGrafo;
    while(curr != NULL) 
    {
    	if(curr->rank > largest->rank) {
    	    largestPrev = prev;
    	    largest = curr;
        }
        prev = curr;
        curr = curr->prox;
    }
    NODE* tmp;
    if(largest != ptrGrafo){
        largestPrev->prox = ptrGrafo;
        tmp = ptrGrafo->prox;
        ptrGrafo->prox = largest->prox;
        largest->prox = tmp;
    }
    largest->prox = ordenaNos(largest->prox);
    return largest;
}
NODE* rankeia(NODE* node)//Calcula o PR N vezes, onde N eh o tamanho da lista de elementos
{
	NODE* aux = node;
	while(aux->prox!=NULL){
		calcPR(node);
		aux = aux->prox;
	}
	return ordenaNos(node);
}
void RemoveNonAlpha(char* source)
{
  char* i = source;
  char* j = source;
  while(*j != 0)
  {
    *i = *j++;
    if(isalpha(*i))
      i++;
  }
  *i = 0;
}
//Flag: nao remove o lixo, que esta localizado no ultimo elemento da lista.
void removeLIXO(NODE *node)
{
	NODE *prev, *aux = node;
	while(aux!=NULL)
	{
		if(strcmp(aux->nome, "\0") == 0)
		{
			printf("Entrou aqui\tNome: %s\tEndereco: %p\n", aux->nome, aux);
			NODE* lixo = aux;
			prev->prox = NULL;
			sleep(1);
			free(lixo);		
		}
		else
			prev = aux;
			aux = aux->prox;
	}
}