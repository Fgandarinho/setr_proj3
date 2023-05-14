#include "MyEvents/MyEvents.h"
#include "MyMovies/MyMovies.h"

/* Use a "big" sleep time to reduce CPU load (button detection int activated, not polled) */
#define SLEEP_TIME_MS   60*1000 

/**
 * Nomes dos estados da a implementaÃ§Ã£o da maquina de estado 
*/
#define showMovie 1
#define buyMovie 2
#define notByMovie 3



struct filme ret_filme;								/*cria uma variavel do tipo filme para retorno das funções das funções de MyMovies*/
struct botao ret_bota;								/*cria uma variavel do tipo botao para retrono das  funções de MyEventes*/

static int creditoAcomulado = 0;
static int currentMovie = 1;

static bool state_showMovie= true;			/* flags usadas na maquina de estado para que no ciclo infinito o terminal não esteja sempre a printK();*/
static bool state_buyMovie= false;
static bool state_notByMovie= false;


/**
 * FunÃ§Ã£o que implementa a mÃ¡quina de estados do projeto "mÃ¡quina de venda de filmes"
 * 
*/
void initStateMachine(void)
{
	int state = showMovie; 				//estado inicial
	int rtrn=0;							//variavel usada para o retorno das funções	
	
	while(1)							//MÃ¡quina de estado em loop infinito!!!!	
	{
		ret_bota = readBot();	//lê e actualiza o estado do botões
		switch(state)
		{	/*######################## ESTADO 1 ######################*/
			case showMovie:	
					/* ########################################*/
					/* ###### ACTIVIDADES DESTE ESTADO ####### */
				if(state_showMovie==true)
				{
					ret_filme = showFilme(currentMovie); //mostra o filme selecionado
					printk("%s, com sessão às : %s, e custa %d EUROS\n",ret_filme.nomeFilme, ret_filme.sessionTime, ret_filme.price);
					
					rtrn=credito(&creditoAcomulado,0,0); //Mostra o crédito atual
					printk("O credito acolmulado e: %d \n", rtrn);

					state_showMovie=false;					//flags para so realizar este código 1x!!!!		
					state_buyMovie=true;
					state_notByMovie=true;
				}
							/*###################################################################*/	
							/*########## CONDIÇOES/EVENTOS para SALTAR de estado ################*/
				if(ret_bota._up==true)									// verificar o botão_up se foi pressionado
				{
					state=showMovie;						//next_state -> showMovie
					if(currentMovie <= (NUM_MAX_FILMES-1))	/*-1 pois o array conta com o valor 0-4 -> NUM_MAX_FILMES=5*/	
					{
						currentMovie++;						/*incrementa para o proximo filme*/
					}else
						{
							currentMovie=0;					/*se o indice dos filmes atingir o máximo a lista deve reeniciar*/					
						}
					state_showMovie=true;					//permite escrever novamente as infoirmaçoões do filme atual no state_showMovie
					ret_bota._up=false;					    //volta a colocar a sinalização do botão UP a false	
				}

				if(ret_bota._dw==true)									// verificar o botão_up se foi pressionado
				{
					state=showMovie;						//next_state -> showMovie
					if(currentMovie >0)	/*-1 pois o array conta com o valor 0-4 -> NUM_MAX_FILMES=5*/	
					{
						currentMovie--;						/*incrementa para o proximo filme*/
					}else{
							currentMovie=NUM_MAX_FILMES-1;					/*se o indice dos filmes atingir o máximo a lista deve reeniciar*/					
						}
					state_showMovie=true;					//permite escrever novamente as infoirmaçoões do filme atual no state_showMovie
					ret_bota._dw=false;					    //volta a colocar a sinalização do botão UP a false	
				}

				if(ret_bota._ret==true && creditoAcomulado>0)
				{
					int ret;
					state=showMovie;						//next_state -> showMovie
					ret= credito(&creditoAcomulado,0,0); 	//Lê o credito presente
					printk(" ---------------------> credito devolvido: %d\n",ret);
					ret= credito(&creditoAcomulado,0,3);	//remove todo o credito
					state_showMovie=true;					//permite escrever novamente as infoirmaçoões do filme atual no state_showMovie
					ret_bota._ret=false;					    //volta a colocar a sinalização do botão UP a false
				}

				if(ret_bota._1E==true || ret_bota._2E==true || ret_bota._5E==true || ret_bota._10E==true)	//Inserido dinheiro			
				{
					if(ret_bota._1E == true)
					{
						rtrn=credito(&creditoAcomulado,1,1);	//adiciona 1euro
						printk("$$ O seu credito atual e de: %d EURO \n", rtrn);
						ret_bota._1E=false;	

					}else{ if(ret_bota._2E == true)
							{
								rtrn=credito(&creditoAcomulado,2,1);	//adiciona 2euro
								printk("$$ O seu credito atual e de: %d EURO \n", rtrn);
								ret_bota._2E=false;	

							}else{ if(ret_bota._5E == true)
									{
										rtrn=credito(&creditoAcomulado,5,1);	//adiciona 5euro
										printk("$$ O seu credito atual e de: %d EURO \n", rtrn);
										ret_bota._5E=false;	

									}else{if(ret_bota._10E == true)
											{ 
											rtrn=credito(&creditoAcomulado,10,1);	//adiciona 10euro
											printk("$$ O seu credito atual e de: %d EURO \n", rtrn);
											ret_bota._10E=false;	
											}
										}
								} 
						}	

					state_showMovie=true;					//permite escrever novamente as infoirmaçoões do filme atual no state_showMovie
					
				}//fim de if(ret_bota._1E==true || ret_bota._2E==true || ret_bota._10E==true || ret_bota._10E==true)

				if(ret_bota._sel == true && creditoAcomulado>=ret_filme.price)					//compra Filme
				{
					state=buyMovie;							//sALTA PARA O ESTADO 2 -> BUYmOVIE SE existir credito sufucinete

					state_buyMovie=true;					//permite que as informações apareçam no ecrã quando iniciar o ESTADO 2					

					ret_bota._sel=false;					//Coloca a flag do Botão novamente a false
				}

				if(ret_bota._sel == true && creditoAcomulado<ret_filme.price)
				{
					state=notByMovie;							//sALTA PARA O ESTADO 3 -> notByMovie Se não existir credito suficiente
					
					state_notByMovie=true;						//permite que as informações seja escrita no ecrã quando iniciar o Estado 3

					ret_bota._sel=false;						//reset a flag do botão Select (false)

				}
			break;

					/*######################## ESTADO 2 ######################*/
			case buyMovie:									
							/* ########################################*/
							/* ###### ACTIVIDADES DESTE ESTADO ####### */
					if(state_buyMovie==true)
					{
						ret_filme = showFilme(currentMovie); 			//mostra o filme selecionado
						printk("O fime: %s foi Comprado\n",ret_filme.nomeFilme);
					
						rtrn=credito(&creditoAcomulado,0,0); 			//Mostra o crédito atual
						rtrn=credito(&creditoAcomulado,ret_filme.price,2);			//Desconta o preço do filme ao credito e devolve		
						printk("O credito acolmulado e: %d \n", rtrn);	//mostra o credito acomulado
					
						state_showMovie=false;							//Até sair deste estado não está sempre a repetir or printK
						state_buyMovie=false;
						state_notByMovie=true;
					}
					
					
					/*###################################################################*/	
				    /*########## CONDIÇOES/EVENTOS para SALTAR de estado ################*/
					if(ret_bota._ret == true)
					{
						state=showMovie;		/*Salta para o Estado n1 -> showMovei*/
						state_showMovie=true;	/*permite que se escreva novamente as informações do filme atual */
						ret_bota._ret=false;	/*manda a flag de sinalização do estado a baixo*/	
					}

					if(ret_bota._1E==true || ret_bota._2E==true || ret_bota._5E==true || ret_bota._10E==true)	//Inserido dinheiro			
					{
						state=showMovie;								//salta para o primeiro estado ->showMovie
						if(ret_bota._1E == true)						//actualiza o credito mediante o dinheiro colocado
						{
							rtrn=credito(&creditoAcomulado,1,1);	//adiciona 1euro
							printk("$$ O seu credito atual e de: %d EURO \n", rtrn);
							ret_bota._1E=false;	

						}else{ if(ret_bota._2E == true)
								{
									rtrn=credito(&creditoAcomulado,2,1);	//adiciona 2euro
									printk("$$ O seu credito atual e de: %d EURO \n", rtrn);
									ret_bota._2E=false;	

								}else{ if(ret_bota._5E == true)
										{
											rtrn=credito(&creditoAcomulado,5,1);	//adiciona 5euro
											printk("$$ O seu credito atual e de: %d EURO \n", rtrn);
											ret_bota._5E=false;	

										}else{if(ret_bota._10E == true)
												{ 
												rtrn=credito(&creditoAcomulado,10,1);	//adiciona 10euro
												printk("$$ O seu credito atual e de: %d EURO \n", rtrn);
												ret_bota._10E=false;	
												}
											}
									} 
							}	

						state_showMovie=true;					//permite escrever novamente as infoirmaçoões do filme atual e do credito no state_showMovie
						
					}//fim de if(ret_bota._1E==true || ret_bota._2E==true || ret_bota._10E==true || ret_bota._10E==true)

			break;

						/*######################## ESTADO 3 ######################*/
			case notByMovie:								
							/* ########################################*/
							/* ###### ACTIVIDADES DESTE ESTADO ####### */
					if(state_notByMovie==true)
					{
						ret_filme = showFilme(currentMovie); 			//mostra o filme selecionado
						printk("O fime: %s NÂO FOI Comprado\n",ret_filme.nomeFilme);
					
						rtrn=credito(&creditoAcomulado,0,0); 			//Mostra o crédito atual
						printk("O credito acolmulado e: %d \n", rtrn);	//mostra o credito acomulado
					
					
					state_showMovie=true;
					state_buyMovie=true;
					state_notByMovie=false;
					}

					/*###################################################################*/	
				    /*########## CONDIÇOES/EVENTOS para SALTAR de estado ################*/
					if(ret_bota._ret == true)
					{
						state=showMovie;		/*Salta para o Estado n1 -> showMovei*/
						state_showMovie=true;	/*permite que se escreva novamente as informações do filme atual */
						ret_bota._ret=false;	/*manda a flag de sinalização do estado a baixo*/	
					}

					if(ret_bota._1E==true || ret_bota._2E==true || ret_bota._5E==true || ret_bota._10E==true)	//Inserido dinheiro			
					{
						state=showMovie;								//salta para o primeiro estado ->showMovie
						if(ret_bota._1E == true)						//actualiza o credito mediante o dinheiro colocado
						{
							rtrn=credito(&creditoAcomulado,1,1);	//adiciona 1euro
							printk("$$ O seu credito atual e de: %d EURO \n", rtrn);
							ret_bota._1E=false;	

						}else{ if(ret_bota._2E == true)
								{
									rtrn=credito(&creditoAcomulado,2,1);	//adiciona 2euro
									printk("$$ O seu credito atual e de: %d EURO \n", rtrn);
									ret_bota._2E=false;	

								}else{ if(ret_bota._5E == true)
										{
											rtrn=credito(&creditoAcomulado,5,1);	//adiciona 5euro
											printk("$$ O seu credito atual e de: %d EURO \n", rtrn);
											ret_bota._5E=false;	

										}else{if(ret_bota._10E == true)
												{ 
												rtrn=credito(&creditoAcomulado,10,1);	//adiciona 10euro
												printk("$$ O seu credito atual e de: %d EURO \n", rtrn);
												ret_bota._10E=false;	
												}
											}
									} 
							}	

						state_showMovie=true;					//permite escrever novamente as infoirmaçoões do filme atual e do credito no state_showMovie
						
					}//fim de if(ret_bota._1E==true || ret_bota._2E==true || ret_bota._10E==true || ret_bota._10E==true)



				/*condiÃ§Ãµe/eventos para saltar de estado*/
			break;


			default:
				/*nÃ£o existem instruÃ§Ãµes de defaultiu*/

		}//fim do switch(state)
	
		writeBot(ret_bota);			/*atualiza todas as flag dos botoes*/	
		k_msleep(500);				/*Tempo de refresh da Máquina de estados*/

	}//fim do while(1)
}//fim do void initStateMachine(void)


/* 
 * The main function
 */
void main(void)
{
	int ret;
	
		
	/*Inicializar os devices em MyEventes.c*/
	initDevicesIO();


	/*botões funciona com interrupções -> devolve apenas uma mensagem a dizer que foi clicado*/


	/*funções que gere lista de filmes*/
	alocListMovies();

	/*escreve na lista os filmes presentes no guião do trabalho*/
	creatListMovies();
	
	

	printk("\n\n###################################\n");
	printk("# Máquinas de Estados inicializada #\n");
	printk("###################################\n\n");


	initStateMachine();
	

}