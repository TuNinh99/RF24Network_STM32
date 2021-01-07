/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "string.h"
#include "stdio.h"
#include "stdbool.h" 
#include "NRF24.h"
#include "lcd16x2.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define CSN_Pin GPIO_PIN_1
#define CSN_GPIO_Port GPIOA
#define CE_Pin GPIO_PIN_4
#define CE_GPIO_Port GPIOA
#define rs_lcd_Pin GPIO_PIN_12
#define rs_lcd_GPIO_Port GPIOB
#define rw_lcd_Pin GPIO_PIN_13
#define rw_lcd_GPIO_Port GPIOB
#define en_lcd_Pin GPIO_PIN_14
#define en_lcd_GPIO_Port GPIOB
#define d4_lcd_Pin GPIO_PIN_8
#define d4_lcd_GPIO_Port GPIOA
#define d5_lcd_Pin GPIO_PIN_9
#define d5_lcd_GPIO_Port GPIOA
#define d6_lcd_Pin GPIO_PIN_10
#define d6_lcd_GPIO_Port GPIOA
#define d7_lcd_Pin GPIO_PIN_11
#define d7_lcd_GPIO_Port GPIOA

#define high 0u
#define low 1u

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
