
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

#define BLE_DATA_RX						"+RCV"
#define BLE_NEW_CONNECTION				"+++++C"
#define BLE_NEW_DISCONNECTION			"-----#"

#define BLE_CONNECTION_BYTE_POSITION	6
#define BLE_RX_DATA_BYTE_POSITION		5
#define BLE_RX_SIZE_BYTE_POSITION		7


#define BLE_PARSER_CHAR_COUNT			4

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
	char			ConnectedDevice;
	char 			txBuffer[BLE_MODULE_BUFFER_SIZE];
	char 			rxBuffer[BLE_MODULE_BUFFER_SIZE];
}hBleModule_t;
/* VARIABLES -----------------------------------------------------------------*/
extern hBleModule_t hBleModule;
/* FUNCTIONS DECLARATION -----------------------------------------------------*/
void rybg211_bleModuleInit			(void);
void rybg211_setDeviceName			(char* moduleBuffer, char* nameString);
uint8_t rybg211_rxPacketParser		(char* moduleBuffer, uint8_t packetSize);
uint32_t rybg211_rxDataRead			(char* moduleBuffer, char* targertBuffer);
uint8_t asciiToValue					(uint32_t* targetValue, uint8_t* String);


#endif /* RYBG211_H_ */

/**************************  Useful Electronics  ****************END OF FILE***/
