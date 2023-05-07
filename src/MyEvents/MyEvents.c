#include "MyEvents.h"

/**
 * /autor
 * /date
 * /bugs: 
*/

/**
*função invovado pela ISR do Botão_0
*quando invocada simula a inserção de 1euro
*/
void button0_pressed(void)
{
	printk("moeda 1€ inserida\n");
}

/**
*função invovado pela ISR do Botão_1
*quando invocada simula a inserção de 1euro
*/
void button1_pressed(void)
{
	printk("moeda 2€ inserida\n");
}

/**
*função invovado pela ISR do Botão_2
*quando invocada simula a inserção de 1euro
*/
void button2_pressed(void)
{
	printk("moeda 5€ inserida\n");
}


/**
*função invovado pela ISR do Botão_3
*quando invocada simula a inserção de 1euro
*/
void button3_pressed(void)
{
	printk("moeda 10€ inserida\n");
}


/**
 * Função que inicia e configura os devicesrivers(hradware)
*/
void init_config_Devices(void)
{
    int ret;
	
	/* ######Check if device is PREPARADO...####### */
            /*LEDS - outputs*/
	if (!device_is_ready(led0.port))  
	{
		printk("Error: led0: %s nao esta ok \n", led0.port->name);
		return;
	}

  	if(!device_is_ready(led1.port))
	{
		printk("Error: led0: %s nao esta ok \n", led0.port->name);
		return;
	}

	if(!device_is_ready(led2.port))
	{
		printk("Error: led0: %s nao esta ok \n", led0.port->name);
		return;
	}

	if(!device_is_ready(led3.port))
	{
		printk("Error: led0: %s nao esta ok \n", led3.port->name);
		return;
	}
        /* ********Botões -> inputs********** */
	if(!device_is_ready(button0.port))
	{
		printk("Error: Botao1: %s nao esta ok \n", button0.port->name);
	}

    if(!device_is_ready(button1.port))
	{
		printk("Error: Botao1: %s nao esta ok \n", button1.port->name);
	}
    
    if(!device_is_ready(button2.port))
	{
		printk("Error: Botao2: %s nao esta ok \n", button2.port->name);
	}
    
    if(!device_is_ready(button3.port))
	{
		printk("Error: Botao3: %s nao esta ok \n", button3.port->name);
	}

	/* **********Configure the GPIO pin for output************** */
	ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_INACTIVE);
	if (ret < 0)
	{
		printk("Error: %d gpio_pin_configure_dt falhou PARA LED0 ok \n", ret);
		return;
	}

	ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_INACTIVE);
	if (ret < 0)
	{
		printk("Error: %d gpio_pin_configure_dt falhou PARA LED1 ok \n", ret);
		return;
	}

	ret = gpio_pin_configure_dt(&led2, GPIO_OUTPUT_INACTIVE);
	if (ret < 0)
	{
		printk("Error: %d gpio_pin_configure_dt falhou PARA LED2 ok \n", ret);
		return;
	}

	ret = gpio_pin_configure_dt(&led3, GPIO_OUTPUT_INACTIVE);
	if (ret < 0)
	{
		printk("Error: %d gpio_pin_configure_dt falhou PARA LED3 ok \n", ret);
		return;
	}

        /* **********Configure the GPIO pin for input************** */
	ret = gpio_pin_configure_dt(&button0, GPIO_INPUT | GPIO_PULL_UP);
	if ( ret < 0 )
	{
		printk("Error: %d gpio_pin_configure_dt falhou PARA BUTTON0 ok \n", ret);
		return;
	}
    ret = gpio_pin_configure_dt(&button1, GPIO_INPUT | GPIO_PULL_UP);
	if ( ret < 0 )
	{
		printk("Error: %d gpio_pin_configure_dt falhou PARA BUTTON1 ok \n", ret);
		return;
	}
    ret = gpio_pin_configure_dt(&button1, GPIO_INPUT | GPIO_PULL_UP);
	if ( ret < 0 )
	{
		printk("Error: %d gpio_pin_configure_dt falhou PARA BUTTON2 ok \n", ret);
		return;
	}
    ret = gpio_pin_configure_dt(&button1, GPIO_INPUT | GPIO_PULL_UP);
	if ( ret < 0 )
	{
		printk("Error: %d gpio_pin_configure_dt falhou PARA BUTTON3 ok \n", ret);
		return;
	}

	/* **********Configurar a interrupção para os pinos dos botões**************** */
	ret = gpio_pin_interrupt_configure_dt(&button0, GPIO_INT_EDGE_TO_ACTIVE);
	if ( ret < 0 )
	{
		printk("Error: %d gpio_pin_interrupt_dt falhou PARA BUTTON0 ok \n", ret);
		return;
	}
    ret = gpio_pin_interrupt_configure_dt(&button1, GPIO_INT_EDGE_TO_ACTIVE);
	if ( ret < 0 )
	{
		printk("Error: %d gpio_pin_interrupt_dt falhou PARA BUTTON1 ok \n", ret);
		return;
	}
    ret = gpio_pin_interrupt_configure_dt(&button2, GPIO_INT_EDGE_TO_ACTIVE);
	if ( ret < 0 )
	{
		printk("Error: %d gpio_pin_interrupt_dt falhou PARA BUTTON2 ok \n", ret);
		return;
	}
    ret = gpio_pin_interrupt_configure_dt(&button3, GPIO_INT_EDGE_TO_ACTIVE);
	if ( ret < 0 )
	{
		printk("Error: %d gpio_pin_interrupt_dt falhou PARA BUTTON3 ok \n", ret);
		return;
	}
	printk("########### TODOS O DISPOSITIVOS INICIALIZADOS COM SUCESSO!!! ########\n\n");



	/* ********Inicializar a estrutura para a chamada da função da interrupt ***** */
	gpio_init_callback(&button0_cb_data, button0_pressed, BIT(button0.pin) );
    gpio_init_callback(&button1_cb_data, button1_pressed, BIT(button1.pin) );
    gpio_init_callback(&button2_cb_data, button2_pressed, BIT(button2.pin) );
    gpio_init_callback(&button3_cb_data, button3_pressed, BIT(button3.pin) );



	/*  **********adicionar a função de calbak chamda pela************ */
	gpio_add_callback(button0.port, &button0_cb_data);
    gpio_add_callback(button1.port, &button1_cb_data);
    gpio_add_callback(button2.port, &button2_cb_data);
    gpio_add_callback(button3.port, &button3_cb_data);


}

void test_Leds(void)
{
		/* Toggle the led */
		/* Could be used instead "ret = gpio_pin_toggle_dt(&led);" (simpler-one line only) */
		ret = gpio_pin_set_dt(&led0,ledstate);
		k_msleep(SLEEP_TIME_MS);
		ret = gpio_pin_set_dt(&led1,ledstate);
		k_msleep(SLEEP_TIME_MS);
		ret = gpio_pin_set_dt(&led2,ledstate);
		k_msleep(SLEEP_TIME_MS);
		ret = gpio_pin_set_dt(&led3,ledstate);
		
		k_msleep(SLEEP_TIME_MS);
		if (ret < 0)
		{
			return;
		}

		if(ledstate == 1)
			ledstate = 0;
		else
			ledstate = 1; 


		/* Sleep */
		//k_msleep(SLEEP_TIME_MS);

}