#include "MyEvents.h"

/**
 * /autor
 * /date
 * /bugs: 
*/

/*estrutura para passar o estado de todos os botões*/
static struct botao bot;


/* Define a callback function. It is like an ISR (and runs in the cotext of an ISR) */
/* that is called when the button is pressed */
void button_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
	int i=0;

    /* Toggle led1 */
	gpio_pin_toggle(gpio0_dev,LED1_PIN);

	/* Identify the button(s) that was(ere) hit-> Feito pelo PROF.*/
/*	for(i=0; i<sizeof(buttons_pins); i++)
	{			
		if(BIT(buttons_pins[i]) & pins) 
		{
			printk("Button %d pressed\n\r",i+1);
		}
	}
*/
	if(BIT(buttons_pins[0]) & pins) 
	{
		printk("Botão 1_EUROS\n");
		bot._1E=true;
		
	}

	if(BIT(buttons_pins[1]) & pins) 
	{
		printk("Botão 2_EUROS\n");
		bot._2E=true;
	}

	if(BIT(buttons_pins[2]) & pins) 
	{
		printk("Botão 5_EUROS\n");
		bot._5E=true;
	}

	if(BIT(buttons_pins[3]) & pins) 
	{
		printk("Botão 10_EUROS\n");
		bot._10E=true;
	}

	if(BIT(buttons_pins[4]) & pins) 
	{
		printk("Botão UP\n");
		bot._up=true;
		
	}

	if(BIT(buttons_pins[5]) & pins) 
	{
		printk("Botão DOWN\n");
		bot._dw=true;
	}

	if(BIT(buttons_pins[6]) & pins) 
	{
		printk("Botão SELECT\n");
		bot._sel=true;
	}

	if(BIT(buttons_pins[7]) & pins) 
	{
		printk("Botão RETURN\n");
		bot._ret=true;
	}

}

void initDevicesIO(void)
{
	printk("-------> A inicializar devices\n\r");
	int ret, i;
	uint32_t pinmask = 0; /* Mask for setting the pins that shall generate interrupts */
	
	/* Check if gpio0 device is ready */
	if (!device_is_ready(gpio0_dev)) {
		printk("Error: gpio0 device is not ready\n");
		return;
	} else {
		printk("Success: gpio0 device is ready\n");
	}

	/* Configure the GPIO pins - LED1 for output and buttons 1-4 + IOPINS 2,4,28 and 29 for input
	 * Use internal pull-up to avoid the need for an external resistor (buttons) */
	ret = gpio_pin_configure(gpio0_dev,LED1_PIN, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		printk("Error: gpio_pin_configure failed for led1, error:%d\n\r", ret);
		return;
	}

	for(i=0; i<sizeof(buttons_pins); i++) {
		ret = gpio_pin_configure(gpio0_dev, buttons_pins[i], GPIO_INPUT | GPIO_PULL_UP);
		if (ret < 0) {
			printk("Error: gpio_pin_configure failed for button %d/pin %d, error:%d\n\r", i+1,buttons_pins[i], ret);
			return;
		} else {
			printk("Success: gpio_pin_configure for button %d/pin %d\n\r", i+1,buttons_pins[i]);
		}
	}

	/* Configure the interrupt on the button's pin */
	for(i=0; i<sizeof(buttons_pins); i++) {
		ret = gpio_pin_interrupt_configure(gpio0_dev, buttons_pins[i], GPIO_INT_EDGE_TO_ACTIVE );
		if (ret < 0) {
			printk("Error: gpio_pin_interrupt_configure failed for button %d / pin %d, error:%d", i+1, buttons_pins[i], ret);
			return;
		}
	}

	/* HW init done!*/
	printk("All devices initialized sucesfully!\n\r");

	/* Initialize the static struct gpio_callback variable   */
	pinmask=0;
	for(i=0; i<sizeof(buttons_pins); i++) {
		pinmask |= BIT(buttons_pins[i]);
	}
    gpio_init_callback(&button_cb_data, button_pressed, pinmask); 	
	
	/* Add the callback function by calling gpio_add_callback()   */
	gpio_add_callback(gpio0_dev, &button_cb_data);

}

/*testa LEDS -> TOGGLE*/
void testLeds(void)
{
    gpio_pin_toggle(gpio0_dev,LED1_PIN);
}

/*gere o crédito*/
int credito(int *crd_acomulado, int in_crd, int add_sub)
{
	int ret;

	if(add_sub==0) 						/*mostra o crédito exixtente*/
	{
		ret=*crd_acomulado;	
	}
	if(add_sub==1)
	{
		*crd_acomulado=*crd_acomulado + in_crd;
		ret= *crd_acomulado;
	}

	if(add_sub==2 && *crd_acomulado>=in_crd)
	{
		*crd_acomulado=*crd_acomulado - in_crd;
		ret= *crd_acomulado;
	}

	if(add_sub==3)
	{
		*crd_acomulado=0;
		ret= *crd_acomulado;
	}
	return ret;
}
/*Lê a estruura loca das flags dos botes*/
struct botao readBot()
{
	struct botao ret_botoes;

	ret_botoes._1E = bot._1E;
	ret_botoes._2E = bot._2E;
	ret_botoes._5E = bot._5E;
	ret_botoes._10E = bot._10E;
	ret_botoes._up = bot._up;
	ret_botoes._dw = bot._dw;
	ret_botoes._sel = bot._sel;
	ret_botoes._ret = bot._ret;

	return ret_botoes;
}

/*escreve e atuliza a estrutura local com as flags de todos os botoes*/
void writeBot(struct botao bt)
{
	bot._1E = bt._1E;
	bot._2E = bt._2E;
	bot._5E = bt._5E;
	bot._10E = bt._10E;
	bot._up = bt._up;
	bot._dw = bt._dw;
	bot._sel = bt._sel;
	bot._ret = bt._ret;

	
}