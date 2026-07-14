/*
 * 002led_button.c
 *
 *  Created on: Jul 5, 2026
 *      Author: ASUS
 */




#include"stm32f4xx.h"
#include"stm32f4xx_gpio_driver.h"

#define LOW          0
#define BTN_PRESSED  LOW
void delay(void)
{
	for(uint32_t i = 0; i<500000/2 ; i++);
}

int main(void)
{
	GPIO_Handle_t GpioLed,GpioBtn;

	//1.This is LED GPIO configuration
	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinpuPdControl = GPIO_NO_PUPD;




	GPIO_PeriClockControl(GPIOA,ENABLE);
	GPIO_Init(&GpioLed);

	//2.This is Button GPIO configuration


	GpioBtn.pGPIOx = GPIOC;
	GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioBtn.GPIO_PinConfig.GPIO_PinpuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOC,ENABLE);
	GPIO_Init(&GpioBtn);

	while(1)
	{
		if(GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_NO_13) == BTN_PRESSED)
		{
			delay();
			GPIO_ToggleOutputPin(GPIOA,GPIO_PIN_NO_5);    //Toggles Output

		}
	}



}


