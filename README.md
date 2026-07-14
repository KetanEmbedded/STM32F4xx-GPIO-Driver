# 🚀 STM32F4xx GPIO Driver

A register-level GPIO driver developed from scratch for the **STM32F446RE (NUCLEO-F446RE)** development board using **Embedded C**, without using STM32 HAL or LL libraries.

This project is a part of my Embedded Systems learning journey, where I implemented GPIO peripheral drivers by directly accessing STM32 registers as described in the Reference Manual.

---

## 📌 Features

- ✅ GPIO Initialization
- ✅ GPIO De-initialization
- ✅ GPIO Clock Enable/Disable
- ✅ GPIO Input Read
- ✅ GPIO Output Write
- ✅ GPIO Output Toggle
- ✅ Push-Pull Output Mode
- ✅ Open-Drain Output Mode
- ✅ GPIO Interrupt Configuration
- ✅ Interrupt Enable/Disable (NVIC)
- ✅ Interrupt Priority Configuration
- ✅ External Interrupt Handling (EXTI)

---

## 🛠 Hardware Used

- STM32 NUCLEO-F446RE
- STM32F446RE (ARM Cortex-M4)
- User LED (LD2)
- User Push Button (B1)

---

## 💻 Software Used

- STM32CubeIDE
- Embedded C
- ARM GCC Toolchain

---

## 📂 Project Structure

```
STM32F4xx-GPIO-Driver
│
├── drivers/
│   ├── Inc/
│   └── Src/
│
├── Src/
│
├── Startup/
│
├── README.md
```

---

## ⚙️ GPIO Driver APIs

Implemented APIs include:

```c
GPIO_Init()
GPIO_DeInit()
GPIO_ReadFromInputPin()
GPIO_ReadFromInputPort()
GPIO_WriteToOutputPin()
GPIO_WriteToOutputPort()
GPIO_ToggleOutputPin()

GPIO_IRQConfig()
GPIO_IRQPriorityConfig()
GPIO_IRQHandling()
```

---

## 🧪 Tested Applications

The driver has been tested on the STM32 NUCLEO-F446RE board with:

- LED ON/OFF
- LED Toggle
- LED Blinking
- Push-Pull Output Configuration
- Open-Drain Output Configuration
- External Button Interrupt

---

## 🧠 Concepts Covered

- GPIO Registers
- RCC Peripheral Clock Control
- GPIO Modes
- GPIO Speed Configuration
- Pull-up / Pull-down Configuration
- Push-Pull vs Open-Drain
- EXTI (External Interrupt)
- NVIC (Nested Vectored Interrupt Controller)
- Interrupt Priority
- Interrupt Handling
- Register-Level Programming

---

## 🎯 Learning Outcome

Through this project I learned:

- Writing peripheral drivers without HAL
- Register-level programming
- STM32 memory map
- GPIO architecture
- EXTI and NVIC interrupt mechanism
- Embedded driver development methodology

---

## 🚀 Future Improvements

This repository will be expanded by adding:

- SPI Driver
- I2C Driver
- USART Driver
- Timer Driver
- RCC Driver

---

## 👨‍💻 Author

**Ketan Mahesh Joshi**

Electronics & Telecommunication Engineering  
Embedded Systems | Embedded C | STM32 | ARM Cortex-M4

---

⭐ If you found this project useful, consider giving it a star!
