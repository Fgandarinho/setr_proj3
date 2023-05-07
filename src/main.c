/**
 * Nome: Fernando Gandarinho e Tomas Silva
*/
/**
 * Módulos usados pelo main
*/
#include "MyEvents/MyEvents.h"
#include <zephyr/sys/printk.h>		/*para printk*/

/**
 * Nomes dos estados da a implementação da máquina de estado 
*/
#define showMovie 1
#define buyMovie 2
#define notByMovie 3

/**função da máquina de estados
*Atenção: esta função após inicializar entre em loop infinito
*/
void initStateMachine(void);



 /* 
 The main function
 */
void main(void)
{
	printk("\n############ ->>>> Maquina venda de filmes a inicializar..... \n\n");
	
	/*inicializa os devicesdrivers e hardware*/
	init_config_Devices();
	
	/* inicialia a Máquina de estados*/
	initStateMachine();


}

/**
 * Função que implementa a máquina de estados do projeto "máquina de venda de filmes"
 * 
*/
void initStateMachine(void)
{
	int state = showMovie; 				//estado inicial
	while(1)							//Máquina de estado em loop infinito!!!!	
	{
		switch(state)
		{
			case showMovie:
			/*actividades*/
			/*condiçõe/eventos para saltar de estado*/
			break;


			case buyMovie:
				/*actividades*/
				/*condiçõe/eventos para saltar de estado*/
			break;


			case notByMovie:
			 	/*actividades*/
				/*condiçõe/eventos para saltar de estado*/
			break;


			default:
				/*não existem instruções de defaultiu*/

		}//fim do switch(state)
	
		test_Leds(); //Função para apagar só está aqui para teste de hardware
	
	
	
	}//fim do while(1)
}//fim do main()

