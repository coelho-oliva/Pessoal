/*
	   @authors:	Caio Eduardo Coelho de Oliveira e Raul Silva Menezes
	@matriculas:	16/0003679	e 	16/0017327
		 @flags:	gcc -Wall
*/
#include "proj7.h"
//Pensar em usar um indice para os nós
//Ideia: Nao ficar perguntando se ainda tem amigos para acrescentar. Apenas esperar que a pessoa digite q ou Q. E ai´, sim, perguntar
//se ainda faltam pessoas para acrescentar `a rede

int main ()
{
	NODE *node;
	node = NULL;
	interacaoUsuario(node);
	liberaGrafo(node);
	return 0;
}