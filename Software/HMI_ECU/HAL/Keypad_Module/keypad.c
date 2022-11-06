/******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.c
 *
 * Description: Source file for the Keypad driver
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/
#include "keypad.h"
#include "gpio.h"

/*******************************************************************************
 *                      Functions Prototypes(Private)                          *
 *******************************************************************************/

#ifndef STANDARD_KEYPAD

#if KEYPAD_NUM_COLS == 3

static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 key);

#elif KEYPAD_NUM_COLS == 4

static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number);

#endif

#endif




/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

uint8 KEYPAD_getPressedKey(void)
{
	uint8 row,col;
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+0, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+1, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+2, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+3, PIN_INPUT);

	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+0, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+1, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+2, PIN_INPUT);

#if KEYPAD_NUM_COLS == 4
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+3, PIN_INPUT);
#endif

	while(1)
	{
		for(row=0;row<KEYPAD_NUM_ROWS;row++)
		{
			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+row, PIN_OUTPUT);
			GPIO_writePin(PORTB_ID, KEYPAD_FIRST_ROW_PIN_ID+row, KEYPAD_BUTTON_PRESSED);
			for(col=0;col<KEYPAD_NUM_COLS;col++)
			{
				if(GPIO_readPin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+col) == KEYPAD_BUTTON_PRESSED)
						#ifndef STANDARD_KEYPAD
							#if KEYPAD_NUM_COLS == 3
								return KEYPAD_4x3_adjustKeyNumber(row*KEYPAD_NUM_COLS + col +1);
							#elif KEYPAD_NUM_COLS == 4
								return KEYPAD_4x4_adjustKeyNumber(row*KEYPAD_NUM_COLS + col +1);
							#endif

						#else
								return (row*KEYPAD_NUM_COLS + col +1);
						#endif
			}
			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+row, PIN_INPUT);
		}
	}
}
#ifndef STANDARD_KEYPAD

#if KEYPAD_NUM_COLS == 3

static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 key)
{
	switch(key)
	{
	case 10:
		return '*';
	case 11:
		return 0;
	case 12:
		return '#';
	}
	return key;
}

#elif KEYPAD_NUM_COLS == 4

static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number)
{
	uint8 keypad_button = 0;
	switch(button_number)
	{
	case 1: keypad_button = 7;
	break;
	case 2: keypad_button = 8;
	break;
	case 3: keypad_button = 9;
	break;
	case 4: keypad_button = '%'; // ASCII Code of %
	break;
	case 5: keypad_button = 4;
	break;
	case 6: keypad_button = 5;
	break;
	case 7: keypad_button = 6;
	break;
	case 8: keypad_button = '*'; /* ASCII Code of '*' */
	break;
	case 9: keypad_button = 1;
	break;
	case 10: keypad_button = 2;
	break;
	case 11: keypad_button = 3;
	break;
	case 12: keypad_button = '-'; /* ASCII Code of '-' */
	break;
	case 13: keypad_button = 13;  /* ASCII of Enter */
	break;
	case 14: keypad_button = 0;
	break;
	case 15: keypad_button = '='; /* ASCII Code of '=' */
	break;
	case 16: keypad_button = '+'; /* ASCII Code of '+' */
	break;
	default: keypad_button = button_number;
	break;
	}
	return keypad_button;
}
#endif
#endif


