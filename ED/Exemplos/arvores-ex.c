/*
Exercicio de arvore binaria
1- Cria uma arvore;
2- Inclui elementos;
3- Exclui elementos;
4- Apaga arvore;

*/
#include <stdio.h>
#include <stdlib.h>

typedef struct No{
	int conteudo, marcador;
	struct No *esquerda, *direita;
} laco;

#define true 1
#define false 0

int 	 ArvContemSoma(laco *ptrArvore, int somaProcurada);
laco* 	 ArvCriaRaiz(int conteudo);
laco*	 ArvInsere(laco *ptrArvore, int conteudo);
void	 ArvLibera(laco *ptrArvore);
void	 ArvMostra(laco *ptrArvore);
laco* 	 ArvNovoNo(int conteudo);
int 	 ArvProcura(laco *ptrArvore, int valorProcurado);
int  	 ArvTamanho(laco *ptrArvore);
int		 ArvMaiorGalho(laco *ptrArvore);
int		 solveGame(laco* ptrArvore);

int main(){
	laco *ptrArvore=NULL;
	int conteudo, result;
	int veto
	//Cria uma arvore binaria-------------------------------------------------------------	
	//  2
	//1   3
	int vetor[] = {1, 2, 3, 5, 7, 11, 13};
	for (int i=0;i<7;++i) {
		ptrArvore= ArvInsere(ptrArvore, vetor[i]);
	}

	//Tentativa de inserir automaticamente e de maneira organizada-------------------------------------------------------------
	// while(true)
	// {
	//printf("Insira os valores desejados:\n");
	// 	scanf("%d", &conteudo);
	// 	if(conteudo == 100)
	// 		break;
	// 	ptrArvore = ArvNovoNo(conteudo);
	// }

	// printf("Raiz da arvore: %d\tEsquerda: %d\n", ptrArvore->conteudo, ptrArvore->esquerda->conteudo);
	// printf("Insira o valor a ser procurado\n");
	// scanf("%d", &conteudo);
	// result	=  ArvProcura(ptrArvore, conteudo);
	// if(result)
	// 	printf("Encontrado o valor.\n\n");
	// else
	// 	printf("Sorry, not found.\n\n");
	ArvMostra(ptrArvore);
	printf("Ha %d no´s na arvore criada\n", ArvTamanho(ptrArvore));
	printf("O galho mais longo possui profundidade %d\n", ArvMaiorGalho(ptrArvore));
	printf("Checar se ha´ algum caminho cujo somatorio de a soma procurada. Qual o valor da soma?\n");
	scanf("%d", &conteudo);
	if(ArvContemSoma(ptrArvore, conteudo))
		printf("Contem um caminho!\n");
	else printf("Nao ha caminhos que resultem na soma procurada.\n");
	ArvLibera(ptrArvore);
	return 0;
}

//lib.
int ArvContemSoma(laco* ptrArvore, int somaProcurada){
	if(ptrArvore==NULL||somaProcurada==0)
		return (somaProcurada==0);
	//Senao chegou ao fim, procura nos filhos
	int parciais = somaProcurada - ptrArvore->conteudo;
	return(ArvContemSoma(ptrArvore->esquerda, parciais) ||
		ArvContemSoma(ptrArvore->direita, parciais));
}
//Insere de maneira ordenada
laco*	 ArvInsere(laco *ptrArvore, int conteudo){
	if(ptrArvore == NULL) //(Sub)Arvore vazia
		return ArvNovoNo(conteudo);
	if(conteudo<=ptrArvore->conteudo)//Menor valor no laco da esquerda.
		ptrArvore->esquerda = ArvInsere(ptrArvore->esquerda, conteudo);
	else 
		ptrArvore->direita = ArvInsere(ptrArvore->direita, conteudo);
	return ptrArvore;
}

void ArvLibera(laco *ptrArvore){
	if(ptrArvore==NULL)
		return;
	ArvLibera(ptrArvore->esquerda);
	ArvLibera(ptrArvore->direita);
	free(ptrArvore);
}
int		 ArvMaiorGalho(laco *ptrArvore){
	if(ptrArvore==NULL)
		return 0;
	int GalhoEsq = ArvMaiorGalho(ptrArvore->esquerda);
	int GalhoDir = ArvMaiorGalho(ptrArvore->direita);
	printf("Esquerda: %d\tDireita: %d\n", GalhoEsq, GalhoDir);
	if(GalhoEsq>GalhoDir) return GalhoEsq+1;
	else 				  return GalhoDir+1;
}

void ArvMostra(laco *ptrArvore){
	//Mostra a arvore no sentido Simetrico esquerda-Raiz-direita
	if(ptrArvore == NULL)
		return;
	ArvMostra(ptrArvore->esquerda);
	printf("%d\t%p\n", ptrArvore->conteudo, ptrArvore);
	ArvMostra(ptrArvore->direita);
}
laco* ArvNovoNo(int conteudo){
	laco* novo = (laco*) malloc(sizeof(laco));
	novo->conteudo = conteudo;
	novo->marcador = 0; //Set cell as not ran into yet
	novo->esquerda = novo->direita = NULL;
	return novo;
}
arvore* ArvOrganiza(arvore* ptrArvore){

	}
int ArvProcura(laco *ptrArvore, int valorProcurado){
	int aux;
	if(ptrArvore == NULL)
		return false;
	if(ptrArvore->conteudo == valorProcurado){
		printf("Endereco: %p\t%d\n", ptrArvore, ptrArvore->conteudo);
		return true;
	}
	aux = ArvProcura(ptrArvore->esquerda, valorProcurado);
	aux = ArvProcura(ptrArvore->direita, valorProcurado);
}
int  	 ArvTamanho(laco *ptrArvore){
	if(ptrArvore==NULL)
		return(0);
	return 1+ ArvTamanho(ptrArvore->esquerda) + ArvTamanho(ptrArvore->direita);
}
//Pseudocode 
// int		 solveGame(laco* ptrArvore){
// 	//pilha* ptrPilha = (pilha*)malloc(sizeof(pilha));
// 	while(ptrPilha!=NULL)
// 	{
// 		if(ptrArvore->esquerda == NULL && ptrArvore->direita == NULL)
// 		{
// 			if(IsGood(ptrArvore)) //IsGood function will change as the problem too.
// 				return true;
// 			return false;	//if it is not a good leaf, which means that it solves the problem.
// 		}
// 		if(HasUntriedChild(ptrArvore))
// 			putOnStack(ptrPilha, ptrChild);
// 		else
// 			popOffStack(ptrChild);
// 	}
// 	return false;	 //none of the leaves solved the game
// }