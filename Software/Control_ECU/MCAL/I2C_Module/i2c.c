 /******************************************************************************
 *
 * Module: I2C
 *
 * File Name: i2c.c
 *
 * Description: Source file for the ATmega32 I2C Driver
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/
#include "i2c.h"
#include "common_macros.h"
#include <avr/io.h>


/*******************************************************************************
 *                      Functions Definition                                   *
 *******************************************************************************/

/*------------------------------------------------------------------
[Function Name]:  I2C_init
[Description]: initialize I2C (TWI) Interface
[Args]:
[in]	I2C_ConfigType * config :
							pointer i2c configuration structure
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void I2C_init(I2C_ConfigType * config)
{
	/* Enable I2C */
	TWCR = (1<<TWEN);
	/* Setup Two Wire Bus address my address if any master device want to call me */
	TWAR =  config->address<<1;
	/* Setup Bit Rate .... F_CPU must be 8MHz or 16 MHz*/
	switch(config->speed)
	{
	case STANDARD_MODE:
		TWSR = 0x00;
		TWBR = 0x20;
		if(F_CPU == 16000000UL)
			TWBR = 0x48;
		break;
	case FAST_MODE:
		TWSR = 0x00;
		TWBR = 0x02;
		if(F_CPU == 16000000UL)
				TWBR = 0x0C;
		break;
	case FAST_MODE_PLUS:
		/* can't be done in 8 MHz CPU clock frequency */
		if(F_CPU == 16000000UL)
		{
			TWSR = 0x00;
			TWBR = 0x00;
		}
		break;
	case HIGHSPEED_MODE:
		/* can't be done in 8 MHz or 16 MHz CPU clock frequency */
		break;
	}
}





/*------------------------------------------------------------------
[Function Name]:  I2C_start
[Description]: send the Start bit
[Args]:
[in]	-NONE
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void I2C_start(void)
{
	/*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA);

	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}





/*------------------------------------------------------------------
[Function Name]:  I2C_stop
[Description]: send the Stop bit
[Args]:
[in]	-NONE
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void I2C_stop(void)
{
	/*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}





/*------------------------------------------------------------------
[Function Name]:  I2C_writeByte
[Description]: send the start bit
[Args]:
[in]	uint8 data:
					contains the data you want to send through the I2C
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void I2C_writeByte(uint8 data)
{
    /* Put data On TWI data Register */
	TWDR = data;

	/*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1<<TWINT) | (1<<TWEN);
    /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}





/*------------------------------------------------------------------
[Function Name]:  I2C_readByteWithACK
[Description]: reads the byte received with ACK bit send to Continue receiving
[Args]:
[in]	-NONE
[out]	-NONE
[in/out] -NONE
[Returns]: the data read
------------------------------------------------------------------*/
uint8 I2C_readByteWithACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);

	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));

	/* Read Data */
	return TWDR;
}





/*------------------------------------------------------------------
[Function Name]:  I2C_readByteWithNACK
[Description]: reads the byte received with NACK bit send to Stop receiving
[Args]:
[in]	-NONE
[out]	-NONE
[in/out] -NONE
[Returns]: the data read
------------------------------------------------------------------*/
uint8 I2C_readByteWithNACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1<<TWINT) | (1<<TWEN);

    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));

	/* Read Data */
	return TWDR;
}





/*------------------------------------------------------------------
[Function Name]:  I2C_getStatus
[Description]: send the start bit
[Args]:
[in]	-NONE
[out]	-NONE
[in/out] -NONE
[Returns]: the I2C(TWI) interface Status
------------------------------------------------------------------*/
uint8 I2C_getStatus(void)
{
	/* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	return (TWSR & 0xF8);
}
