
/**
 ******************************************************************************
 * @Channel Link    :  https://www.youtube.com/user/wardzx1
 * @file    		:  rybg211.h
 * @author  		:  Ward Almasarani - Useful Electronics
 * @version 		:  v.1.0
 * @date    		:  Nov 2, 2022
 * @brief   		:
 *
 ******************************************************************************/

#ifndef RYBG211_H_
#define RYBG211_H_


/* INCLUDES ------------------------------------------------------------------*/
#include "stdlib.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
/* MACROS --------------------------------------------------------------------*/
#define BLE_MODULE_BUFFER_SIZE		256

#define BLE_MODULE_RESET_PIN			GPIO_PIN_14
#define BLE_MODULE_RESET_GPIO_PORT		GPIOB

//AT command set

#define BLE_NAME_SET					"AT+NAME="
#define BLE_DATA_SEND	 				"AT+SEND="
#define BLE_POWER_SET					"AT+CRFOP="

#define BLE_CMD_TERM					"\r\n"
#define BLE_NEW_FIELD					","

/* ENUMORATIONS --------------------------------------------------------------*/

/* STRUCTURES & TYPEDEFS -----------------------------------------------------*/
typedef union
{	uint8_t all;
	struct
	{
		uint8_t packetReceived		:1,
				packetToTransmit	:1,
				reserved			:6;

	}flag;

}controlFlags_t;

typedef struct
{
	controlFlags_t	controlFlags;
	uint16_t 		txPacketSize;
	uint16_t 		rxPacketSize;
	uint32_t 		httpTimer;
	uint32_t 		txTimer;
	uint32_t 		rxTimer;
	char 			txBuffer[BLE_MODULE_BUFFER_SIZE];
	char 			rxBuffer[BLE_MODULE_BUFFER_SIZE];
}hBleModule_t;
/* VARIABLES -----------------------------------------------------------------*/
extern hBleModule_t hBleModule;
/* FUNCTIONS DECLARATION -----------------------------------------------------*/
void rybg211_bleModuleInit(void);
void rybg211_setDeviceName(uint8_t* moduleBuffer, char* nameString);


#endif /* RYBG211_H_ */

/**************************  Useful Electronics  ****************END OF FILE***/
