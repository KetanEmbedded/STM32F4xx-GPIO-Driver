/*
 * stm32f4xx_gpio_driver.h
 *
 *  Created on: Jul 3, 2026
 *      Author: ASUS
 */

#ifndef DRIVERS_INC_STM32F4XX_GPIO_DRIVER_H_
#define DRIVERS_INC_STM32F4XX_GPIO_DRIVER_H_

#include<stm32f4xx.h>



typedef struct
{
	uint8_t GPIO_PinNumber;   //-> possible values from "@GPIO__PIN_NUMBERS"
	uint8_t GPIO_PinMode;     //-> possible values from "@GPIO_PIN_MODES "
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_PinpuPdControl;
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_PinAltFunMode;


}GPIO_PinConfig_t;

typedef struct
{
	// pointer to hold the base address of GPIO peripheral

	GPIO_RegDef_t *pGPIOx; // This holds the Base Address of the GPIO port to which the pin belongs
	GPIO_PinConfig_t GPIO_PinConfig; // This holds the GPIO Pin configuration settings

}GPIO_Handle_t;


/*@GPIO__PIN_NUMBERS
 * GPIO pin numbers
 */
#define GPIO_PIN_NO_0    0
#define GPIO_PIN_NO_1    1
#define GPIO_PIN_NO_2    2
#define GPIO_PIN_NO_3    3
#define GPIO_PIN_NO_4    4
#define GPIO_PIN_NO_5    5
#define GPIO_PIN_NO_6    6
#define GPIO_PIN_NO_7    7
#define GPIO_PIN_NO_8    8
#define GPIO_PIN_NO_9    9
#define GPIO_PIN_NO_10   10
#define GPIO_PIN_NO_11   11
#define GPIO_PIN_NO_12   12
#define GPIO_PIN_NO_13   13
#define GPIO_PIN_NO_14   14
#define GPIO_PIN_NO_15   15

/*@GPIO_PIN_MODES
 * GPIO pin possible modes
 */
#define GPIO_MODE_IN            0   //non interrupt mode
#define GPIO_MODE_OUT           1  //non interrupt mode
#define GPIO_MODE_ALTFN         2  //non interrupt mode
#define GPIO_MODE_ANALOG        3  //non interrupt mode
#define GPIO_MODE_IT_FT         4  //interrupt mode
#define GPIO_MODE_IT_RT         5  //interrupt mode
#define GPIO_MODE_IT_RFT        6  //interrupt mode

/*
 * GPIO pin possible Output Types
 */

#define GPIO_OP_TYPE_PP     0
#define GPIO_OP_TYPE_OD     1

/*
 * GPIO pin possible output Speeds
 *
 */
#define GPIO_SPEED_LOW           0
#define GPIO_SPEED_MEDIUM        1
#define GPIO_SPEED_FAST          2
#define GPIO_SPEED_HIGH          3

/*
 * GPIO pin Pull up and Pull down configuration  macros
 */
#define GPIO_NO_PUPD                 0
#define GPIO_PIN_PU                  1
#define GPIO_PIN_PD                  2

/************************************APIs Supported by This Driver**************************************************************
 *                      for more ifo about APIs check the function definations
 *******************************************************************************************************************************/

/*
 * Peripheral clock Setup
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

//Init and DeInit

void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

//Data Read and Write
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx,uint8_t GPIO_PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t GPIO_PinNumber,uint8_t value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx,uint16_t value);

// Toggle Output
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t GPIO_PinNumber);

//IRQ configuration and ISR Handling
void GPIO_IRQInterruptConfig(uint8_t IRQNumber,uint8_t EnorDi);
void GPIO_IRQHandling(uint8_t GPIO_PinNumber);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority);










#endif /* DRIVERS_INC_STM32F4XX_GPIO_DRIVER_H_ */
