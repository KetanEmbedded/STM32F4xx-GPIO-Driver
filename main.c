/*
 * main.c
 *
 *  Created on: Jul 14, 2026
 *      Author: ASUS
 */
#include"stm32f4xx.h"

int main(void)
{
	return 0;
}

void EXTI0_IRQHandler(void)
{
	// handle the interuppt
	GPIO_IRQHandling(0);
}
