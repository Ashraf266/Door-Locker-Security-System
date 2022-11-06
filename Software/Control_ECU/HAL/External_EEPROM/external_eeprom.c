 /******************************************************************************
 *
 * Module: External_EEPROM
 *
 * File Name: external_eeprom.c
 *
 * Description: Source file for the External_EEPROM Driver
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/
#include "external_eeprom.h"

#include "i2c.h"

/*******************************************************************************
 *                      Functions Definition                                   *
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
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data)
{
	uint8 eepromAddress = 0b10100000 | (uint8)((u16addr & 0x0700) >> 7);
	I2C_start();
	if(I2C_getStatus() != I2C_START)
		return ERROR;
	I2C_writeByte(eepromAddress & 0xFE);
	if(I2C_getStatus() != I2C_MT_SLA_W_ACK)
		return ERROR;
	I2C_writeByte((uint8)(u16addr));
	if(I2C_getStatus() != I2C_MT_DATA_ACK)
		return ERROR;
	I2C_writeByte(u8data);
	if(I2C_getStatus() != I2C_MT_DATA_ACK)
		return ERROR;
	I2C_stop();

	return SUCCESS;
}




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
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data)
{
	uint8 eepromAddress = 0b10100000 | (uint8)((u16addr & 0x0700) >> 7);
	I2C_start();
	if(I2C_getStatus() != I2C_START)
		return ERROR;
	I2C_writeByte(eepromAddress & 0xFE);
	if(I2C_getStatus() != I2C_MT_SLA_W_ACK)
		return ERROR;
	I2C_writeByte((uint8)(u16addr));
	if(I2C_getStatus() != I2C_MT_DATA_ACK)
		return ERROR;
	I2C_start();
	if(I2C_getStatus() != I2C_REP_START)
		return ERROR;
	I2C_writeByte(eepromAddress | 0x01);
	if(I2C_getStatus() != I2C_MT_SLA_R_ACK)
		return ERROR;
	*u8data = I2C_readByteWithNACK();
	if(I2C_getStatus() != I2C_MR_DATA_NACK)
		return ERROR;
	I2C_stop();


	return SUCCESS;
}
