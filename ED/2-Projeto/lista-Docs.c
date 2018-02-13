/*
Le dois arquivos e compara suas semelhanças.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#define PI 3.141592653

typedef char string[30];
typedef struct celula
{
	int frequencia;
	string palavra;
	struct celula* prox;
}celula;
//Functions Declaration
FILE 	*abreArquivo(int num_arquivo);
void	criaResultado(celula* ptrLista1, celula* ptrLista2);
celula 	*iniciaLista();
void 	insert(celula *list, string newWord);
void 	findsWord(celula *ptrLista, string WordFromFile);
void 	liberaLista(celula *list);
double 	moduloVetorial(celula* ptrLista);
celula* OrdenaDecrescente(celula* ptrLista);
int 	produtoEscalar(celula *ptrLista1, celula *ptrLista2);
int 	tamanhoLista(celula* ptrLista);

int main()
{
	string pal_arquivo;
	FILE *arq1, *arq2;
	celula *ptrLista1, *ptrLista2;
	arq1 = abreArquivo(1);
	if (arq1==NULL)
	{
		printf("Nao foi possivel abrir o arquivo\n");
		return EXIT_FAILURE;
	}
	ptrLista1 = iniciaLista();
	while((fscanf(arq1, "%s", pal_arquivo))!= EOF)
		findsWord(ptrLista1, pal_arquivo);
	
	fclose (arq1);
	int tamanho;
	tamanho = tamanhoLista(ptrLista1);
	printf("Tamanho da lista criada para o arquivo 1:	%d\n", tamanho);

	arq2 = abreArquivo(2);
	if (arq2==NULL)
	{
		printf("Nao foi possivel abrir o arquivo\n");
		return EXIT_FAILURE;
	}
	ptrLista2 =	iniciaLista();
	while((fscanf(arq2, "%s", pal_arquivo))!= EOF)
		findsWord(ptrLista2, pal_arquivo);
	fclose (arq2);
	tamanho = tamanhoLista(ptrLista2);
	printf("Tamanho da lista criada para o arquivo 2:	%d\n", tamanho);
	sleep(1);

	//Ordena as listas por frequencia
	ptrLista1 = OrdenaDecrescente(ptrLista1);
	ptrLista2 = OrdenaDecrescente(ptrLista2);
	printf("Listas ordenadas.\n");
	sleep(1);

	//Calcula o angulo entre os vetores-lista
	criaResultado(ptrLista1, ptrLista2);
	liberaLista(ptrLista1);
	liberaLista(ptrLista2);
	return 0;
}

//lib.
FILE* abreArquivo (int num_arquivo)
{
	string nome;
	FILE *fp;
	printf("Digite o nome do arquivo %d:\n", num_arquivo);
	scanf("%s", nome);
	fp = fopen(nome, "r");
	if (fp==NULL)
		return NULL;
	return fp;
}
void criaResultado(celula* ptrLista1, celula* ptrLista2)
{
	FILE* fp;
	char arquivo[] = "compararDoc.txt";
	fp = fopen(arquivo, "w+");
	double angulo, modulo, razao;
	int produto;
	produto = produtoEscalar(ptrLista1, ptrLista2);
	modulo = (moduloVetorial(ptrLista1))*(moduloVetorial(ptrLista2));
	razao = produto/modulo;
	angulo = acos(razao);
	fprintf(fp, "Tamanho das listas criadas:\n1)%d palavras;\n",tamanhoLista(ptrLista1));
	fprintf(fp, "2)%d palavras\n", tamanhoLista(ptrLista2));
	fprintf(fp, "Produto interno das listas:	%d\n", produto);
	fprintf(fp, "Produto dos modulos: %.5lf\n", modulo);
	fprintf(fp, "Produto/Modulo: 	%lf\nAngulo entre vetores:	%.3lf radianos\n", razao, angulo);
	//Mostra resultado no terminal.
	if(angulo <= PI/4)
		printf("Alerta: os arquivos sao extremamente semelhantes, configurando plagio.\n");
	else
		printf("Os arquivos sao diferentes. Yay! :)\n");
	
	fprintf(fp, "\nLista de palavras com suas respectivas frequencias.\n--Lista 1 ordenada.\nFrequencia		||	Palavras\n");
	while(ptrLista1!=NULL)
	{
		if(strcmp(ptrLista1->palavra, "CabecaDaLista")==0)
		{
			ptrLista1=ptrLista1->prox;
			continue;
		}
		fprintf(fp, "%d					%s\n", ptrLista1->frequencia, ptrLista1->palavra);
		ptrLista1=ptrLista1->prox;
	}
	fprintf(fp, "--Lista 2 ordenada.\nFrequencia	||	Palavras\n");
	while(ptrLista2!=NULL)
	{
		if(strcmp(ptrLista2->palavra, "CabecaDaLista")==0)
		{
			ptrLista2=ptrLista2->prox;
			continue;
		}
		fprintf(fp, "%d					%s\n", ptrLista2->frequencia, ptrLista2->palavra);
		ptrLista2=ptrLista2->prox;
	}
	fclose(fp);
}
celula* iniciaLista()
{
	celula* ptrLista;
	ptrLista = (celula*) malloc(sizeof(celula));
	ptrLista->frequencia = 0;
	strcpy(ptrLista->palavra, "CabecaDaLista");
	ptrLista->prox = NULL; //fim da lista
	return ptrLista;
}
void insert(celula* ptrLista, string novaPalavra)
{	
	celula* novoElemento;
	novoElemento = (celula*) malloc(sizeof(celula));
	novoElemento->frequencia = 1;
	strcpy(novoElemento->palavra, novaPalavra);
	novoElemento->prox = ptrLista->prox;
	ptrLista->prox = novoElemento;	
}
void findsWord(celula *ptrLista, string WordFromFile)
{
	celula* finder;
	finder = ptrLista;
	while(finder != NULL && strcmp(WordFromFile, finder->palavra))
	{
		finder = finder->prox;
	}
	if(finder == NULL){
		insert(ptrLista, WordFromFile);
	}
	else
		finder->frequencia++;
}
void liberaLista(celula* list)
{
	if (list!=NULL)
	{
		liberaLista(list->prox);
		free(list);
	}
}
double moduloVetorial(celula *ptrLista)
{
	double modulo=0;
	while(ptrLista!=NULL){
		modulo += pow(ptrLista->frequencia, 2);
		ptrLista = ptrLista->prox;
	}
	return sqrt(modulo);
}
celula* OrdenaDecrescente(celula* ptrLista) 
{
	if(ptrLista == NULL)
	    return ptrLista; // the list is sorted.
	//1- find largest node. 
	celula *curr, *largest, *largestPrev, *prev;
	curr = ptrLista;
	largest = ptrLista;
	prev = ptrLista;
	largestPrev = ptrLista;
	while(curr != NULL) {
        if(curr->frequencia > largest->frequencia) {
            largestPrev = prev;
            largest = curr;
        }
        prev = curr;
        curr = curr->prox;
    }
	//2- switching firt node and largest node : 
	celula* tmp;
	if(largest != ptrLista)
	{
	    largestPrev->prox = ptrLista;
	    tmp = ptrLista->prox;
	    ptrLista->prox = largest->prox;
	    largest->prox = tmp;
	}

	// now largest is the first node of the list.

	// calling the function again with the sub list;
	//            list minus its first node.
	largest->prox = OrdenaDecrescente(largest->prox);


	return largest;
}
int produtoEscalar(celula *ptrLista1, celula *ptrLista2)
{
    int D1escalarD2 = 0;
    celula *comp = ptrLista2;
    //comparar as palavras da lista
    while(ptrLista1->prox != NULL)//percorre a primeira lista, elemento por elemento
    {
        while(comp->prox!=NULL && (strcmp(ptrLista1->palavra, comp->palavra)!=0))
            comp = comp->prox;
        if (comp->prox == NULL)//Se não tem a palavra igual, o produto dessas componentes vale zero
                D1escalarD2 += 0;
        else //Achou as palavras iguais, multiplica as frequencias
                D1escalarD2 += ptrLista1->frequencia*comp->frequencia;
        ptrLista1 = ptrLista1->prox;
        comp = ptrLista2;
    }
    return D1escalarD2;
}
int tamanhoLista(celula* ptrLista)
{
	int contador=0;
	while(ptrLista!=NULL){
		contador++;
		ptrLista = ptrLista->prox;
	}
	return contador;
}