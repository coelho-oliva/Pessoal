/*Trabalho dos Jogos.
      file: jogos.c
    author: Caio Eduardo Coelho de Oliveira
 matricula: 16/0003679	
disciplina: APC

3 joguinhos que podem ser selecionados digitando-se suas respectivas opções. 
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
void senha(){
	int entrada, valor, tentativas = 0;
	srand((unsigned)time(NULL));
	valor = rand()%100001;
	printf("Regras: A senha é um valor de 0 a 100.000(cem mil)\nDigitar um valor negativo termina o jogo e o(a) jogador(a) recebe uma\npenalizacao de 99 tentativas\n");
	printf("Digite seu palpite.\n");
	while(1)
	{
		if(scanf(" %d", &entrada) == 1)
		{
			tentativas ++;
			if(entrada < 0){
				printf("Tá aí a resposta, bicho véi sem graça... A senha era: %d\nTentativas: %d\n", valor, tentativas + 99);
				return;
			}
			else if(entrada != valor){
				if (entrada > valor){
					printf("É menor!\nTente novamente!\n");
				}
				if (entrada < valor){
					printf("Aposte mais alto...\n");
				}
			}
			else if(entrada == valor){
				printf("THE END.\n");
				if (tentativas > 25){
					printf("Aonde tu tava indo, hein, Comando Estelar? %d tentativas, sério mesmo?\n\n", tentativas);
				}
				else if(tentativas > 15 && tentativas < 25){
					printf("Mas também... Nem conta, fala sério... %d tentativas, po.\n\n", tentativas);
				}
				else if(tentativas > 10 && tentativas <= 15){
					printf("Not bad, boundy hunter, not bad at all... %d palpites.\n\n", tentativas);
				}
				else {
					printf("Parabéns! Até que enfim alguém esperto apareceu aqui!\n Tentativas: %d\n\n", tentativas);
				}
				printf("Volte quando puder! ^^\n");
				return;
			}
		}
		else{
			printf("Entrada inválida. Por favor, escreva o número em algarismos.\n");
			getchar();
			continue;
		}
	}
}	
void palitos(){
	int qtd = 10, num, joker, jogador = 1;

	printf("Jogo dos Palitinhos\nProcessando...\n");
	sleep(1);
	printf("Pronto!\n");
	sleep(1);
	printf("Regras: Cada jogador só pode retirar 1 ou 2 palitos por vez.\nDigitar 0 termina o jogo.\n");	
	for(joker = 10; joker > 0; joker--){
		printf("|");
	}
	printf("\n");
	while(qtd > 0)
	{
		if(jogador == 1)
		{
			printf("Jogador 1, qual a sua jogada?\n");
			if(scanf(" %d", &num) == 1)
			{
				if(num == 0){
					printf("OK. Volte sempre! :)\n");
					return;
				}
				if(num > 2 || num > qtd || num < 0){
					printf("You can't do that.\n");
					continue;
				}
				else {
					qtd -= num;
					for(joker = qtd; joker > 0; joker--){
						printf("|");
					}
					jogador = 2;
				}
				printf("\n");
			}
			else
			{
				printf("Entrada inválida. :/\n");
				sleep(1);
				printf("\e[H\e[2J");
				for(joker = qtd; joker > 0; joker--){
						printf("|");
				}
				printf("\n");
				getchar();
				continue;
			}		
		}
		else if(jogador == 2)
		{
			printf("Jogador 2, qual a sua jogada?\n");
			if(scanf(" %d", &num) == 1)
			{	
				if(num == 0){
					printf("OK. Volte sempre! :)\n");
					return;
				}
				if(num > 2 || num > qtd || num < 0){
					printf("You can't do that.\n");
					continue;
				}
				else 
				{
					qtd -= num;
					for(joker = qtd; joker > 0; joker--){
						printf("|");
					}
					jogador = 1;
				}
				printf("\n");
			}
			else
			{
				printf("Entrada inválida. :/\n");
				sleep(1);
				printf("\e[H\e[2J");
				for(joker = qtd; joker > 0; joker--){
						printf("|");
				}
				printf("\n");
				getchar();
				continue;
			}			
		}
	}
	if(qtd == 0){
		if (jogador == 1) printf("Jogador 2 ganhou! Parabéns!\n");
		else if (jogador == 2)	printf("Jogador 1 ganhou! Parabéns!\n");
	}
	return;
}
/*Observação: O jogo possui um bug notório: 
	01. Quando dois jogadores perdem com o mesmo personagem, o jogo dá empate. */
void p_p_t_s_l(){
	char jog[3];
	int i;

	int teste(char j1, char j2, char j3, char um, char dois, char tres){
		int i;
		char jog[3];
		jog[0] = j1;
		jog[1] = j2;
		jog[2] = j3;
		for(i = 0; i < 3; ++i)
		{
				/*Estão fora das condições do bloco atual, então sai*/
				if(jog[i] != um && jog[i] != dois && jog[i] != tres){
					return 0;
				}
		}		
		/*Estão nas condições*/
		if(jog[0] != jog[1] && jog[0] != jog[2] && jog[1] != jog[2]){
			printf("Processando\n");
			printf(".\n");
			sleep(1);
			printf(".\n");
			sleep(1);
			printf(".\n");
			sleep(2);
			jog[0] == um ? (printf("Jogador 1 ganhou!\nIuuu, perderam, bestas!\n")) : (jog[1] == um ? (printf("Jogador 2 ganhou!\nIuuu, perderam, bestas!\n")): (printf("Jogador 3 ganhou!\nIuuu, perderam, bestas!\n")));
			return 1;				
		}
		return 0;
	}
	

	while(1)
	{
		for(i = 1; i <= 3; ++i){
			printf("Jogador %d, digite como quer per- Ops, qual a sua jogada?\n", i);
			printf("p)Pedra\nP)Papel\nT)Tesoura\nS)Spock\nL)Lagarto\n\n");
			scanf(" %c", &jog[i]);
			printf("\e[H\e[2J");
			if(jog[i] != 'T' && jog[i] != 'S' && jog[i] != 'L' && jog[i] != 'p' && jog[i] != 'P'){
				i--;
				printf("Selecione uma das alternativas abaixo.\n");
				continue;
			}
		}
		/*Condições para ganhar:*/
		if(teste(jog[0], jog[1], jog[2], 'p', 'T', 'L')){
			printf("Jogada: Pedra-Tesoura-Lagarto\n");
			return;
		}
		else if(teste(jog[0], jog[1], jog[2], 'P', 'S', 'p')){
			printf("Jogada Papel-Spock-Pedra\n");
			return;
		}
		else if(teste(jog[0], jog[1], jog[2], 'T', 'L', 'P')){
			printf("Jogada Tesoura-Lagarto-Papel\n");
			return;
		}
		else if(teste(jog[0], jog[1], jog[2], 'S', 'T', 'p')){
			printf("Jogada Spock-Tesoura-Pedra\n");
			return;
		}
		else if(teste(jog[0], jog[1], jog[2], 'L', 'S', 'P')){
			printf("Jogada Lagarto-Spock-Papel\n");
			return;
		}
		else{
			printf("Empate!\nGeente, meu óculos,\nNinguém sai.\n\n");
		}			



	}	
	return;
}

int main()
{
	int code;

	while(1){
		printf("1) Senha.\n2) Palitinhos.\n3) Pedra-Papel-Tesoura-Lagarto-Spock.\n4) Sair.\n");
		printf("Digite a opção que deseja:\n");
		scanf("%d", &code);

		if (code == 1){
			printf("\n");
			printf("Jogo da senha. Iniciando...\n");
			senha();
		}
		else if(code == 2){
			printf("\n");
			palitos();
		}
		else if(code == 3){
			printf("\n");
			p_p_t_s_l();
		}
		else if(code == 4) break;
		else{
			printf("Processando...\n");
			sleep(2);
			printf("Você está vendo alguma opção com esse número? Pois é; não tem, né...\n");
		} 

	}

	return 0;
}