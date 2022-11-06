 /******************************************************************************
 *
 * Module: I2C
 *
 * File Name: i2c.h
 *
 * Description: Header file for the ATmega32 I2C (TWI) Driver
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/
#ifndef I2C_H_
#define I2C_H_

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define I2C_START         0x08 /* start has been sent */
#define I2C_REP_START     0x10 /* repeated start */
#define I2C_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define I2C_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define I2C_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define I2C_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define I2C_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/*------------------------------------------------------------------
[ENUM Name]: SpeedMode
[ENUM Description]: Contains the speed modes for I2C
					STANDARD_MODE 	= 100 Kb/s
					FAST_MODE     	= 400 kb/s
					FAST_MODE_PLUS	= 1   Mb/s
					HIGHSPEED_MODE  = 3.4 Mb/s
------------------------------------------------------------------*/
typedef enum
{
	STANDARD_MODE,FAST_MODE,FAST_MODE_PLUS,HIGHSPEED_MODE
}SpeedMode;

/*------------------------------------------------------------------
[Structure Name]: I2C_ConfigType
[Structure Description]: it contains I2C configurations
------------------------------------------------------------------*/
typedef struct
{
	SpeedMode speed;
	uint8 address;
}I2C_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
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
void I2C_init(I2C_ConfigType * config);




/*------------------------------------------------------------------
[Function Name]:  I2C_start
[Description]: send the Start bit
[Args]:
[in]	-NONE
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void I2C_start(void);




/*------------------------------------------------------------------
[Function Name]:  I2C_stop
[Description]: send the Stop bit
[Args]:
[in]	-NONE
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void I2C_stop(void);




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
void I2C_writeByte(uint8 data);




/*------------------------------------------------------------------
[Function Name]:  I2C_readByteWithACK
[Description]: reads the byte received with ACK bit send to Continue receiving
[Args]:
[in]	-NONE
[out]	-NONE
[in/out] -NONE
[Returns]: the data read
------------------------------------------------------------------*/
uint8 I2C_readByteWithACK(void);




/*------------------------------------------------------------------
[Function Name]:  I2C_readByteWithNACK
[Description]: reads the byte received with NACK bit send to Stop receiving
[Args]:
[in]	-NONE
[out]	-NONE
[in/out] -NONE
[Returns]: the data read
------------------------------------------------------------------*/
uint8 I2C_readByteWithNACK(void);





/*------------------------------------------------------------------
[Function Name]:  I2C_getStatus
[Description]: send the start bit
[Args]:
[in]	-NONE
[out]	-NONE
[in/out] -NONE
[Returns]: the I2C(TWI) interface Status
------------------------------------------------------------------*/
uint8 I2C_getStatus(void);



#endif /* I2C_H_ */
