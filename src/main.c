#include "MyEvents/MyEvents.h"
#include "MyMovies/MyMovies.h"

/**
 * Nomes dos estados da a implementaÃ§Ã£o da maquina de estado 
*/
#define showMovie 1
#define buyMovie 2
#define notByMovie 3



/**
 * FunÃ§Ã£o que implementa a mÃ¡quina de estados do projeto "mÃ¡quina de venda de filmes"
 * 
*/
void initStateMachine(void)
{
	int state = showMovie; 				//estado inicial
	while(1)							//MÃ¡quina de estado em loop infinito!!!!	
	{
		switch(state)
		{
			case showMovie:
			/*actividades*/
			/*condiÃ§Ãµe/eventos para saltar de estado*/
			break;


			case buyMovie:
				/*actividades*/
				/*condiÃ§Ãµe/eventos para saltar de estado*/
			break;


			case notByMovie:
			 	/*actividades*/
				/*condiÃ§Ãµe/eventos para saltar de estado*/
			break;


			default:
				/*nÃ£o existem instruÃ§Ãµes de defaultiu*/

		}//fim do switch(state)
	
		testLeds(); //FunÃ§Ã£o para apagar sÃ³ estÃ¡ aqui para teste de hardware
		k_msleep(1000);
	
	
	
	}//fim do while(1)
}//fim do void initStateMachine(void)


/* 
 * The main function
 */
void main(void)
{
	int ret;
	/*Inicializar os devices*/
	initDevicesIO();

	//ret=credito(&creditoAcomulado, 1,0);
	//printk("o credito acolmulado e: %d", ret);
	alocListMovies();
	creatListMovies();

	ret=listaFilmes[1].price;
	printk("preço do filme %d",ret);

	initStateMachine();
	

}