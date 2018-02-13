 /*
    @author: Caio Eduardo C de Oliveira e Raul S. Menezes
      @nome: sort-vector.c
      @matricula: Caio:         Raul: 16/0017327
 
 
      Programa visa receber 13 valores inteiros e apresentá-los em ordem crescente, decrescente e como foram digitados.
      A técnica requerida é o uso de dois ponteiros de vetores de inteiros.
*/
#include <stdio.h>
 
#define N 4
void recebe_valores(int *vetor)
{
    int i;
    printf("Inclua os inteiros no vetor:\n");
    for(i=0;i<N;i++)
    {
        scanf("%d", &vetor[i]);
    }
}
void mostra_original(int *vetor)
{
    int i;
    printf("Vetor: original.\n");
    for(i=0;i<N;i++)
        printf("Inteiros: %d || Endereco: %p\n", vetor[i], &vetor[i]);
    printf("\n");
}
void ordena_cresc(int* vetorDados)
{
    int i, z;
    int *ptr_cresc = vetorDados, *ultimo_mostrado = vetorDados;
    /*Organiza os endereços contidos nos elementos do vetor ptr_cresc*/
    printf("Vetor em ordem crescente\n");
	for(i=0;i<N;i++)
	{
        z = i;
        if(vetorDados[i+1]>=vetorDados[i] && *ptr_cresc>=*ultimo_mostrado)
        {
            ptr_cresc = &vetorDados[i];
            printf("Banana  ptr_cresc = %d  ultimo_mostrado = %d\n", *ptr_cresc, *ultimo_mostrado);
            for(;z>0;z--){
                if(*ptr_cresc>=vetorDados[z-1]){
                    if(&vetorDados[z-1]==ultimo_mostrado)
                        continue;
                    else
                    {
                        ultimo_mostrado = ptr_cresc;
                        ptr_cresc = &vetorDados[z-1];
                        printf("Banana1     ptr_cresc = %d  ultimo_mostrado = %d\n", *ptr_cresc, *ultimo_mostrado);
                    }
                }
                else    break;
            }
            ultimo_mostrado = ptr_cresc;
        }
        else if(vetorDados[i+1]<vetorDados[i] && *ptr_cresc>=*ultimo_mostrado)
        {
            ptr_cresc = &vetorDados[i+1];
            printf("Maca    ptr_cresc = %d  ultimo_mostrado = %d\n", *ptr_cresc, *ultimo_mostrado);
                for(z;z>0;z--){
                if(*ptr_cresc>=vetorDados[z-1]){
                    if(&vetorDados[z-1]==ultimo_mostrado)
                        continue;
                    else
                    {
                        ultimo_mostrado = ptr_cresc;
                        ptr_cresc = &vetorDados[z-1];
                        printf("Maca1\n");
                    }
                }
                else    break;
            }
            ultimo_mostrado = ptr_cresc;
        }
    	printf("Inteiro: %d || Endereco: %p\n", *ptr_cresc, ptr_cresc);
	}
    printf("\n");
}

 
int main()
{
    int vetorDados[N];
    recebe_valores(vetorDados);
    mostra_original(vetorDados);
    ordena_cresc(vetorDados);
    /*ordena_decres(vetorDados);*/
    printf("\n");
    return 0;
}