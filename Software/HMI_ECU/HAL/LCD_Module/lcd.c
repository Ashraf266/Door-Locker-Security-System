 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the LCD Driver
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/
#include "lcd.h"
#include "gpio.h"
#include "common_macros.h"
#include <stdlib.h>
#include <util/delay.h>



/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


/*------------------------------------------------------------------
[Function Name]:  LCD_init
[Description]: Initialize the LCD
1. Setup the LCD pins directions by use the GPIO driver.
2. Setup the LCD Data Mode 4-bits or 8-bits.
[Args]:
[in]	 -NONE
[out]	 -NONE
[in/out] -NONE
[Returns]: Nothing

------------------------------------------------------------------*/
void LCD_init(void)
{
	GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_RW_PORT_ID, LCD_RW_PIN_ID, PIN_OUTPUT);
	GPIO_writePin(LCD_RW_PORT_ID, LCD_RW_PIN_ID, LOGIC_LOW);/*this driver is always in write mode*/
	GPIO_setupPinDirection(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT);
	_delay_ms(20);/*wait till the LCD Turn ON*/

#if(LCD_DATA_BITS_MODE == 4)
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, PIN_OUTPUT);
	/*Mode configurations*/
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);

#elif(LCD_DATA_BITS_MODE == 8)
	GPIO_setupPortDirection(LCD_DATA_PORT_ID, PORT_OUTPUT);
	/*Mode configurations*/
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
#endif

	LCD_sendCommand(LCD_CURSOR_OFF);
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}


/*------------------------------------------------------------------
[Function Name]:  LCD_sendCommand
[Description]: Send the required command to the screen
[Args]:
[in]	 uint8 command:
					Takes the required command to pass it to the LCD
[out]	 -NONE
[in/out] -NONE
[Returns]: Nothing

------------------------------------------------------------------*/
void LCD_sendCommand(uint8 command)
{
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW);
	_delay_ms(1);/*Tas = 50ns*/
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);/*Tpw - Tdws = 190ns*/

#if(LCD_DATA_BITS_MODE == 4)
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(command,4));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(command,5));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(command,6));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(command,7));

	_delay_ms(1);/*Tdsw = 100ns*/
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);/*Th = 13ns*/

	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);/*Tpw - Tdws = 190ns*/
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(command,0));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(command,1));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(command,2));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(command,3));

#elif(LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT_ID, command);
#endif

	_delay_ms(1);/*Tdsw = 100ns*/
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);/*Th = 13ns*/
}


/*------------------------------------------------------------------
[Function Name]:  LCD_displayCharacter
[Description]: Display the required character on the screen
[Args]:
[in]	 uint8 data:
					Takes the required data to display it on the screen
[out]	 -NONE
[in/out] -NONE
[Returns]: Nothing

------------------------------------------------------------------*/
void LCD_displayCharacter(char data)
{
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);/*Tas = 50ns*/
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);/*Tpw - Tdws = 190ns*/

#if(LCD_DATA_BITS_MODE == 4)
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(data,4));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(data,5));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(data,6));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(data,7));

	_delay_ms(1);/*Tdsw = 100ns*/
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);/*Th = 13ns*/

	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);/*Tpw - Tdws = 190ns*/
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(data,0));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(data,1));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(data,2));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(data,3));

#elif(LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT_ID, data);
#endif

	_delay_ms(1);/*Tdsw = 100ns*/
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);/*Th = 13ns*/
}


/*------------------------------------------------------------------
[Function Name]:  LCD_displayString
[Description]: Display the required string on the screen
[Args]:
[in]	 const char *str:
					Takes the address of the first character in the string
[out]	 -NONE
[in/out] -NONE
[Returns]: Nothing

------------------------------------------------------------------*/
void LCD_displayString(const char *str)
{
	while(*str != '\0')
	{
		LCD_displayCharacter(*str);
		str++;
	}
}


/*------------------------------------------------------------------
[Function Name]:  LCD_moveCursor
[Description]: Move the cursor to a specified row and column index on the screen
[Args]:
[in]	 uint8 row:
					Takes the row you want the cursor to be in
		 uint8 column:
		 	 	 	Takes the column you want the cursor to be in
[out]	 -NONE
[in/out] -NONE
[Returns]: Nothing

------------------------------------------------------------------*/
void LCD_moveCursor(uint8 row,uint8 column)
{
	uint8 cursorAddress;
	switch(row)
	{
	case 0:
		cursorAddress = column+0x00;
		break;
	case 1:
		cursorAddress = column+0x40;
		break;
	case 2:
		cursorAddress = column+0x10;
		break;
	case 3:
		cursorAddress = column+0x50;
		break;
	}
	LCD_sendCommand(LCD_SET_CURSOR_LOCATION | cursorAddress);
}


/*------------------------------------------------------------------
[Function Name]:  LCD_displayStringRowColumn
[Description]: Display the required string in a specified row and column index on the screen
[Args]:
[in]	 uint8 row:
					Takes the row you want the cursor to be in
		 uint8 column:
		 	 	 	Takes the column you want the cursor to be in
		 const char *str:
					Takes the address of the first character in the string
[out]	 -NONE
[in/out] -NONE
[Returns]: Nothing

------------------------------------------------------------------*/
void LCD_displayStringRowColumn(uint8 row,uint8 column,const char *str)
{
	LCD_moveCursor(row, column);
	LCD_displayString(str);
}


/*------------------------------------------------------------------
[Function Name]:  LCD_intgerToString
[Description]: Display the required decimal value on the screen
[Args]:
[in]	 int data:
					Takes the required data to display it on the screen
[out]	 -NONE
[in/out] -NONE
[Returns]: Nothing

------------------------------------------------------------------*/
void LCD_intgerToString(int data)
{
	char buffer[16];
	itoa(data,buffer,10);
	LCD_displayString(buffer);
}


/*------------------------------------------------------------------
[Function Name]:  LCD_clearScreen
[Description]: Send the clear screen command
[Args]:
[in]	 -NONE
[out]	 -NONE
[in/out] -NONE
[Returns]: Nothing

------------------------------------------------------------------*/
void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}
