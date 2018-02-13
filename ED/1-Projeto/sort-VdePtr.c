/*
    	 @author: Caio Eduardo C de Oliveira e Raul S. Menezes
      	   @nome: sort-vector.c
      @matricula: Caio: 16/0003679        Raul: 16/0017327
 
 
      Programa visa receber 13 valores inteiros e apresentá-los em ordem crescente, decrescente e como foram digitados.
      A técnica requerida é o uso de dois ponteiros de vetores de inteiros.
*/
#include <stdio.h>
 
#define N 17
void recebe_valores(int *vetor)
{
    int i;
    printf("Inclua os inteiros no vetor:\n");
    for(i=0;i<N;i++)
        scanf("%d", &vetor[i]);
}
void mostra_original(int *vetor)
{
    int i;
    printf("Vetor: original.\n");
    for(i=0;i<N;i++)
        printf("Inteiros: %d || Endereco: %p\n", vetor[i], &vetor[i]);
    printf("\n");
}
void troca(int* (*vetorPonteiros), int x, int i)
{
    int *aux;
    aux = vetorPonteiros[i];
    vetorPonteiros[i] = vetorPonteiros[i+(x)];
    vetorPonteiros[i+(x)] = aux;
}
void ordena_cresc(int* *vetorPonteiros)
{
    int* aux;
    int i, j;
 
    /*Organiza os endereços contidos nos elementos do vetor ptr_cresc*/
    for(i=0;i<N-1;i++)
    {
        if(*(vetorPonteiros)[i]>*(vetorPonteiros)[i+1])
        {
            troca(vetorPonteiros, 1, i);
	        for(j=i;j>0;j--){
	            if(*(vetorPonteiros)[j]<*(vetorPonteiros)[j-1])
	                troca(vetorPonteiros, -1, j);
	            else
	                break; /*Usado para diminuir o esforço do programa de percorrer todo o vetor*/
	        }
    	}
    }
    printf("Vetor em ordem crescente.\n");
    for(i=0;i<N;i++)
        printf("Inteiros: %d || Endereco: %p\n", *vetorPonteiros[i], vetorPonteiros[i]);
    printf("\n");
}
void ordena_decres(int* *vetorPonteiros)
{
    int* aux;
    int i, j;
    /*Organiza os endereços contidos nos elementos do vetorPonteiros*/
    for(i=0;i<N-1;i++)
    {
        if(*(vetorPonteiros)[i]<*(vetorPonteiros)[i+1])
        {
            troca(vetorPonteiros, 1, i);
	        for(j=i;j>0;j--)
	        {
	            if(*(vetorPonteiros)[j]>*(vetorPonteiros)[j-1])
	                troca(vetorPonteiros, -1, j);
	            else
	                break;/*Usado para diminuir o esforço do programa de percorrer todo o vetor, já que os elementos anteriores não são maiores que o atual*/
	        }
    	}
    }
    printf("Vetor em ordem decrescente.\n");
    for(i=0;i<N;i++)
        printf("Inteiros: %d || Endereco: %p\n", *vetorPonteiros[i], vetorPonteiros[i]);
    printf("\n");
}

 
int main()
{
    int vetorDados[N];
    int *vetorPonteiros[N];
    /*recebe valores no vetor*/
    recebe_valores(vetorDados);
    int i;
    for(i=0;i<N;i++)
        vetorPonteiros[i] = &(vetorDados[i]);
    mostra_original(vetorDados);
    ordena_cresc(vetorPonteiros);
    ordena_decres(vetorPonteiros);
    printf("\n");
    return 0;
}