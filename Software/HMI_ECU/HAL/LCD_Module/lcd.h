 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD Driver
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* LCD Data bits mode configuration, its value should be 4 or 8*/
#define LCD_DATA_BITS_MODE 8

#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))

#error "Number of Data bits should be equal to 4 or 8"

#endif

/* LCD HW Ports and Pins IDs */
#define LCD_RS_PORT_ID                 PORTD_ID
#define LCD_RS_PIN_ID                  PIN5_ID

#define LCD_RW_PORT_ID                 PORTD_ID
#define LCD_RW_PIN_ID                  PIN6_ID

#define LCD_E_PORT_ID                  PORTD_ID
#define LCD_E_PIN_ID                   PIN7_ID

#define LCD_DATA_PORT_ID               PORTC_ID

#if (LCD_DATA_BITS_MODE == 4)

#define LCD_DB4_PIN_ID                 PIN3_ID
#define LCD_DB5_PIN_ID                 PIN4_ID
#define LCD_DB6_PIN_ID                 PIN5_ID
#define LCD_DB7_PIN_ID                 PIN6_ID

#endif

/* LCD Commands */
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80




/*******************************************************************************
 *                              Functions Prototypes                           *
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
void LCD_init(void);





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
void LCD_sendCommand(uint8 command);





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
void LCD_displayCharacter(char data);





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
void LCD_displayString(const char *str);





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
void LCD_moveCursor(uint8 row,uint8 column);





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
void LCD_displayStringRowColumn(uint8 row,uint8 column,const char *str);





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
void LCD_intgerToString(int data);





/*------------------------------------------------------------------
[Function Name]:  LCD_clearScreen
[Description]: Send the clear screen command
[Args]:
[in]	 -NONE
[out]	 -NONE
[in/out] -NONE
[Returns]: Nothing

------------------------------------------------------------------*/
void LCD_clearScreen(void);


#endif /* LCD_H_ */
