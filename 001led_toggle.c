/*
 * 001led_toggle.c
 *
 *  Created on: Jul 4, 2026
 *      Author: ASUS
 */

#include"stm32f4xx.h"
#include"stm32f4xx_gpio_driver.h"

void delay(void)
{
	for(uint32_t i = 0; i<500000 ; i++);
}
int main(void)
{
	GPIO_Handle_t GpioLed;
	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinpuPdControl = GPIO_NO_PUPD;


	GPIO_PeriClockControl(GPIOA,ENABLE);
	GPIO_Init(&GpioLed);

	while(1)
	{
		GPIO_ToggleOutputPin(GPIOA,GPIO_PIN_NO_5);    //Toggles Output
		delay();
	}



}

