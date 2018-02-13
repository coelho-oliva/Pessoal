//teste
#include <stdio.h>

int main(){
	int i=0;
	while(1)
	{
		printf("Inicio.\n");
		while(i<5)
		{
			printf("Valor de i: %d\n", i);
			i++;
			if(i==3)	break;
		}
		printf("Inicio: valor de i: %d\n", i);
		i++;
		if(i>7)
			break;
	}


	return 0;
}