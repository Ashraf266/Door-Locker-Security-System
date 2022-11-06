 /******************************************************************************
 *
 * Module: External_EEPROM
 *
 * File Name: external_eeprom.h
 *
 * Description: Header file for the External_EEPROM Driver
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/
#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/*------------------------------------------------------------------
[Function Name]:  EEPROM_writeByte
[Description]: write a byte to the EEPROM
[Args]:
[in]	uint16 u16addr:
					Contains the address you want to write your data in
		uint8 u8data:
					The data you want to write in the EEPROM
[out]	-NONE
[in/out] -NONE
[Returns]: whether the data is successfully written or not
------------------------------------------------------------------*/
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);




/*------------------------------------------------------------------
[Function Name]:  EEPROM_writeByte
[Description]: write a byte to the EEPROM
[Args]:
[in]	uint16 u16addr:
					Contains the address you want to read from
		uint8 *u8data:
					pointer to the variable you want to write the data in
[out]	-NONE
[in/out] -NONE
[Returns]: whether the data is successfully read or not
------------------------------------------------------------------*/
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);

#endif /* EXTERNAL_EEPROM_H_ */
