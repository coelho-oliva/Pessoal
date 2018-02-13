void soluciona(arvore* caminho, fila* filaPrimos, int** mapa, int tamanho)
{
	int i, j; posicao* posProx;
	arvore* path; path = ArvCria();
	i = caminho->posPrimo->linha; j = caminho->posPrimo->coluna;
	if (i!=0 && i!=(tamanho-1) && j!=0 && j!=(tamanho-1)){// Tenho todas as possibilidades
		if(mapa[i][j+1]==0) // Direita livre
		{
			if(caminho->filho==NULL || caminho->filho->posPrimo!=){ // Nao passou por aqui 
				direita();
			}
			//soluciona(); Tenho que pensar na parte que dá merda para saber como voltar
		}
		if(mapa[i][j-1]==0) // Esquerda livre
		{
			esquerda();
		}
		if(mapa[i-1][j]==0) // Em cima livre
		{
			emCima();
		}
		if(mapa[i+1][j]==0) // Em baixo livre
		{
			emBaixo();
		}
	}
	else // Casos de bordo
	{
		if(i==0 && j==0) // Canto superior esquerdo (1º elemento)
		{
			if(mapa[i][j+1]==0) // Direita livre
			{
				direita();
			}
			if(mapa[i+1][j]==0) // Baixo livre
			{	
				emBaixo();
			}
		}
		if(i==0 && j==(tamanho-1)) // Canto superior direito
		{
			if(mapa[i][j-1]==0) // Esquerda livre
			{
				esquerda();
			}
			if(mapa[i+1][j]==0) // Baixo livre 
			{
				emBaixo();
			}
		}
		if(i==(tamanho-1) && j=0) // Canto inferior esquerdo
		{
			if(mapa[i][j+1]==0) // Direita livre
			{
				direita();
			}
			if(mapa[i-1][j]) // Em cima livre
			{
				emCima();
			}
		}
		if(i==(tamanho-1) && j===(tamanho-1)) //Canto inferior direito (ultimo elemento)
		{
			if(mapa[i][j-1]==0) // Esquerda livre
			{
				esquerda();
			}
			if(mapa[i-1][j]) // Em cima livre
			{
				emCima();
			}
		}
	}
}

void direita();
void esquerda();
void emCima();
void emBaixo();