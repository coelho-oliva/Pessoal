/*@author: Caio Eduardo Coelho de Oliveira

Objetivo: organizar um vetor utilizando apenas dois ponteiros, sem alterar o vetor original.
*/
#include <stdio.h>
 
#define N 4
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
        printf("Inteiros: %d	||	Endereco: %p\n", vetor[i], &vetor[i]);
    printf("\n");
}
/*void troca(int* (*vetorPonteiros), int x, int i)
{
    int *aux;
    aux = vetorPonteiros[i];
    vetorPonteiros[i] = vetorPonteiros[i+(x)];
    vetorPonteiros[i+(x)] = aux;
}*/
void ordena_cresc(int* vetorDados, int* ptrCresc)
{
    int i, j;
 
    /*Organiza os endereços contidos nos elementos do vetor ptr_cresc*/
    for(i=0;i<N-1;i++)
    {
        if(vetorDados[i] > vetorDados[i+1])
        {
            //troca(vetorPonteiros, 1, i);
        	ptrCresc = &vetorDados[i+1];
	        for(j=i;j>0;j--)
	        {
	            if(vetorDados[j-1]>vetorDados[j])
	            //troca(vetorPonteiros, -1, j);
	            	ptrCresc = &vetorDados[j];	
	            else
	                break; /*Maior eficiencia.*/
	        }	
        }
        /*if(i!=0 && ptrCresc == &vetorDados[i])	//Para que elementos iguais nao sejam considerados diferentes
        {
        	ptrCresc = &vetorDados[i+1];
        }*/
    	printf("%d\n", *ptrCresc);
    }
}
/*void ordena_decres(intvetorPonteiros)
{
    int* aux;
    int i, j;
    /*Organiza os endereços contidos nos elementos do vetorPonteiros/
    for(i=0;i<N-1;i++)
    {
        if(*(vetorPonteiros)[i]<*(vetorPonteiros)[i+1])
            troca(vetorPonteiros, 1, i);
        for(j=i;j>0;j--)
        {
            if(*(vetorPonteiros)[j]>*(vetorPonteiros)[j-1])
                troca(vetorPonteiros, -1, j);
            else
                break;
        }
    }
    printf("Vetor em ordem decrescente.\n");
    for(i=0;i<N;i++)
        printf("Inteiros: %d || Endereco: %p\n", *vetorPonteiros[i], vetorPonteiros[i]);
    printf("\n");*/

 
int main()
{
    int vetorDados[N];
    int *ptrCresc;
    /*recebe valores no vetor*/
    recebe_valores(vetorDados);
    mostra_original(vetorDados);
    ptrCresc = vetorDados;
    ordena_cresc(vetorDados, ptrCresc);
    /*ordena_decres(vetorPonteiros);*/
    printf("\n");
    return 0;
}