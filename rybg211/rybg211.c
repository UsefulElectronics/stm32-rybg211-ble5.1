
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

void rybg211_setDeviceName(uint8_t* moduleBuffer, char* nameString)
{
	uint8_t nameStringSize = strlen(nameString);

	memcpy(moduleBuffer ,BLE_NAME_SET, nameStringSize);



	strcat((char*) moduleBuffer ,BLE_NEW_FIELD);
}

/**************************  Useful Electronics  ****************END OF FILE***/
