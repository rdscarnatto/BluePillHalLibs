/*
 * msp.c
 *
 *  Created on: Jan 11, 2023
 *      Author: ARRSC
 */
#include "stm32f1xx_hal.h"


/**
  * @brief  Initialize the MSP.
  * @retval None
  */
void HAL_MspInit(void)
{
	//Here will do low level processor specific inits
		// 1. Set up the priority grouping specific inits
		HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4); // This is the default

		// 2. Enable the requires system exceptions of the arm cortex mx processor
		SCB->SHCSR |= 0x7 << 16; // USGFAULT | BUSFAULT | MEMFAULT exceptions

		// 3. Configure the priority for the system exceptions
		HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
		HAL_NVIC_SetPriority(BusFault_IRQn, 1, 0);
		HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef gpio_uart = {0};
	// Here we are going todo the low lavel inits. of USART2 peripheral
	//1. Enable the clock for the UART2 peripheral
	__HAL_RCC_USART2_CLK_ENABLE();

	//2. Do the pin muxing configurations
	__HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
   	gpio_uart.Pin = GPIO_PIN_2 | GPIO_PIN_3;
	gpio_uart.Mode = GPIO_MODE_AF_PP;
	gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
	gpio_uart.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &gpio_uart);

	//3. Enable IRQ and set up the priority (NVIC settings)
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn,15,0);

}