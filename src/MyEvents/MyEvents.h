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

/*Variaveis globais módulo  */
static int creditoAcomulado = 0;

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



void button_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins);

void initDevicesIO(void);

void testLeds(void);

/**
 * Função que atualiza o crédito disponivel
 * Inputs: 
 *  crd_acomulado -> ponteiro pra a zona de memoria onde está guardada o plafaudo
 *  in_crd -> crédito a tratar dentro da função(1€;2€;5€;10)
 *  add_sub -> operação a realizar: 0-> mostra crédito ; 1-> Adiciona crédito(in_crd); 2-> remove_credito(in_crd); 3->remove_ALLcredito
*/
int credito(int *crd_acomulado, int in_crd, int add_sub);

#endif