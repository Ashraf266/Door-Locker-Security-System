 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the ATmega32 UART Driver
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/

#include "uart.h"
#include <avr/io.h>
#include "common_macros.h"




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
void UART_init(UART_ConfigType * config)
{
	/* calculate the value of the UBRR register to setup the baud rate */
	uint16 ubrrValue = (uint16)((F_CPU / (8UL * config->baudrate)) - 1);

	/* U2X = 1 for double transmission speed */
	UCSRA = (1<<U2X);

	/************************** UCSRB Description **************************
	* RXCIE = 0 Disable USART RX Complete Interrupt Enable
	* TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	* UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	* RXEN  = 1 Receiver Enable
	* RXEN  = 1 Transmitter Enable
	* UCSZ2 = 0 For 8-bit data mode
	* RXB8 & TXB8 not used for 8-bit data mode
	***********************************************************************/
	UCSRB = (1<<RXEN) | (1<<TXEN);

	/* URSEL   = 1 The URSEL must be one when writing the UCSRC */
	UCSRC = (1<<URSEL);

	/* Setup parity bit */
	UCSRC = (UCSRC&0xCF) | ((config->parity&0x03)<<4);

	/* Setup Number of stop bits */
	UCSRC = (UCSRC&0xF7) | ((config->stopbit&0x01)<<3);

	/* Setup Number of Data Bits */
	UCSRC = (UCSRC&0xF9) | ((config->databits&0x03)<<1);

	/* Setup baudrate */
	UBRRH = (uint8)(ubrrValue >> 8);
	UBRRL = (uint8)ubrrValue;
}



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
void UART_sendByte(uint8 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	* transmitting a new byte so wait until this flag is set to one
	*/
	while(BIT_IS_CLEAR(UCSRA,UDRE));

	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR = data;

	/************************* Another Method *************************
	UDR = data;
	while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transmission is complete TXC = 1
	SET_BIT(UCSRA,TXC); // Clear the TXC flag
	*******************************************************************/
}



/*------------------------------------------------------------------
[Function Name]:  UART_receiveByte
[Description]: responsible for receive byte from another UART device.
[Args]:
[in]	 -NONE
[out]	 -NONE
[in/out] -NONE
[Returns]: the data received through UART
------------------------------------------------------------------*/
uint8 UART_receiveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC));

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
	return UDR;
}




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
void UART_sendString(const uint8 * str)
{
	/* Send the whole string */
	while(*str != '\0')
	{
		UART_sendByte(*str);
		str++;
	}
}



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
void UART_receiveString(uint8 * str)
{

	/* Receive the first byte */
	*str = UART_receiveByte();

	/* Receive the whole string until the '#' */
	while(*str != '#')
	{
		str++;
		*str = UART_receiveByte();

	}
}
