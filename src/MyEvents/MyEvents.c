#include "MyEvents.h"

/**
 * /autor
 * /date
 * /bugs: 
*/




/* Define a callback function. It is like an ISR (and runs in the cotext of an ISR) */
/* that is called when the button is pressed */
void button_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
	int i=0;

    /* Toggle led1 */
	gpio_pin_toggle(gpio0_dev,LED1_PIN);

	/* Identify the button(s) that was(ere) hit*/
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
		int ret;
		printk("Inserido 1_EURO\n");
		ret = credito(&creditoAcomulado, 1, 1);
		printk(" ----------------------> Tem: %d \n",ret);

	}

	if(BIT(buttons_pins[1]) & pins) 
	{
		int ret;
		printk(" Inserido 2_EUROS\n");
		ret = credito(&creditoAcomulado, 2, 1);
		printk(" ----------------------> Tem: %d \n",ret);

	}

	if(BIT(buttons_pins[2]) & pins) 
	{
		int ret;
		printk("Inserido 5_EUROS\n");
		ret = credito(&creditoAcomulado, 5, 1);
		printk(" ----------------------> Tem: %d \n",ret);

	}
	if(BIT(buttons_pins[3]) & pins) 
	{
		int ret;
		printk("Inserido 10_EUROS\n");
		ret = credito(&creditoAcomulado, 10, 1);
		printk(" ----------------------> Tem: %d \n",ret);

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

void testLeds(void)
{
    gpio_pin_toggle(gpio0_dev,LED1_PIN);
}


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