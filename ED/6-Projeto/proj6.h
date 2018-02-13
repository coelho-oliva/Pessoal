#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define qtdDocs 12
#define MaiorPalavra 50
#define TamanhoTabela 113
typedef char PALAVRA[MaiorPalavra];

typedef struct celula
{
	PALAVRA palavra;
	int documentos[qtdDocs];
	struct celula* prox;
}lista;

typedef struct HASH
{
	int key;
	lista *celula;
}Hash;

lista*		criaLista();
//Hash*		criaTabelaHashing();
int 		estaNaLista(lista *ptrLista, PALAVRA palavra);
int 		hashFunction(PALAVRA palavra, unsigned int *peso);
lista*		incluiComecoLista(lista* ptrLista, int documentos, PALAVRA palavra);
void		insereNaHT(lista* celula, Hash *Tabela, unsigned int *peso);
void 		insereVetorDocumentos(int* documentos, int doc);
void 		salvaIndInvert(lista* listaPalavras);
void 		salvaHashDocs(Hash* Tabela);


lista* criaLista()
{
	lista* ptrLista;
    ptrLista = (lista*) malloc(sizeof(lista));
    strcpy(ptrLista->palavra, "zzzzz\0");
    int i;
    for(i=0;i<qtdDocs;i++)
    	ptrLista->documentos[i] = 0;
	ptrLista->prox = NULL;
	return ptrLista;
}
/*Hash* criaTabelaHashing()
{

}*/
void incluiNaLista(lista* ptrLista, int doc, PALAVRA palavra)
{
	while(ptrLista->prox!=NULL && (strcmp(ptrLista->palavra, palavra) != 0))
	{
		ptrLista = ptrLista->prox;
	}
	lista* novaCel = ptrLista;
	if(ptrLista->prox==NULL)
	{
		novaCel = criaLista();
		strcpy(novaCel->palavra, palavra);
		ptrLista->prox = novaCel;
	}
	insereVetorDocumentos(novaCel->documentos, doc);
}
void insereVetorDocumentos(int* documentos, int doc)
{
	int i = 0;
	while(i<qtdDocs)
	{
		if(documentos[i]==doc)
			return;
		if(documentos[i] == 0){
			documentos[i] = doc;	
			return;
		}	i++;
	}
}
void criavetPesos(unsigned  int* vetPesos)
{	
	int i, j, k;
	for(i=0, j = k = 1;i<MaiorPalavra;i++){
		(k+=i+5); j += 5;
		vetPesos[i] = i*i*i + k*i*i - j*i + 3;
	}
}
int hashFunction(PALAVRA palavra, unsigned int *peso)
{
	int key, i;
	key = i = 0;
	while(palavra[i]!='\0')
	{
		key += palavra[i]*peso[i];
		i++;
	}
	return key;
}
void insereNaHT(lista* Lista, Hash* Tabela, unsigned int *peso)
{
	int indice, key, j;
	key = hashFunction(Lista->palavra, peso);
	indice = key%TamanhoTabela;
	if(strcmp((Tabela[indice].celula->palavra), "zzzzz\0") == 0)
	{
		Tabela[indice].key = key;
		strcpy(Tabela[indice].celula->palavra, Lista->palavra);
		for(j=0; j<qtdDocs; j++)
			Tabela[indice].celula->documentos[j] = Lista->documentos[j];
	}
	else
	{
		lista* novaCel = malloc(sizeof(lista));
		novaCel->prox = Tabela[indice].celula;
		Tabela[indice].celula = novaCel;
		strcpy(novaCel->palavra, Lista->palavra);
		for(j=0; j<qtdDocs; j++)
			novaCel->documentos[j] = Lista->documentos[j];
	}
}
void salvaIndInvert(lista* listaPalavras)
{
	listaPalavras = listaPalavras->prox;	//Ignora a cabeça da lista
	FILE* arquivo = fopen("IndInvert.txt", "w+");
	int i;
	while(listaPalavras!=NULL)
	{
		fprintf(arquivo, "%s ", listaPalavras->palavra);
		for(i=0; i<qtdDocs; i++)
		{	
			if(listaPalavras->documentos[i] == 0)	break;
			fprintf(arquivo, "%d ", listaPalavras->documentos[i]);
		}
		fprintf(arquivo, "\n");
		listaPalavras = listaPalavras->prox;
	}
	fclose(arquivo);
}
void salvaHashDocs(Hash* Tabela)
{
	FILE* arquivo = fopen("HashDocs.txt", "w+");
	int i, j;
	lista* aux;
	for(i=0; i<TamanhoTabela; i++)
	{
		aux = Tabela[i].celula;
		while(aux != NULL){
			fprintf(arquivo, "Palavra: %s Chave: %d Docs: ", aux->palavra, Tabela[i].key);
			for(j=0; j<TamanhoTabela && aux->documentos[j]!=0; j++)
				fprintf(arquivo, "%d ", aux->documentos[j]);
			fprintf(arquivo, "\n");
			aux = aux->prox;
		}
	}
	fclose(arquivo);
}