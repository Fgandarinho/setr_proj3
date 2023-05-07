#ifndef MY_EVENTS_H_
#define MY_EVENTS_H_
/*módulo que vai registar todos os eventos gerados pelo hardware
Ou seja
 1€ -> Botao_1 -> P0.11
 2€ -> Botao_2 -> P0.12
 5€ -> Botão_3 -> P0.24
10€ -> Botão_4 -> P0.25

B_Up ->        -> P0.03 
B_Down ->      -> P0.04
B_Select ->    -> P0.28
B_Return ->    -> P0.29
*/

#include <zephyr/kernel.h>          /* for k_msleep() */
#include <zephyr/device.h>          /* for device_is_ready() and device structure */
#include <zephyr/devicetree.h>	/* for DT_NODELABEL() */
#include <zephyr/drivers/gpio.h>    /* for GPIO api*/
#include <zephyr/sys/printk.h>		/*para printk*/

/* Define the sleep time, in ms (roughly half the period) */
#define SLEEP_TIME_MS 250

/* Get led 0 node ID. Refer to the DTS file to find "led0" node label
 *   (could also be obtained via alias, see below).
 */
#define LED0_NODE DT_NODELABEL(led0)
#define LED1_NODE DT_NODELABEL(led1)
#define LED2_NODE DT_NODELABEL(led2)
#define LED3_NODE DT_NODELABEL(led3)
#define SW0_NODE DT_NODELABEL(button0)
#define SW1_NODE DT_NODELABEL(button1)
#define SW2_NODE DT_NODELABEL(button2)
#define SW3_NODE DT_NODELABEL(button3)
/*
 * Get the device pointer, pin number, and configuration flags. A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
static const struct gpio_dt_spec led3 = GPIO_DT_SPEC_GET(LED3_NODE, gpios);
static const struct gpio_dt_spec button0 = GPIO_DT_SPEC_GET(SW0_NODE, gpios);
static const struct gpio_dt_spec button1 = GPIO_DT_SPEC_GET(SW1_NODE, gpios);
static const struct gpio_dt_spec button2 = GPIO_DT_SPEC_GET(SW2_NODE, gpios);
static const struct gpio_dt_spec button3 = GPIO_DT_SPEC_GET(SW3_NODE, gpios);
/*Variaveis Globais*/
static int ret, ledstate=0;


/* varialvel de callback para o botão_1*/
static struct gpio_callback button0_cb_data;
static struct gpio_callback button1_cb_data;
static struct gpio_callback button2_cb_data;
static struct gpio_callback button3_cb_data;



/*
* função que inicia e configura todos os dispositivos usados(hardware)
*/
void init_config_Devices(void);


/*
função a ser invocada pela ISR do Botão_1
*/
void button0_pressed(void);

/*
função a ser invocada pela ISR do Botão_2
*/
void button1_pressed(void);

/*
função a ser invocada pela ISR do Botão_3
*/
void button2_pressed(void);

/*
função a ser invocada pela ISR do Botão_3
*/
void button3_pressed(void);


/*
 função que testa os leds 
*/
void test_Leds(void);



#endif