/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define COMMON_BUFFER_SIZE		256
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
typedef union
{	uint8_t all;
	struct
	{
		uint8_t bleToUsb		:1,
				usbToBle		:1,
				reserved		:6;

	}flag;

}flags_t;

typedef struct
{
	flags_t			controlFlags;
	uint16_t 		blePacketSize;
	uint16_t 		usbPacketSize;
	uint32_t 		timer;
	char 			bleBuffer[COMMON_BUFFER_SIZE];
	char 			usbBuffer[COMMON_BUFFER_SIZE];
}hCommonBuffer_t;
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MODULE_RESET_Pin GPIO_PIN_14
#define MODULE_RESET_GPIO_Port GPIOB
#define LED1_Pin GPIO_PIN_5
#define LED1_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_6
#define LED2_GPIO_Port GPIOB
#define LED3_Pin GPIO_PIN_7
#define LED3_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
