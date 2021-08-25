/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32l4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ADS131A0x.h"
#include "st7735.h"
#include "fonts.h"
#include "math.h"

#include "MQTT.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

extern void UART_IRQHandler ();


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi);



extern void TimingDelay_Decrement(void);
//extern void prvvTIMERExpiredISR( void );
//extern void prvvUARTTxReadyISR(void);
//extern void prvvUARTRxISR(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi3;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim15;
extern UART_HandleTypeDef huart1;
/* USER CODE BEGIN EV */

extern char outputParam[5];
extern float temperature;
extern char test[15];


/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32L4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32l4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */

  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
  * @brief This function handles TIM1 break interrupt and TIM15 global interrupt.
  */
void TIM1_BRK_TIM15_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_BRK_TIM15_IRQn 0 */

  /* USER CODE END TIM1_BRK_TIM15_IRQn 0 */
  HAL_TIM_IRQHandler(&htim15);
  /* USER CODE BEGIN TIM1_BRK_TIM15_IRQn 1 */

  /* USER CODE END TIM1_BRK_TIM15_IRQn 1 */
}

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */

  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */

  /* USER CODE END TIM3_IRQn 1 */
}

/**
  * @brief This function handles SPI1 global interrupt.
  */
void SPI1_IRQHandler(void)
{
  /* USER CODE BEGIN SPI1_IRQn 0 */

  /* USER CODE END SPI1_IRQn 0 */
  HAL_SPI_IRQHandler(&hspi1);
  /* USER CODE BEGIN SPI1_IRQn 1 */

  /* USER CODE END SPI1_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */
	UART_IRQHandler();
  /* USER CODE END USART1_IRQn 0 */
  //HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles SPI3 global interrupt.
  */
void SPI3_IRQHandler(void)
{
  /* USER CODE BEGIN SPI3_IRQn 0 */

  /* USER CODE END SPI3_IRQn 0 */
  HAL_SPI_IRQHandler(&hspi3);
  /* USER CODE BEGIN SPI3_IRQn 1 */

  /* USER CODE END SPI3_IRQn 1 */
}

/**
  * @brief This function handles TIM6 global interrupt, DAC channel1 underrun error interrupt.
  */
void TIM6_DAC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_DAC_IRQn 0 */

  /* USER CODE END TIM6_DAC_IRQn 0 */
  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_DAC_IRQn 1 */

  /* USER CODE END TIM6_DAC_IRQn 1 */
}

/* USER CODE BEGIN 1 */
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) {
	if(hspi -> Instance == ADS131A0x_SPI_PORT.Instance){
		// Nothing to do here
	}
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin == ADS131A0x_DRDY_Pin) {
		ADS131A0x_Ready_flag = 1;

		ADS131A0xSetCS(0);
		HAL_SPI_TransmitReceive(&ADS131A0x_SPI_PORT, emptyTxBuffer, ADS131A0x_DataBuf, ADS131A0x_WORD_SIZE*5, 1);
		ADS131A0xSetCS(1);

		ADS131A0xGetChannels();


	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim6)
	{

		NVIC_DisableIRQ(EXTI9_5_IRQn);
		  if (fabs(measf.Ch4) > 1.0) {
				sprintf(test, "%.2f", measf.Ch4);
				ST7735_WriteString(135, 0 + 5, " V", Font_11x18, ST7735_WHITE,
						ST7735_BLUE);
			} else if (fabs(measf.Ch4) <= 1.0) {
				sprintf(test, "%.2f", measf.Ch4 * 1000.0);
				ST7735_WriteString(135, 0 + 5, "mV", Font_11x18, ST7735_WHITE,
						ST7735_BLUE);
			}


			ST7735_WriteString(35, 0 + 5, test, Font_11x18, ST7735_WHITE,
					ST7735_BLUE);

			  if (fabs(measf.Ch3) > 1.0) {
					sprintf(test, "%.2f", measf.Ch3);
					ST7735_WriteString(135, 25 + 5, " A", Font_11x18, ST7735_WHITE,
							ST7735_BLUE);
				} else if (fabs(measf.Ch3) <= 1.0) {
					sprintf(test, "%.2f", measf.Ch3 * 1000.0);
					ST7735_WriteString(135, 25 + 5, "mA", Font_11x18, ST7735_WHITE,
							ST7735_BLUE);
				}


			ST7735_WriteString(35, 25 + 5, test, Font_11x18, ST7735_WHITE, ST7735_BLUE);



			  if (fabs(measf.Ch2) > 1.0) {
					sprintf(test, "%.2f  ", measf.Ch2);
					ST7735_WriteString(135, 50 + 5, " V", Font_11x18, ST7735_WHITE,
							ST7735_BLUE);
				} else if (fabs(measf.Ch2) <= 1.0) {
					sprintf(test, "%.2f", measf.Ch2 * 1000.0);
					ST7735_WriteString(135, 50 + 5, "mV", Font_11x18, ST7735_WHITE,
							ST7735_BLUE);
				}



			ST7735_WriteString(35, 50 + 5, test, Font_11x18, ST7735_WHITE, ST7735_BLUE);

			  if (fabs(measf.Ch1) > 1.0) {
					sprintf(test, "%.2f  ", measf.Ch1);
					ST7735_WriteString(135, 75 + 5, " A", Font_11x18, ST7735_WHITE,
							ST7735_BLUE);
				} else if (fabs(measf.Ch1) <= 1.0) {
					sprintf(test, "%.2f", measf.Ch1 * 1000.0);
					ST7735_WriteString(135, 75 + 5, "mA", Font_11x18, ST7735_WHITE,
							ST7735_BLUE);
				}

			ST7735_WriteString(35, 75 + 5, test, Font_11x18, ST7735_WHITE, ST7735_BLUE);

		    sprintf(test, "%.1f*C", temperature);
			ST7735_WriteString(5, 100 + 5, test, Font_11x18, ST7735_WHITE, ST7735_BLUE);


static uint8_t cntrep;
cntrep++;
	if(cntrep > 5)
	{
		cntrep = 0;
		static uint8_t cnt;

		if(cnt == 0)
		{
			ST7735_WriteString(80, 100 + 5, "Ef", Font_11x18, ST7735_WHITE, ST7735_BLUE);
			sprintf(outputParam, "%.2f %",measf.Eff);
			ST7735_WriteString(105, 100 + 5, outputParam, Font_11x18, ST7735_WHITE, ST7735_BLUE);
		}
		else if(cnt == 1)
		{
			ST7735_WriteString(80, 100 + 5, "P1", Font_11x18, ST7735_WHITE, ST7735_BLUE);
			 sprintf(outputParam, "%.2f %",measf.P1);
					ST7735_WriteString(105, 100 + 5, outputParam, Font_11x18, ST7735_WHITE, ST7735_BLUE);

		}
		else if(cnt == 2)
		{
			ST7735_WriteString(80, 100 + 5, "P2", Font_11x18, ST7735_WHITE, ST7735_BLUE);
			 sprintf(outputParam, "%.2f %",measf.P2);
					ST7735_WriteString(105, 100 + 5, outputParam, Font_11x18, ST7735_WHITE, ST7735_BLUE);

		}
		cnt ++ ;
		if(cnt > 2) cnt = 0;

	}

	// Moim zdaniem tu najlepiej dodać obsługę RS-485


	}

	NVIC_EnableIRQ(EXTI9_5_IRQn);


	if(htim == &htim15)

	{
		if (measf.P1 / measf.P2 > 1.0)
		{
			measf.Eff = ( measf.P2 / measf.P1 ) * 100;
		}
		else
		{
			measf.Eff = ( measf.P1 / measf.P2 ) * 100;
		}

		if (fabs(measf.Ch3) >= 0.05)
		{
			measf.Q_CH1 = measf.Q_CH1 + (measf.Ch3 / 36000.0L);
		}

		if (fabs(measf.Ch1) >= 0.05)
		{
			measf.Q_CH2 = measf.Q_CH2 + (measf.Ch1 / 36000.0L);
		}

		if (fabs(measf.P1) >= 1.0)
		{
			measf.EnergyCH1 = measf.EnergyCH1 + (measf.P1 / 36000.0L);
		}
		if (fabs(measf.P2) >= 1.0)
		{
			measf.EnergyCH2 = measf.EnergyCH2 + (measf.P2 / 36000.0L);
		}
	}

	if(htim == &htim3)
	{
		MQTTClient_Publish(&measf, &temperature);
	}
}


//void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
//{
//	if(htim->Instance == TIM1)
//	{
//		prvvTIMERExpiredISR( );
//	}
//}

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	if(huart->Instance == USART3)
//	{
//		prvvUARTRxISR();
//		HAL_UART_Receive_IT(&huart3, usart3_rx_data_buff, 1);
//	}
//}
//
//void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
//{
//
//	if(huart->Instance == USART3)
//	{
//		HAL_GPIO_WritePin(USART3_DIR_GPIO_Port, USART3_DIR_Pin, GPIO_PIN_RESET);
//		prvvUARTTxReadyISR();
//	}
//}


void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
	if(hspi == &hspi1)
	{

	}

	if(hspi == &hspi3)
	{
		NVIC_SystemReset();
	}
}


/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
