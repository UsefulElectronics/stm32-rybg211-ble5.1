
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
#include "stdbool.h"
#include "ctype.h"
/* PRIVATE STRUCTRES ---------------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/
hBleModule_t hBleModule;
/* DEFINITIONS ---------------------------------------------------------------*/

/* MACROS --------------------------------------------------------------------*/
#define ONE_DIGITLIMIT			9
#define TWO_DIGITLIMIT			99
#define THREE_DIGITLIMIT		999
#define FOUR_DIGITLIMIT			9999

#define ONE_DIGIT				0
#define TWO_DIGIT				1
#define THREE_DIGIT				2
#define ASCII_STARTING_VALUE			'0'

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

uint8_t rybg211_rxPacketParser(char* moduleBuffer, uint8_t packetSize)
{
	uint8_t packetToRead = false;

	if(0 == memcmp(moduleBuffer, BLE_DATA_RX, BLE_PARSER_CHAR_COUNT))
	{
		//Activation to read the data part of the received packet.
		packetToRead = true;
	}
	else if(0 == memcmp(moduleBuffer, BLE_NEW_CONNECTION,BLE_PARSER_CHAR_COUNT))
	{
		hBleModule.ConnectedDevice = moduleBuffer[6];
		//Clear the UART DMA RX buffer
		memset(moduleBuffer, 0, BLE_MODULE_BUFFER_SIZE);
	}
	else if(0 == memcmp(moduleBuffer, BLE_NEW_DISCONNECTION, BLE_PARSER_CHAR_COUNT))
	{
		hBleModule.ConnectedDevice = 0;
		//Clear the UART DMA RX buffer
		memset(moduleBuffer, 0, BLE_MODULE_BUFFER_SIZE);
	}

	return packetToRead;
}

/**
 * @brief 	The passed string head must start with a numeric character and this function will
 * 			convert the digits in the sting into an integer value and store it in targetValue
 * 			Note that this function will keep String without any change.
 *			Currently only 3 digit conversion is supported by this function.
 *
 * @param 	targetValue : After ASCII to Integer conversion the integer value will be stored here.
 *
 * @param 	String		: String of numeric characters to be converted to one single integer and
 * 						  stored in targetValue. the value stored in String won't be changed.
 *
 * @return	This function will return the number of found digits in the passed String.
 */
uint8_t asciiToValue(uint32_t* targetValue, uint8_t* String)
{
	uint8_t 	digitCount  = 0;
	uint32_t 	tempValue 	= 0;
	uint16_t 	tens 		= 0;
	//Count the number of digits in the string
	while(isdigit(String[digitCount]))
	{
		++digitCount;
	}
	//This check is done to prevent this function from execution if non alphanumeric string is passed to this function.
	if(0 != digitCount)
	{
		//Operation fix
		digitCount -= 1;
		//determines the multiplications of tens
		tens = digitCount == ONE_DIGIT   ? 1   : tens;
		tens = digitCount == TWO_DIGIT   ? 10  : tens;
		tens = digitCount == THREE_DIGIT ? 100 : tens;
		//Start calculating the integer value out of the passed digits
		for(int8_t i = 0; i <= digitCount; ++i)
		{
			tempValue = tempValue + ((String[i] - ASCII_STARTING_VALUE) * tens);
			tens = tens / 10;
		}
		//Pass the obtained integer value to targetValue that will be returned
		*targetValue = tempValue;
		//digitCount will carry the number of found digits in the String
		++digitCount;
	}
	return digitCount;
}

/**
 * @brief	the passed value will be converted to numeric characters and stored in targetString
 *			right after determining the number of digits that the passed value has. This function supports
 *			5 digits number conversion
 *
 * @param 	value			: the integer to be converted to numeric characters.
 *
 * @param 	targetString	: this is where the converted numeric characters will be stored.
 *
 * @return	This function will return the number of found digits in the passed value.
 */
uint8_t valueToAscii(uint32_t value, uint8_t* targetString)
{
	uint8_t digitPosition = 0;
	//=====> Made up rule:
	//value/(digit to obtain) %10 (%10 is to get rid of upper tens)
	if(value > FOUR_DIGITLIMIT)
	{
		targetString[digitPosition] = (value / 10000) 		+ ASCII_STARTING_VALUE;
		++digitPosition;
		targetString[digitPosition] = (value / 1000) % 10	+ ASCII_STARTING_VALUE;
		++digitPosition;
		targetString[digitPosition] = (value / 100) % 10 	+ ASCII_STARTING_VALUE;
		++digitPosition;
		targetString[digitPosition] = (value / 10) % 10 	+ ASCII_STARTING_VALUE;
		++digitPosition;
		targetString[digitPosition] = (value % 10)  		+ ASCII_STARTING_VALUE;
		++digitPosition;
	}
	else
	{
		if(value > THREE_DIGITLIMIT)
		{
			//The passed value is 4 digit value
			targetString[digitPosition] = (value / 1000) 		+ ASCII_STARTING_VALUE;
			++digitPosition;
			targetString[digitPosition] = (value / 100) % 10 	+ ASCII_STARTING_VALUE;
			++digitPosition;
			targetString[digitPosition] = (value / 10) % 10 	+ ASCII_STARTING_VALUE;
			++digitPosition;
			targetString[digitPosition] = (value % 10)  		+ ASCII_STARTING_VALUE;
			++digitPosition;
		}
		else
		{
			if(value > TWO_DIGITLIMIT)
			{
				//The passed value is 3 digit value
				targetString[digitPosition] = (value / 100) 	+ ASCII_STARTING_VALUE;
				++digitPosition;
				targetString[digitPosition] = (value / 10) % 10 + ASCII_STARTING_VALUE;
				++digitPosition;
				targetString[digitPosition] = (value % 10)  	+ ASCII_STARTING_VALUE;
				++digitPosition;
			}
			else
			{
				if(value > ONE_DIGITLIMIT)
				{
					//The passed value is 2 digit value
					targetString[digitPosition] = (value / 10) 	+ ASCII_STARTING_VALUE;
					++digitPosition;
					targetString[digitPosition] = (value % 10) 	+ ASCII_STARTING_VALUE;
					++digitPosition;
				}
				else
				{
					//The passed value is 1 digit value
					targetString[digitPosition] = value + ASCII_STARTING_VALUE;
					++digitPosition;
				}
			}
		}
	}


	//digitPosition will carry the number of found digits in the passed value integer.
	return digitPosition;
}


/**
 * @brief
 *
 * @param moduleBuffer
 * @param targertBuffer
 * @return
 */
uint32_t rybg211_rxDataRead(char* moduleBuffer, char* targertBuffer)
{
	//+1 is used to ignore the ',' from the received packet and jump directly to the data field.
	uint8_t dataPositionOffset = BLE_RX_SIZE_BYTE_POSITION + 1;

	uint32_t length = 0;
	//Convert the size from ASCII to integer format and obtain the number of digits to adjust the correct data positio.
	dataPositionOffset += asciiToValue(&length, (uint8_t*)moduleBuffer + BLE_RX_SIZE_BYTE_POSITION);

	memcpy(targertBuffer, moduleBuffer + dataPositionOffset, length);

	return length;
}
/**************************  Useful Electronics  ****************END OF FILE***/
