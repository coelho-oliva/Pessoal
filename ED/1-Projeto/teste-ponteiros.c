/*
Teste comportamento de ponteiros*/
#include <stdio.h>
#define N 4
void mostraPtrFunc(int* (*ponteiros))
{
	int i;
	printf("Lendo com %%p:\n");
	for(i=0;i<N;i++)
		printf("%p\n", ponteiros[i]);
}
void mostraVetor(int* vetor)
{
	int i;
	printf("Vetor original.\n");
	for(i=0;i<N;i++)
		printf("%d	%p\n", vetor[i], &vetor[i]);
}

int main()
{
	int vetor[N], i;
	int* enderecos_do_vetor[N];

	printf("Insert vector elements\n");
	for(i=0;i<N;i++)
	{
		scanf("%d", &vetor[i]);
		enderecos_do_vetor[i] = &vetor[i];
	}
	mostraVetor(vetor);

	printf("Dentro da main:\n");
	for(i=0;i<N;i++)
		printf("%p\n", enderecos_do_vetor[i]);

	printf("Pela funcao:\n");
	mostraPtrFunc(enderecos_do_vetor);

	return 0;
}