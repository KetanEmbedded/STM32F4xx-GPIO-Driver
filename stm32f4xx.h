/*
 * stm32f4xx.h
 *
 *  Created on: Jun 30, 2026
 *      Author: ASUS
 */

#include<stdint.h>

/****************************************PROCESOR SPECIFIC DETAILS********************************************************/
//ARM cortex Mx processors NVIC ISERx Register addresses
#define _vo volatile
#define NVIC_ISER0        ((_vo uint32_t*)0xE000E100)
#define NVIC_ISER1        ((_vo uint32_t*)0xE000E104)
#define NVIC_ISER2        ((_vo uint32_t*)0xE000E108)

//ARM cortex Mx processors NVIC ICERx Register addresses


#define NVIC_ICER0        ((_vo uint32_t*)0xE000E180)
#define NVIC_ICER1        ((_vo uint32_t*)0xE000E184)
#define NVIC_ICER2        ((_vo uint32_t*)0xE000E188)
#define NVIC_ICER3        ((_vo uint32_t*)0xE000E18C)


/*********************************************************************************************************************/

/*
 * priority register addresses
 */

#define NVIC_PR_BASE_ADDR  ((_vo uint32_t*)0xE000E400)
//Num of priority bits implemented in priority register

#define NO_PR_BITS_IMPLEMENTED         4



/*********************************************************************************************/
#ifndef DRIVERS_INC_STM32F4XX_H_
#define DRIVERS_INC_STM32F4XX_H_

/* base addresses f Flash and SRAM memories */

#define FLASH_BASEADDR       0x08000000U   //This is the base address of flash memory

#define SRAM1_BASEADDR       0x20000000U   //112kb  base address of SRAM1
#define SRAM2_BASEADDR       0x2001C000U // Base address of SRAM2
#define SRAM SRAM1_BASEADDR

#define ROM_BASEADDR         0x1FFF0000U   //"System Memory" in Reference manual


/* AHBx and APBx Bus peripheral base address */

#define PERIPH_BASE   0X40000000

#define APB1_PERIPH_BASE   PERIPH_BASE
#define APB2_PERIPH_BASE   0x40010000

#define AHB1_PERIPH_BASE   0x40020000
#define AHB2_PERIPH_BASE   0x50000000

/* Base address of all peripherals which are hanging on AHB1 Bus
 *
 *TODO: Complete for all other peripherals
 */

#define GPIOA_BASEADDR   (AHB1_PERIPH_BASE + 0x0000) //(AHB1_PERIPH_BASE + offset)
#define GPIOB_BASEADDR   (AHB1_PERIPH_BASE + 0x0400) // same here
#define GPIOC_BASEADDR   (AHB1_PERIPH_BASE + 0x0800) // same here
#define GPIOD_BASEADDR   (AHB1_PERIPH_BASE + 0x0C00) // same here
#define GPIOE_BASEADDR   (AHB1_PERIPH_BASE + 0x1000) // same here
#define GPIOF_BASEADDR   (AHB1_PERIPH_BASE + 0x1400) // same here
#define GPIOG_BASEADDR   (AHB1_PERIPH_BASE + 0x1800) // same here
#define GPIOH_BASEADDR   (AHB1_PERIPH_BASE + 0x1C00) // same here
#define RCC_BASEADDR     (AHB1_PERIPH_BASE + 0x3800) // same here


/* Base address of all peripherals which are hanging on APB1 Bus
 *
 */

#define I2C1_BASEADDR    (APB1_PERIPH_BASE + 0x5400)//   (APB1_PERIPH_BASE + offset)
#define I2C2_BASEADDR    (APB1_PERIPH_BASE + 0x5800)// same here
#define I2C3_BASEADDR    (APB1_PERIPH_BASE + 0x5C00)// same here

#define SPI2_BASEADDR    (APB1_PERIPH_BASE + 0x3800)// same here
#define SPI3_BASEADDR    (APB1_PERIPH_BASE + 0x3C00)// same here

#define USART2_BASEADDR    (APB1_PERIPH_BASE + 0x4400)// same here
#define USART3_BASEADDR    (APB1_PERIPH_BASE + 0x4800)// same here

#define UART4_BASEADDR    (APB1_PERIPH_BASE + 0x4C00)// same here
#define UART5_BASEADDR    (APB1_PERIPH_BASE + 0x5000)// same here

/* Base address of all peripherals which are hanging on APB2 Bus
 *
 */

#define EXTI_BASEADDR    (APB2_PERIPH_BASE + 0x3C00)//   (AHB2_PERIPH_BASE + offset)

#define SPI1_BASEADDR    (APB2_PERIPH_BASE + 0x3000)// same here

#define USART1_BASEADDR    (APB2_PERIPH_BASE + 0x1000)// same here0)
#define USART6_BASEADDR    (APB2_PERIPH_BASE + 0x1400)// same here

#define SYSCFG_BASEADDR    (APB2_PERIPH_BASE + 0x3800)// same here



/**************************************Peripherl register defination structures*******************************************/

//NOTE: Register of Peripheral are specific to MCU


typedef struct
{
   volatile uint32_t MODER;     // Mode Register - configures each pin as input/output/alternate function/analog
   volatile uint32_t OTYPER;    // Output Type Register - sets output as push-pull or open-drain
   volatile uint32_t OSPEEDR;   // Output Speed Register - controls pin speed (low/medium/high/very high)
   volatile uint32_t PUPDR;     // Pull-Up/Pull-Down Register - enables internal pull-up or pull-down resistor
   volatile uint32_t IDR;       // Input Data Register - reads current logic state of input pins (read only)
   volatile uint32_t ODR;       // Output Data Register - sets output pins HIGH(1) or LOW(0)
   volatile uint32_t BSRR;      // Bit Set/Reset Register - atomically sets or resets specific output bits
   volatile uint32_t LCKR;      // Lock Register - locks pin configuration to prevent accidental changes
   volatile uint32_t AFR[2];    // Alternate Function Register - AFR[0] for pins 0-7, AFR[1] for pins 8-15

} GPIO_RegDef_t;

/*
 * Peripheral register defination structure for EXTI
 */
typedef struct
{
   volatile uint32_t IMR;
   volatile uint32_t EMR;
   volatile uint32_t RTSR;
   volatile uint32_t FTSR;
   volatile uint32_t IDR;
   volatile uint32_t SWIER;
   volatile uint32_t PR;
   volatile uint32_t LCKR;
   volatile uint32_t AFR[2];

} EXTI_RegDef_t;

/*
 * peripheral Register definition structure for SYSCFG
 */
typedef struct
{
	volatile uint32_t MEMRMP;
	volatile uint32_t PMC;
	volatile uint32_t EXTICR[4];
    volatile uint32_t RESERVED1[2];
	volatile uint32_t CMPCR;
	volatile uint32_t RESERVED2[2];
	volatile uint32_t CFGR;





}SYSCFG_RegDef_t;




	typedef struct
	{
	    volatile uint32_t CR;             // 0x00 : Clock Control Register
	    volatile uint32_t PLLCFGR;        // 0x04 : PLL Configuration Register
	    volatile uint32_t CFGR;           // 0x08 : Clock Configuration Register
	    volatile uint32_t CIR;            // 0x0C : Clock Interrupt Register

	    volatile uint32_t AHB1RSTR;       // 0x10 : AHB1 Peripheral Reset Register
	    volatile uint32_t AHB2RSTR;       // 0x14 : AHB2 Peripheral Reset Register
	    volatile uint32_t AHB3RSTR;       // 0x18 : AHB3 Peripheral Reset Register
	    uint32_t RESERVED0;               // 0x1C : Reserved

	    volatile uint32_t APB1RSTR;       // 0x20 : APB1 Peripheral Reset Register
	    volatile uint32_t APB2RSTR;       // 0x24 : APB2 Peripheral Reset Register
	    uint32_t RESERVED1[2];            // 0x28 - 0x2C : Reserved

	    volatile uint32_t AHB1ENR;        // 0x30 : AHB1 Peripheral Clock Enable Register
	    volatile uint32_t AHB2ENR;        // 0x34 : AHB2 Peripheral Clock Enable Register
	    volatile uint32_t AHB3ENR;        // 0x38 : AHB3 Peripheral Clock Enable Register
	    uint32_t RESERVED2;               // 0x3C : Reserved

	    volatile uint32_t APB1ENR;        // 0x40 : APB1 Peripheral Clock Enable Register
	    volatile uint32_t APB2ENR;        // 0x44 : APB2 Peripheral Clock Enable Register
	    uint32_t RESERVED3[2];            // 0x48 - 0x4C : Reserved

	    volatile uint32_t AHB1LPENR;      // 0x50 : AHB1 Low Power Clock Enable Register
	    volatile uint32_t AHB2LPENR;      // 0x54 : AHB2 Low Power Clock Enable Register
	    volatile uint32_t AHB3LPENR;      // 0x58 : AHB3 Low Power Clock Enable Register
	    uint32_t RESERVED4;               // 0x5C : Reserved

	    volatile uint32_t APB1LPENR;      // 0x60 : APB1 Low Power Clock Enable Register
	    volatile uint32_t APB2LPENR;      // 0x64 : APB2 Low Power Clock Enable Register
	    uint32_t RESERVED5[2];            // 0x68 - 0x6C : Reserved

	    volatile uint32_t BDCR;           // 0x70 : Backup Domain Control Register
	    volatile uint32_t CSR;            // 0x74 : Clock Control & Status Register
	    uint32_t RESERVED6[2];            // 0x78 - 0x7C : Reserved

	    volatile uint32_t SSCGR;          // 0x80 : Spread Spectrum Clock Generation Register
	    volatile uint32_t PLLI2SCFGR;     // 0x84 : PLLI2S Configuration Register
	    volatile uint32_t PLLSAICFGR;     // 0x88 : PLLSAI Configuration Register
	    volatile uint32_t DCKCFGR;        // 0x8C : Dedicated Clock Configuration Register

	    volatile uint32_t CKGATENR;       // 0x90 : Clocks Gated Enable Register
	    volatile uint32_t DCKCFGR2;       // 0x94 : Dedicated Clock Configuration Register 2

	} RCC_RegDef_t;




/* Peripheral definations (peripheral base address typecasted to xxx_RegDef_t)
 *
 */

#define GPIOA ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF ((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG ((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH ((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define RCC   ((RCC_RegDef_t*)RCC_BASEADDR)


#define EXTI  ((EXTI_RegDef_t*)EXTI_BASEADDR)

#define SYSCFG  ((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

/* Clock Enable Macros for GPIOx Peripherals
 *
 */
#define GPIOA_PCLK_EN()     ( RCC->AHB1ENR|=( 1 << 0 ) )
#define GPIOB_PCLK_EN()     ( RCC->AHB1ENR|=( 1 << 1 ) )
#define GPIOC_PCLK_EN()     ( RCC->AHB1ENR|=( 1 << 2 ) )
#define GPIOD_PCLK_EN()     ( RCC->AHB1ENR|=( 1 << 3 ) )
#define GPIOE_PCLK_EN()     ( RCC->AHB1ENR|=( 1 << 4 ) )
#define GPIOF_PCLK_EN()     ( RCC->AHB1ENR|=( 1 << 5 ) )
#define GPIOG_PCLK_EN()     ( RCC->AHB1ENR|=( 1 << 6 ) )
#define GPIOH_PCLK_EN()     ( RCC->AHB1ENR|=( 1 << 7 ) )



/* Clock Enable Macros for I2Cx Peripherals
 *
 */
#define I2C1_PCLK_EN()      (RCC->APB1ENR|= (1 << 21 ) )
#define I2C2_PCLK_EN()      (RCC->APB1ENR|= (1 << 22 ) )
#define I2C3_PCLK_EN()      (RCC->APB1ENR|= (1 << 23 ) )


/* Clock Enable Macros for SPIx Peripherals
 *
 */
#define SPI1_PCLK_EN()      (RCC->APB2ENR|= (1 << 12 ) )
#define SPI2_PCLK_EN()      (RCC->APB1ENR|= (1 << 14 ) )
#define SPI3_PCLK_EN()      (RCC->APB1ENR|= (1 << 15 ) )


/* Clock Enable Macros for USARTx Peripherals
 *
 */
#define USART1_PCLK_EN()    (RCC->APB2ENR |= (1 << 4 ) )
#define USART2_PCLK_EN()    (RCC->APB1ENR |= (1 << 17 ) )
#define USART3_PCLK_EN()    (RCC->APB1ENR |= (1 << 18 ) )
#define USART4_PCLK_EN()    (RCC->APB1ENR |= (1 << 19 ) )
#define USART5_PCLK_EN()    (RCC->APB1ENR |= (1 << 20 ) )
#define USART6_PCLK_EN()    (RCC->APB2ENR |= (1 << 5 ) )




/* Clock Enable Macros for SYSCFG Peripherals
 *
 */
#define SYSCFG_PCLK_EN()    (RCC->APB2ENR |= (1 << 14 ) )


/* Clock Disable Macros for GPIOx Peripherals
 *
 */
#define GPIOA_PCLK_DI()     ( RCC->AHB1ENR &= ~( 1 << 0 ) )
#define GPIOB_PCLK_DI()     ( RCC->AHB1ENR &= ~( 1 << 1 ) )
#define GPIOC_PCLK_DI()     ( RCC->AHB1ENR &= ~( 1 << 2 ) )
#define GPIOD_PCLK_DI()     ( RCC->AHB1ENR &= ~( 1 << 3 ) )
#define GPIOE_PCLK_DI()     ( RCC->AHB1ENR &= ~( 1 << 4 ) )
#define GPIOF_PCLK_DI()     ( RCC->AHB1ENR &= ~( 1 << 5 ) )
#define GPIOG_PCLK_DI()     ( RCC->AHB1ENR &= ~( 1 << 6 ) )
#define GPIOH_PCLK_DI()     ( RCC->AHB1ENR &= ~( 1 << 7 ) )


/* Clock Disable Macros for I2Cx Peripherals
 *
 */
#define I2C1_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 21 ) )
#define I2C2_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 22 ) )
#define I2C3_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 23 ) )


/* Clock Disable Macros for SPIx Peripherals
 *
 */

#define SPI1_PCLK_DI()      (RCC->APB2ENR &= ~(1 << 12 ) )
#define SPI2_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 14 ) )
#define SPI3_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 15 ) )

/* Clock Disable Macros for USARTx Peripherals
 *
 */

#define USART1_PCLK_DI()    (RCC->APB2ENR &= ~(1 << 4 ) )
#define USART2_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 17 ) )
#define USART3_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 18 ) )
#define USART4_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 19 ) )
#define USART5_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 20 ) )
#define USART6_PCLK_DI()    (RCC->APB2ENR &= ~(1 << 5 ) )


/* Clock Disable Macros for SYSCFG Peripherals
 *
 */
#define SYSCFG_PCLK_DI()    (RCC->APB2ENR &= ~(1 << 14 ) )

/*
 * Macoros to reset GPIOx peripherals
 */
#define GPIOA_REG_RESET()        do{ (RCC->AHB1RSTR |= (1 << 0 )) ; (RCC->AHB1RSTR &= ~(1 << 0 )); }while(0)
#define GPIOB_REG_RESET()         do{ (RCC->AHB1RSTR |= (1 << 1 )) ; (RCC->AHB1RSTR &= ~(1 << 1 )); }while(0)
#define GPIOC_REG_RESET()         do{ (RCC->AHB1RSTR |= (1 << 2 )) ; (RCC->AHB1RSTR &= ~(1 << 2 )); }while(0)
#define GPIOD_REG_RESET()         do{ (RCC->AHB1RSTR |= (1 << 3 )) ; (RCC->AHB1RSTR &= ~(1 << 3 )); }while(0)
#define GPIOE_REG_RESET()         do{ (RCC->AHB1RSTR |= (1 << 4 )) ; (RCC->AHB1RSTR &= ~(1 << 4 )); }while(0)
#define GPIOF_REG_RESET()         do{ (RCC->AHB1RSTR |= (1 << 5 )) ; (RCC->AHB1RSTR &= ~(1 << 5 )); }while(0)
#define GPIOG_REG_RESET()         do{ (RCC->AHB1RSTR |= (1 << 6 )) ; (RCC->AHB1RSTR &= ~(1 << 6 )); }while(0)
#define GPIOH_REG_RESET()        do{ (RCC->AHB1RSTR |= (1 << 7 )) ; (RCC->AHB1RSTR &= ~(1 << 7 )); }while(0)

	// returns port code or given GPIOx base address
#define GPIO_BASEADDR_TO_CODE(x)    (  ( x == GPIOA)?0:\
	                                   ( x == GPIOB)?1:\
	                                   ( x == GPIOC)?2:\
	                        		   ( x == GPIOD)?3:\
	                                   ( x == GPIOE)?4:\
	                                   ( x == GPIOF)?5:\
	                                   ( x == GPIOG)?6:\
	                                   ( x == GPIOH)?7:0 )
/*
 * Some generic Macros
 */

#define ENABLE               1
#define DISABLE              0
#define SET                 ENABLE
#define RESET               DISABLE
#define GPIO_PIN_SET        SET
#define GPIO_PIN_RESET      RESET



#endif /* DRIVERS_INC_STM32F4XX_H_ */
