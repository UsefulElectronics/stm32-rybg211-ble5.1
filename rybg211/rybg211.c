
/**
 ******************************************************************************
 * @Channel Link    :  https://www.youtube.com/user/wardzx1
 * @file    		:  rybg211.c
 * @author  		:  Ward Almasarani - Useful Electronics
 * @version 		:  v.1.0
 * @date    		:  Nov 2, 2022
 * @brief   		:
 *
 ******************************************************************************/


/* INCLUDES ------------------------------------------------------------------*/
#include "rybg211.h"
#include "stm32f4xx_hal.h"
#include "string.h"
/* PRIVATE STRUCTRES ---------------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/
hBleModule_t hBleModule;
/* DEFINITIONS ---------------------------------------------------------------*/

/* MACROS --------------------------------------------------------------------*/

/* PRIVATE FUNCTIONS DECLARATION ---------------------------------------------*/

/* FUNCTION PROTOTYPES -------------------------------------------------------*/
void rybg211_bleModuleInit(void)
{
	memset(&hBleModule, 0, sizeof(hBleModule_t));

	HAL_GPIO_WritePin(BLE_MODULE_RESET_GPIO_PORT, BLE_MODULE_RESET_PIN, ENABLE);
}

void rybg211_setDeviceName(char* moduleBuffer, char* nameString)
{
	uint8_t nameStringSize = strlen(nameString);

	memcpy(moduleBuffer ,BLE_NAME_SET, sizeof(BLE_NAME_SET));

	sprintf((char*)moduleBuffer, "%s%d%s%s%s",BLE_NAME_SET,
										nameStringSize,
										BLE_NEW_FIELD,
										nameString,
										BLE_CMD_TERM);


	hBleModule.txPacketSize = strlen((char*)moduleBuffer);

	hBleModule.controlFlags.flag.packetToTransmit = ENABLE;
}

void rybg211_rxPacketParser(char* moduleBuffer, uint8_t packetSize)
{

	char tempBuffer[BLE_MODULE_BUFFER_SIZE] = {0};

	if(0 == memcmp(moduleBuffer, BLE_DATA_RX, BLE_PARSER_CHAR_COUNT))
	{
		memcpy(tempBuffer, moduleBuffer, packetSize);

	}
	else if(0 == memcmp(moduleBuffer, BLE_NEW_CONNECTION,BLE_PARSER_CHAR_COUNT))
	{
		hBleModule.ConnectedDevice = moduleBuffer[6];
	}
	else if(0 == memcmp(moduleBuffer, BLE_NEW_DISCONNECTION, BLE_PARSER_CHAR_COUNT))
	{
		hBleModule.ConnectedDevice = 0;
	}
	//Clear the UART DMA RX buffer
	memset(moduleBuffer, 0, BLE_MODULE_BUFFER_SIZE);
}


/**************************  Useful Electronics  ****************END OF FILE***/
