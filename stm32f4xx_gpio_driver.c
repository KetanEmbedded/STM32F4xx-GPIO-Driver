/*
 * stm32f4xx_gpio_driver.c
 *
 *  Created on: Jul 3, 2026
 *      Author: ASUS
 */

#include"stm32f4xx_gpio_driver.h"



/*
 * @fn          GPIO_PeriClockControl
 * @brief       Enables or disables the peripheral clock for a given GPIO port
 *
 * @param[in]   pGPIOx    - Base address of the GPIO peripheral (GPIOA, GPIOB, etc.)
 * @param[in]   EnorDi    - ENABLE or DISABLE macro
 *
 * @return      None
 * @note        Must be called before using any GPIO peripheral
 */

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
			{
				if(pGPIOx == GPIOA)
				{
					GPIOA_PCLK_EN();
				}else if(pGPIOx == GPIOB)
				{
					GPIOB_PCLK_EN();
				}else if(pGPIOx == GPIOC)
				{
					GPIOC_PCLK_EN();
				}else if(pGPIOx == GPIOD)
				{
					GPIOD_PCLK_EN();
				}else if(pGPIOx == GPIOE)
				{
					GPIOE_PCLK_EN();
				}else if(pGPIOx == GPIOF)
				{
					GPIOF_PCLK_EN();
				}else if(pGPIOx == GPIOG)
				{
					GPIOG_PCLK_EN();
				}else if(pGPIOx == GPIOH)
				{
					GPIOH_PCLK_EN();
				}

		}
			else
			{
				if(pGPIOx == GPIOA)
						{
							GPIOA_PCLK_DI();
						}else if(pGPIOx == GPIOB)
						{
							GPIOB_PCLK_DI();
						}else if(pGPIOx == GPIOC)
						{
							GPIOC_PCLK_DI();
						}else if(pGPIOx == GPIOD)
						{
							GPIOD_PCLK_DI();
						}else if(pGPIOx == GPIOE)
						{
							GPIOE_PCLK_DI();
						}else if(pGPIOx == GPIOF)
						{
							GPIOF_PCLK_DI();
						}else if(pGPIOx == GPIOG)
						{
							GPIOG_PCLK_DI();
						}else if(pGPIOx == GPIOH)
						{
							GPIOH_PCLK_DI();
						}
			}


	}


/*
 * @fn          GPIO_Init
 * @brief       Initializes the GPIO pin according to the configuration
 *              specified in the GPIO handle structure
 *
 * @param[in]   pGPIOHandle - Pointer to GPIO handle structure containing
 *                            base address and pin configuration settings
 *                            (pin number, mode, speed, pull-up/down, output type, alt function)
 *
 * @return      None
 * @note        Call GPIO_PeriClockControl() to enable clock before calling this function
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp = 0;

	//1. configure the mode of GPIO pin
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		//The non-interrupt mode
		temp = ( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ));
		pGPIOHandle->pGPIOx->MODER &= ~( 0x3 <<  pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);// clearing
		pGPIOHandle->pGPIOx->MODER |= temp;   //setting

	}
	else
	{                                 //  (interrupt mode)


		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			//1. configure the falling triggered selection register (FTSR)

			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
			// clear the corresponding RTSR bit
			EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );

		}else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			//1. configure the falling triggered selection register (RTSR)

			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );

			// clear the corresponding FTSR bit

			EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );


		}else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			//1. Configure both the registers (FTSR and RTSR)

			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );


			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
		}

		//2.configure the GPIO Port selection in SYSCFG_EXTICR

		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber/4;
		uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber%4;
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
		SYSCFG_PCLK_EN();
		SYSCFG->EXTICR[temp1] = portcode << (temp2*4);


		//3.Enable the EXTI interrupt delivery using IMR
		EXTI->IMR |= 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;

	}
	temp=0;


	//2.configure the speed
	temp = ( pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ));
	pGPIOHandle->pGPIOx->OSPEEDR &= ~( 0x3 <<  pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);// clearing
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;

	temp = 0;

	//3. configure the PuPd setting
	temp = ( pGPIOHandle->GPIO_PinConfig.GPIO_PinpuPdControl << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ));
	pGPIOHandle->pGPIOx->PUPDR &= ~( 0x3 <<  pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);// clearing
	pGPIOHandle->pGPIOx->PUPDR |= temp;

	temp = 0;


	//4. configure the output type
	temp = ( pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType <<  pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
	pGPIOHandle->pGPIOx->OTYPER &= ~( 0x1 <<  pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);// clearing
    pGPIOHandle->pGPIOx->OTYPER |= temp;

    temp = 0;



	//5. configure the alternate functionality

	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		//Configure the alternate function registers
		uint32_t temp1,temp2;

		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber /8;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber %8;
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2 ));
    	pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2 ));

	}




}


/*
 * @fn          GPIO_DeInit
 * @brief       De-initializes the GPIO port by resetting all its registers
 *              to their default reset values
 *
 * @param[in]   pGPIOx    - Base address of the GPIO peripheral (GPIOA, GPIOB, etc.)
 *
 * @return      None
 * @note        Uses RCC AHB1 reset register to reset entire GPIO port
 */
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx == GPIOA)
			{
				GPIOA_REG_RESET();

			}else if(pGPIOx == GPIOB)
			{
				GPIOB_REG_RESET();

			}else if(pGPIOx == GPIOC)
			{
				GPIOC_REG_RESET();
			}else if(pGPIOx == GPIOD)
			{
				GPIOD_REG_RESET();
			}else if(pGPIOx == GPIOE)
			{
				GPIOE_REG_RESET();
			}else if(pGPIOx == GPIOF)
			{
				GPIOF_REG_RESET();
			}else if(pGPIOx == GPIOG)
			{
				GPIOG_REG_RESET();
			}else if(pGPIOx == GPIOH)
			{
				GPIOH_REG_RESET();
			}


}


/*
 * @fn          GPIO_ReadFromInputPin
 * @brief       Reads the current logic state of a specific input pin
 *
 * @param[in]   pGPIOx          - Base address of the GPIO peripheral
 * @param[in]   GPIO_PinNumber  - Pin number to read (0 to 15)
 *
 * @return      uint8_t         - Pin state: 0 (LOW) or 1 (HIGH)
 * @note        Pin must be configured as input mode before reading
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;
	value = (uint8_t) (pGPIOx->IDR  >>  PinNumber) & (0x00000001);
	return value;

}


/*
 * @fn          GPIO_ReadFromInputPort
 * @brief       Reads the logic state of all 16 pins of a GPIO port at once
 *
 * @param[in]   pGPIOx    - Base address of the GPIO peripheral
 *
 * @return      uint16_t  - 16-bit value representing state of all pins
 *                          Bit 0 = Pin 0, Bit 1 = Pin 1 ... Bit 15 = Pin 15
 * @note        Returns entire IDR register value
 */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
		value = (uint16_t)pGPIOx->IDR ;
		return value;

}


/*
 * @fn          GPIO_WriteToOutputPin
 * @brief       Writes a logic value (HIGH or LOW) to a specific output pin
 *
 * @param[in]   pGPIOx          - Base address of the GPIO peripheral
 * @param[in]   GPIO_PinNumber  - Pin number to write (0 to 15)
 * @param[in]   value           - GPIO_PIN_SET (1) for HIGH, GPIO_PIN_RESET (0) for LOW
 *
 * @return      None
 * @note        Pin must be configured as output mode before writing
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t value)
{
	if(value == GPIO_PIN_SET)
	{
		//Write 1 to the output data register at the bit filed corresponding to the  pin number
		pGPIOx->ODR |= (1 << PinNumber);
	}
	else
	{
		// write 0
		pGPIOx->ODR &= ~(1 << PinNumber);

	}


}


/*
 * @fn          GPIO_WriteToOutputPort
 * @brief       Writes a 16-bit value to all pins of a GPIO port at once
 *
 * @param[in]   pGPIOx    - Base address of the GPIO peripheral
 * @param[in]   value     - 16-bit value to write to the output port
 *                          Bit 0 = Pin 0, Bit 1 = Pin 1 ... Bit 15 = Pin 15
 *
 * @return      None
 * @note        Directly writes to ODR register — all 16 pins updated simultaneously
 */
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t value)
{

	pGPIOx->ODR = value;

}


/*
 * @fn          GPIO_ToggleOutputPin
 * @brief       Toggles the current output state of a specific pin
 *              (HIGH becomes LOW, LOW becomes HIGH)
 *
 * @param[in]   pGPIOx          - Base address of the GPIO peripheral
 * @param[in]   GPIO_PinNumber  - Pin number to toggle (0 to 15)
 *
 * @return      None
 * @note        Uses XOR operation on ODR register for atomic toggle
 */
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t GPIO_PinNumber)
{
	pGPIOx->ODR ^= (1 << GPIO_PinNumber);

}


/*
 * @fn          GPIO_IRQConfig
 * @brief       Configures the interrupt for a GPIO pin — enables/disables
 *              the IRQ and sets its priority in the NVIC
 *
 * @param[in]   IRQNumber    - IRQ number of the interrupt (from vector table)
 * @param[in]   IRQPriority  - Priority level for the interrupt (0 = highest)
 * @param[in]   EnorDi       - ENABLE or DISABLE macro
 *
 * @return      None
 * @note        Configures NVIC registers (ISER/ICER for enable/disable,
 *              IPR for priority)
 */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(IRQNumber <=31)
		{
			//program ISER0 reg
			*NVIC_ISER0 |= (1 << IRQNumber );

		}
		else if(IRQNumber > 31 && IRQNumber < 64 ) //32 to 63
		{
			//program ISER1 reg
			*NVIC_ISER1 |= (1 << IRQNumber % 32 );

		}
		else if(IRQNumber >=  64 && IRQNumber < 96 ) //64 to 95
		{
					//program ISER2 reg
			*NVIC_ISER2 |= (1 << IRQNumber % 64 );

		}
	}
	else
	{
		if(IRQNumber <= 31)
		{
			//program ICER0 reg
			*NVIC_ICER0 |= (1 << IRQNumber );

		}else if(IRQNumber > 31 && IRQNumber < 64)//32 to 63
		{
			//program ICER1 reg
			*NVIC_ICER1 |= (1 << IRQNumber % 32 );


		}else if(IRQNumber >= 64 && IRQNumber < 96)//64 to 95
		{
			//program ICER2 reg
			*NVIC_ICER2 |= (1 << IRQNumber % 64 );

		}
	}

}

/*
 * @fn          GPIO_IRQPriorityConfig
 * @brief       sets the priority of Interuupts
 *
 * @param[in]   IRQPriority
 * @param[in]
 *
 * @return      None
 * @note        Uses XOR operation on ODR register for atomic toggle */

void GPIO_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority)
{
	//1. first lets find out ipr register
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;

	uint8_t shift_amount = ( 8*iprx_section) + ( 8 - NO_PR_BITS_IMPLEMENTED);
	*(NVIC_PR_BASE_ADDR + iprx ) |=    (IRQPriority << shift_amount);


}


/*
 * @fn          GPIO_IRQHandling
 * @brief       Handles the interrupt for a specific GPIO pin
 *              Clears the EXTI pending register for that pin
 *
 * @param[in]
 *
 * @return      None
 * @note
 */
void GPIO_IRQHandling(uint8_t PinNumber)
{

	// clear the EXTI pr register corresponding to the pin number
	if(EXTI->PR & (1 << PinNumber))
	{
		// clear
		EXTI->PR |= (1 << PinNumber);
	}
}




