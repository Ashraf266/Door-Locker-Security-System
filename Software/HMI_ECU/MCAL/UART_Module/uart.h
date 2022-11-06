 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the ATmega32 UART Driver
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/
#ifndef UART_H_
#define UART_H_


#include "std_types.h"



/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/*------------------------------------------------------------------
[ENUM Name]: UART_Parity
[ENUM Description]: it is used to define parity bit
------------------------------------------------------------------*/
typedef enum
{
	DISABLE_PARITY,EVEN_PARITY=2,ODD_PARITY
}UART_Parity;


/*------------------------------------------------------------------
[ENUM Name]: UART_STOPBIT
[ENUM Description]: it's used to define number of stop bits
------------------------------------------------------------------*/
typedef enum
{
	ONE_STOPBIT,TWO_STOPBITS
}UART_STOPBIT;


/*------------------------------------------------------------------
[ENUM Name]: UART_DATABITS
[ENUM Description]: it's used to define number of bits you want to send per frame
------------------------------------------------------------------*/
typedef enum
{
	FIVE_DATABITS,SIX_DATABITS,SEVEN_DATABITS,EIGHT_DATABITS
}UART_DATABITS;



/*------------------------------------------------------------------
[Structure Name]: UART_ConfigType
[Structure Description]: it's used to define UART configurations like parity,stop bits,data bits & baudrate
------------------------------------------------------------------*/
typedef struct
{
	UART_Parity parity;
	UART_STOPBIT stopbit;
	UART_DATABITS databits;
	uint32 baudrate;

}UART_ConfigType;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*------------------------------------------------------------------
[Function Name]:  UART_init
[Description]: Functional responsible for Initialize the UART device by:
				1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
				2. Enable the UART.
				3. Setup the UART baud rate.
[Args]:
[in]	UART_ConfigType * config:
				a pointer to the configuration structure
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void UART_init(UART_ConfigType * config);





/*------------------------------------------------------------------
[Function Name]:  UART_sendByte
[Description]: responsible for send byte to another UART device.
[Args]:
[in]	uint8 data:
				the byte you want to send through UART
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void UART_sendByte(uint8 data);





/*------------------------------------------------------------------
[Function Name]:  UART_receiveByte
[Description]: responsible for receive byte from another UART device.
[Args]:
[in]	 -NONE
[out]	 -NONE
[in/out] -NONE
[Returns]: the data received through UART
------------------------------------------------------------------*/
uint8 UART_receiveByte(void);





/*------------------------------------------------------------------
[Function Name]:  UART_sendString
[Description]: Send the required string through UART to the other UART device.
[Args]:
[in]	const uint8 * str:
				pointer to the first charater of the string you want to send
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void UART_sendString(const uint8 * str);





/*------------------------------------------------------------------
[Function Name]:  UART_receiveString
[Description]: Receive the required string until the '#' symbol through UART from the other UART device.
[Args]:
[in]	 uint8 * str:
				pointer to the first charater of the string you want to save the received string in
[out]	 -NONE
[in/out] -NONE
[Returns]: the string received through UART
------------------------------------------------------------------*/
void UART_receiveString(uint8 * str);

#endif /* UART_H_ */
