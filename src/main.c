/** 
* \file main.c
*
* \brief Este módulo é a main do nosso programa da máquina de filmes implementada com máquina de estados.
*
* \author Fernando Gandarinho e Tomás Silva
* \date 16/05/2023
* \bug There are no bugs
*/

#include "MyEvents/MyEvents.h"
#include "MyMovies/MyMovies.h"

/* Use a "big" sleep time to reduce CPU load (button detection int activated, not polled) */
/**
 * \brief Tempo de sleep da máquina de estados para reduzir a carga do CPU
*/

#define SLEEP_TIME_MS   60*1000 

/**
 * \brief Tempo de refresh da máquina de estados
*/
#define REFRESH_TIME_SM_MS 500

/* Nomes dos estados da a implementaÃ§Ã£o da maquina de estado */
/** \brief Estado 1 da maquina de estados
 * Este estado representa o estado em que o utilizador escolhe o filme e adiciona o credito
 */
#define showMovie 1

/** \brief Estado 2 da maquina de estados
 * Este estado representa o estado em que o utilizador compra o filme
 */
#define buyMovie 2

/** \brief Estado 3 da maquina de estados
 * Este estado representa o estado em que o utilizador não compra o filme
 */
 */
#define notByMovie 3


/** \brief Definiçao da estrutura de dados para os filmes.
 *    Esta estrutura contém os vários filmes existentes na maquina de filmes.
 * 
 * 	\author Fernando Gandarinho e Tomás Silva
 * 	
 * 	\date 16/05/2023
 * 
 */
struct filme ret_filme;						/*cria uma variavel do tipo filme para retorno das funções das funções de MyMovies*/


/** \brief Definiçao da estrutura dos botões
 *    Esta estrutura contém os vários botões a ser utilizado no projeto
 *
 * 	\date 16/05/2023
 * 
 */

struct botao ret_bota;						/*cria uma variavel do tipo botao para retrono das  funções de MyEventes*/


/** \brief Variavel global para o credito acumulado
 *
 * 	\date 16/05/2023
 * 
 */
static int creditoAcomulado = 0;			/*variavel que contem o credito acomulado*/		


/** \brief Variavel global para o indice do filme atual
 *
 * 	\date 16/05/2023
 * 
 */
static int currentMovie = 1;				/*variavel que sinaliza o indice do fime selecionado*/

static bool state_showMovie= true;			/* flags usadas na maquina de estado para que no ciclo infinito o terminal não esteja sempre a printK();*/
static bool state_buyMovie= false;
static bool state_notByMovie= false;


/**
 * \brief Função que implementa a máquina de estados do projeto "máquina de venda de filmes"
 * 
 * \author Fernando Gandarinho e Tomás Silva
 * \date 16/05/2023
 * \bug There are no bugs
 * 
*/
void initStateMachine(void)
{
	int state = showMovie; 					//estado inicial
	int rtrn=0;								//variavel usada para o retorno das funções	
	
	while(1)								//MÃ¡quina de estado em loop infinito!!!!	
	{
		ret_bota = readBot();				//lê e actualiza o estado do botões
		switch(state)
		{	/*######################## ESTADO 1 ######################*/
			case showMovie:	
					/* ########################################*/
					/* ###### ACTIVIDADES DESTE ESTADO ####### */
				if(state_showMovie==true)
				{
					ret_filme = showFilme(currentMovie); 		//mostra o filme selecionado
					printk("%s, com sessão às : %s, e custa %d EUROS\n",ret_filme.nomeFilme, ret_filme.sessionTime, ret_filme.price);
					
					rtrn=credito(&creditoAcomulado,0,0); 		//Mostra o crédito atual
					printk("O credito acolmulado e: %d \n", rtrn);

					state_showMovie=false;						//flags para so realizar este código 1x!!!!		
					state_buyMovie=true;
					state_notByMovie=true;
				}
							/*###################################################################*/	
							/*########## CONDIÇOES/EVENTOS para SALTAR de estado ################*/
				if(ret_bota._up==true)									// verificar o botão_up se foi pressionado
				{
					state=showMovie;									//next_state -> showMovie
					if(currentMovie < NUM_MAX_FILMES-1)				/*-1 pois o array conta com o valor 0-4 -> NUM_MAX_FILMES=5*/	
					{
						currentMovie++;									/*incrementa para o proximo filme*/
					}else
						{
							currentMovie=0;								/*se o indice dos filmes atingir o máximo a lista deve reeniciar*/					
						}
					state_showMovie=true;								//permite escrever novamente as infoirmaçoões do filme atual no state_showMovie
					ret_bota._up=false;								    //volta a colocar a sinalização do botão UP a false	
				}

				if(ret_bota._dw==true)									// verificar o botão_up se foi pressionado
				{
					state=showMovie;									//next_state -> showMovie
					if(currentMovie >0)									/*-1 pois o array conta com o valor 0-4 -> NUM_MAX_FILMES=5*/	
					{
						currentMovie--;									/*incrementa para o proximo filme*/
					}else{
							currentMovie=NUM_MAX_FILMES-1;				/*se o indice dos filmes atingir o máximo a lista deve reeniciar*/					
						}
					state_showMovie=true;								//permite escrever novamente as infoirmaçoões do filme atual no state_showMovie
					ret_bota._dw=false;					    			//volta a colocar a sinalização do botão UP a false	
				}

				if(ret_bota._ret==true && creditoAcomulado>0)			//Se botão return é pressionado e existe crédito	
				{
					int ret;
					state=showMovie;												//next_state -> showMovie
					ret= credito(&creditoAcomulado,0,0); 							//Lê o credito presente
					printk(" ---------------------> credito a ser devolvido: %d\n",ret);	//apresenta ao utilizador o credito que vai devolver
					ret= credito(&creditoAcomulado,0,3);							//remove todo o credito
					state_showMovie=true;											//permite escrever novamente as infoirmaçoões do filme atual no state_showMovie
					ret_bota._ret=false;					    					//volta a colocar a sinalização do botão UP a false
				}

				if(ret_bota._1E==true || ret_bota._2E==true || ret_bota._5E==true || ret_bota._10E==true)	//Inserido dinheiro			
				{
					coinInsert();	
					state_showMovie=true;											//permite escrever novamente as infoirmaçoões do filme atual no state_showMovie
					
				}//fim de if(ret_bota._1E==true || ret_bota._2E==true || ret_bota._10E==true || ret_bota._10E==true)

				if(ret_bota._sel == true && creditoAcomulado>=ret_filme.price)		//compra Filme
				{
					state=buyMovie;													//sALTA PARA O ESTADO 2 -> BUYmOVIE SE existir credito sufucinete
					state_buyMovie=true;											//permite que as informações apareçam no ecrã quando iniciar o ESTADO 2					
					ret_bota._sel=false;											//Coloca a flag do Botão novamente a false
				}

				if(ret_bota._sel == true && creditoAcomulado<ret_filme.price)
				{
					state=notByMovie;												//sALTA PARA O ESTADO 3 -> notByMovie Se não existir credito suficiente
					state_notByMovie=true;											//permite que as informações seja escrita no ecrã quando iniciar o Estado 3
					ret_bota._sel=false;											//reset a flag do botão Select (false)

				}
			break;

					/*######################## ESTADO 2 ######################*/
			case buyMovie:									
							/* ########################################*/
							/* ###### ACTIVIDADES DESTE ESTADO ####### */
					if(state_buyMovie==true)
					{
						ret_filme = showFilme(currentMovie); 						//mostra o filme selecionado
						printk("O fime: %s foi Comprado\n",ret_filme.nomeFilme);
					
						rtrn=credito(&creditoAcomulado,0,0); 						//Mostra o crédito atual
						rtrn=credito(&creditoAcomulado,ret_filme.price,2);			//Desconta o preço do filme ao credito e devolve		
						printk("O credito acolmulado e: %d \n", rtrn);				//mostra o credito acomulado
					
						state_showMovie=false;										//Até sair deste estado para não estar sempre a repetir or printK
						state_buyMovie=false;
						state_notByMovie=true;
					}
					
					
					/*###################################################################*/	
				    /*########## CONDIÇOES/EVENTOS para SALTAR de estado ################*/
					if(ret_bota._ret == true)
					{
						state=showMovie;											/*Salta para o Estado n1 -> showMovei*/
						state_showMovie=true;										/*permite que se escreva novamente as informações do filme atual */
						ret_bota._ret=false;										/*manda a flag de sinalização do estado a baixo*/	
					}

					if(ret_bota._1E==true || ret_bota._2E==true || ret_bota._5E==true || ret_bota._10E==true)	//Inserido dinheiro			
					{
						state=showMovie;											//salta para o primeiro estado ->showMovie
						
						coinInsert();	

						state_showMovie=true;										//permite escrever novamente as infoirmaçoões do filme atual e do credito no state_showMovie
						
					}//fim de if(ret_bota._1E==true || ret_bota._2E==true || ret_bota._10E==true || ret_bota._10E==true)

			break;

						/*######################## ESTADO 3 ######################*/
			case notByMovie:								
							/* ########################################*/
							/* ###### ACTIVIDADES DESTE ESTADO ####### */
					if(state_notByMovie==true)
					{
						ret_filme = showFilme(currentMovie); 						//mostra o filme selecionado
						printk("O fime: %s NÂO FOI Comprado\n",ret_filme.nomeFilme);
					
						rtrn=credito(&creditoAcomulado,0,0); 						//Mostra o crédito atual
						printk("O credito acolmulado e: %d \n", rtrn);				//mostra o credito acomulado
					
					
					state_showMovie=true;
					state_buyMovie=true;
					state_notByMovie=false;
					}

					/*###################################################################*/	
				    /*########## CONDIÇOES/EVENTOS para SALTAR de estado ################*/
					if(ret_bota._ret == true)
					{
						state=showMovie;											/*Salta para o Estado n1 -> showMovei*/
						state_showMovie=true;										/*permite que se escreva novamente as informações do filme atual */
						ret_bota._ret=false;										/*manda a flag de sinalização do estado a baixo*/	
					}

					if(ret_bota._1E==true || ret_bota._2E==true || ret_bota._5E==true || ret_bota._10E==true)	//Inserido dinheiro			
					{
						state=showMovie;											//salta para o primeiro estado ->showMovie

						coinInsert();	

						state_showMovie=true;										//permite escrever novamente as infoirmaçoões do filme atual e do credito no state_showMovie
						
					}//fim de if(ret_bota._1E==true || ret_bota._2E==true || ret_bota._10E==true || ret_bota._10E==true)



					break;


			default:
				/*nÃ£o existem instruCOES de defaultE*/

		}//fim do switch(state)
	
		writeBot(ret_bota);															/*atualiza todas as flag dos botoes*/	
		k_msleep(REFRESH_TIME_SM_MS);																/*Tempo de refresh da Máquina de estados*/

	}//fim do while(1)
}//fim do void initStateMachine(void)



/*fução que vai tratar os eventos da inserção das moedas*/
void coinInsert(void)
{
	int rt=0;										//variavel local para retorno das funções	
	if(ret_bota._1E == true)						//actualiza o credito mediante o dinheiro colocado
	{
		rt=credito(&creditoAcomulado,1,1);	//adiciona 1euro
		printk("$$ O seu credito atual e de: %d EURO \n", rt);
		ret_bota._1E=false;	

	}else{ if(ret_bota._2E == true)
			{
				rt=credito(&creditoAcomulado,2,1);	//adiciona 2euro
				printk("$$ O seu credito atual e de: %d EURO \n", rt);
				ret_bota._2E=false;	

			}else{ if(ret_bota._5E == true)
					{
						rt=credito(&creditoAcomulado,5,1);	//adiciona 5euro
						printk("$$ O seu credito atual e de: %d EURO \n", rt);
						ret_bota._5E=false;	

					}else{if(ret_bota._10E == true)
							{ 
							rt=credito(&creditoAcomulado,10,1);	//adiciona 10euro
							printk("$$ O seu credito atual e de: %d EURO \n", rt);
							ret_bota._10E=false;	
							}
						}
				} 
		}
							
}

/* 
 * The main function
 */
 
 /**
 * \brief Função principal do programa
 * 
 * \author Fernando Gandarinho e Tomás Silva
 * \date 16/05/2023
 * \bug There are no bugs
 *  
 */
void main(void)
{
			
	/*Inicializar os devices em MyEventes.c*/
	initDevicesIO();

	/*botões funciona com interrupções -> devolve apenas uma mensagem a dizer que foi clicado*/

	/*funções que gere lista de filmes*/
	alocListMovies();

	/*escreve na lista os filmes presentes no guião do trabalho*/
	creatListMovies();

	/*mensagem de apresentação */
	printk("\n\n###################################\n");
	printk("# Máquinas de Estados inicializada #\n");
	printk("###################################\n\n");

	/*inicializa a máquina de estados esta vai entrar em loop infinito*/
	initStateMachine();
	

}
