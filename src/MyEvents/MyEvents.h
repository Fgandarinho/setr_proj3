/** \file MyEvents.h
 *	\author Fernando Gandarinho e Tomás Silva
 *
 *	\brief Este ficheiro pretende definir as funçoes de criação e
 * 		gestao dos eventos/interrupções. 
 *  
 * 	\date 16/05/2023
 * 	\bug There are no bugs 
 */
#ifndef MY_EVENTS_H_
#define MY_EVENTS_H_

/* Includes. Add according to the resources used  */
#include <zephyr/kernel.h>          /* for k_msleep() */
#include <zephyr/device.h>          /* for device_is_ready() and device structure */
#include <zephyr/devicetree.h>		/* for DT_NODELABEL() */
#include <zephyr/drivers/gpio.h>    /* for GPIO api*/
#include <zephyr/sys/printk.h>      /* for printk()*/

/* Use a "big" sleep time to reduce CPU load (button detection int activated, not polled) */
#define SLEEP_TIME_MS   60*1000 


/*Flags que sinalização quando os botões são pressonados*/
/*IMPORTANTE: é da responsabilidade do leitor da flag voltar a coloca-la a false*/
/** \brief Definiçao da estrutura dos botões
 *    Esta estrutura contém os vários botões a ser utilizado no projeto
 * 
 * 	\author Fernando Gandarinho e Tomás Silva
 * 	\param[in] _up: define o botão up para o menu dos filmes (Filme seguinte)
 * 	\param[in] _dw: define o botão down para o menu dos filmes (Filme anterior)
 * 	\param[in] _sel: define o botão de seleção do filme (Seleciona o filme)
 * 	\param[in] _ret: define o botão retorno do valor inserido (Retorna o valor inserido)
 * 	\param[in] _1E: define o botão de 1€ (Adiciona 1€ ao crédito)
 *  \param[in] _2E: define o botão de 2€ (Adiciona 2€ ao crédito)
 *  \param[in] _5E: define o botão de 5€ (Adiciona 5€ ao crédito)
 *  \param[in] _10E: define o botão de 10€ (Adiciona 10€ ao crédito)      
 * 
 * 	\date 16/05/2023
 * 
 */
struct botao
{
    bool _up;
    bool _dw; 
    bool _sel;
    bool _ret;
    bool _1E;
    bool _2E;
    bool _5E;
    bool _10E;
};

/* Set the pins used for LED and buttons */
/* LED 1 and buttons 1-4 are the ones on board */
/* buttons 5-8 are connected to pins labeled A0 ... A3 (gpio0 pins 3,4,28,29) */
#define LED1_PIN 13
static const uint8_t buttons_pins[] = {11,12,24,25,3,4,28,29}; /* vector with pins where buttons are connected */
	
/* Get node ID for GPIO0, which has leds and buttons */ 
#define GPIO0_NODE DT_NODELABEL(gpio0)

/* Now get the device pointer for GPIO0 */
static const struct device * gpio0_dev = DEVICE_DT_GET(GPIO0_NODE);

/* Define a variable of type static struct gpio_callback, which will latter be used to install the callback
*  It defines e.g. which pin triggers the callback and the address of the function */
static struct gpio_callback button_cb_data;


/** \brief Intancia a interrupção quando o botão é pressionado
 * 
 * 	\author Fernando Gandarinho e Tomás Silva
 * 	\param[in] *dev: device pointer
 * 	\param[in] *cb: variable of type static struct gpio_callback
 *  \param[in] pins: Pin number
 * 	\date 16/05/2023
 * 
 */
void button_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins);


/** \brief Inicializa os dispositivos de IO
 * 
 * 	\author Fernando Gandarinho e Tomás Silva
 * 	
 * 	\date 16/05/2023
 * 
 */
void initDevicesIO(void);

/** \brief Função para o LED alternar o seu valor a cada interrupção
 * 
 * 	\author Fernando Gandarinho e Tomás Silva
 * 	
 * 	\date 16/05/2023
 * 
 */
void testLeds(void);

/**
 * \brief Função que atualiza o crédito disponivel
 *  
 * \author Fernando Gandarinho e Tomás Silva
 * 	\param[in] *crd_acomulado: Ponteiro para a zona de memoria onde está guardada o plafond
 * 	\param[in] in_crd: Crédito introduzido (1€;2€;5€;10)
 *  \param[in] add_sub: Operação a realizar: 0-> mostra crédito ; 1-> Adiciona crédito(in_crd); 2-> subtrai_credito(in_crd); 3->remove_ALLcredito
 * 	\date 16/05/2023
*/
int credito(int *crd_acomulado, int in_crd, int add_sub);

/*Função que lê nao estado de todas as flags dos botões*/
/**
 * \brief Função que lê nao estado de todas as flags dos botões
 *  
 * \author Fernando Gandarinho e Tomás Silva
 *  \param[out] ret_botoes, retorna a estrutura botao
 *
 * 	\date 16/05/2023
*/
struct botao readBot();

/*Função que atualiza a flag de um botão */
/**
 * \brief Função que atualiza a flag de um botão
 *  
 * \author Fernando Gandarinho e Tomás Silva
 *  \param[in] bt: estrutura botao
 *
 * 	\date 16/05/2023
*/
void writeBot(struct botao bt);

#endif
