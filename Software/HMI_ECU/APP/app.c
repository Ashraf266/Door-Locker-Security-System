/******************************************************************************
 *
 * Module: APP
 *
 * File Name: app.c
 *
 * Description: Source file for the Final_Project HMI_ECU application
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/
#include "app.h"
#include "lcd.h"
#include "keypad.h"
#include "uart.h"
#include "timer.h"
#include <util/delay.h>
#include <avr/io.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
/* seconds counter */
uint8 g_sec = 0;

/* counter to count how many times password has been written wrong */
uint8 passWrongCounter = 0;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*------------------------------------------------------------------
[Function Name]:  app
[Description]:  contain the main loop and the main functionality of the application
[Args]:
[in]	-NONE
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void app(void)
{
	/* variable to store pressed key */
	uint8 keyPressed;

	/* array to store first password entered */
	uint8 pass1arr[PASSWORD_SIZE];

	/* array to store second password entered */
	uint8 pass2arr[PASSWORD_SIZE];

	/* flag to set and reset the password */
	uint8 passSetFlag = 0;

	/* UART configurations structure */
	UART_ConfigType uartConfig = {DISABLE_PARITY,ONE_STOPBIT,EIGHT_DATABITS,9600};

	/* set I-Bit to enable interrupts */
	SREG = (1<<7);

	/* initialize LCD Screen */
	LCD_init();

	/* initialize UART */
	UART_init(&uartConfig);

	/* send READY BYTE to the Control ECU */
	UART_sendByte(HMI_READY);

	while(1)
	{
		/* check if the password is set or not */
		if(passSetFlag == 0)
		{
			/* Checks if the User has logged in before
			 * and the system has restarted for any reason
			 */

			/* asks the Control ECU if password already exists */
			UART_sendByte(CHECK_IF_PASS_EXIST);

			/* if it exist set password is set flag to one and go to the first of the main loop */
			if(UART_receiveByte() == PASS_EXIST)
			{

				passSetFlag = 1;
				continue;
			}

			/* password is not found it means we should setup a new password */
			do
			{
				getPassword(pass1arr);
				getPasswordConfirmation(pass2arr);
				/* Password is set successfully */
				passSetFlag = 1;

				/* repeat till two passwords match */
			}while(checkPasswordsMatching(pass1arr, pass2arr) == TWO_PASSWORDS_NOT_MATCHED);

			/* you got out of the loop means Password is saved successfully */
		}

		/* display Main Menu */
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "+ : Open Door");
		LCD_displayStringRowColumn(1, 0, "- : Change Pass");

		/* loop to get only one of the two options '+' or '-' to open the door or change the password */
		do
		{
			keyPressed = KEYPAD_getPressedKey();
		}while(keyPressed != '+' && keyPressed != '-');

		/* open Door Option */
		if(keyPressed == '+')
		{
			/* loop to repeat till the password is right or you lose all three tries */
			while(1)
			{
				getPassword(pass1arr);

				/* checks if the password is right */
				if(checkPassword(pass1arr) == RIGHT_PASSWORD)
				{
					/* if password is right open the door and get out of the loop */
					openDoor();
					break;
				}

				/* password is wrong -- your chances has reduced by one */
				else
				{
					passWrongCounter++;

					LCD_clearScreen();
					LCD_moveCursor(0, 0);
					LCD_displayString("Wrong Password!!");
					_delay_ms(500);
				}
				/* checks if you entered the password wrong for three times */
				if(passWrongCounter == MAX_NUM_OF_WRONG_TRIES)
				{
					/* activate the alarm */
					activateAlarm();
					break;
				}
			}
			/* reset your wrong pass tries */
			passWrongCounter = 0;

		}

		/* change Password Option */
		else
		{
			/* loop to repeat till the password is right or you lose all three tries */
			while(1)
			{
				getPassword(pass1arr);
				/* checks if the password is right */
				if(checkPassword(pass1arr) == RIGHT_PASSWORD)
				{
					LCD_clearScreen();
					LCD_moveCursor(0, 0);
					LCD_displayString("Change the pass");
					delaySeconds(1);

					/* Clear password flag and continues to get to the loop */
					passSetFlag = 0;

					/* deletes the password in the EEPROM */
					UART_sendByte(RESET_PASS);
					while(UART_receiveByte() != RESET_COMPLETE );

					break;
				}

				/* password is wrong -- your chances has reduced by one */
				else
				{
					passWrongCounter++;
					LCD_clearScreen();
					LCD_moveCursor(0, 0);
					LCD_displayString("Wrong Password!!");
					_delay_ms(500);
				}
				/* checks if you entered the password wrong for three times */
				if(passWrongCounter == MAX_NUM_OF_WRONG_TRIES)
				{
					activateAlarm();
					break;
				}
			}
			/* reset your wrong pass tries */
			passWrongCounter = 0;

		}
	}

}





/*------------------------------------------------------------------
[Function Name]:  countSec
[Description]:  function to increase the number of seconds by one whenever it called
[Args]:
[in]	-NONE
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void countSec(void)
{
	g_sec++;
}





/*------------------------------------------------------------------
[Function Name]:  getPassword
[Description]:  function to get the password and store on an array
[Args]:
[in]	uint8 * pass:
					Pointer to the password array
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void getPassword(uint8 * pass)
{
	/* variable to store pressed key */
	uint8 keyPressed;
	/* counter variable for FOR Loop */
	uint8 i;
	LCD_clearScreen();
	LCD_moveCursor(0, 0);
	LCD_displayString("plz enter pass:");
	LCD_moveCursor(1, 0);
	/* loop to get the password */
	for(i=0;i<PASSWORD_SIZE;i++)
	{
		do
		{
			keyPressed = KEYPAD_getPressedKey();
		}while(keyPressed > 9);
		pass[i] = keyPressed;
		LCD_intgerToString(keyPressed);
		_delay_ms(500);
		LCD_moveCursor(1, i);
		LCD_displayCharacter('*');
	}
	/* wait for the Enter */
	while(KEYPAD_getPressedKey() != 13);
}





/*------------------------------------------------------------------
[Function Name]:  getPasswordConfirmation
[Description]:  function to confirm that the password you entered
[Args]:
[in]	uint8 * pass:
					Pointer to the password array
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void getPasswordConfirmation(uint8 * pass)
{
	/* variable to store pressed key */
	uint8 keyPressed;
	/* counter variable for FOR Loop */
	uint8 i;
	LCD_clearScreen();
	LCD_moveCursor(0, 0);
	LCD_displayString("plz re-enter the");
	LCD_moveCursor(1, 0);
	LCD_displayString("same pass: ");
	/* loop to get the password Confirmation */
	for(i=0;i<PASSWORD_SIZE;i++)
	{
		do
		{
			keyPressed = KEYPAD_getPressedKey();
		}while(keyPressed > 9);
		pass[i] = keyPressed;
		LCD_intgerToString(keyPressed);
		_delay_ms(500);
		LCD_moveCursor(1, i+11);
		LCD_displayCharacter('*');
	}
	/* wait for the Enter */
	while(KEYPAD_getPressedKey() != 13);
}





/*------------------------------------------------------------------
[Function Name]:  getPasswordConfirmation
[Description]:  function to check the two password
[Args]:
[in]	uint8 * pass1:
					Pointer to the password1 array
		uint8 * pass2:
					Pointer to the password2 array
[out]	-NONE
[in/out] -NONE
[Returns]: whether the passwords matched or not
------------------------------------------------------------------*/
uint8 checkPasswordsMatching(uint8 * pass1,uint8 * pass2)
{
	/* counter variable for FOR Loop */
	uint8 i;

	UART_sendByte(SETTING_UP_A_NEW_PASS);
	/* send password 1 and password 2 through UART to check them */
	for(i=0;i<PASSWORD_SIZE;i++)
	{
		UART_sendByte(pass1[i]);
	}
	for(i=0;i<PASSWORD_SIZE;i++)
	{
		UART_sendByte(pass2[i]);
	}
	if(UART_receiveByte() == NEW_PASS_SAVED)
		return TWO_PASSWORDS_MATCHED;
	else
		return TWO_PASSWORDS_NOT_MATCHED;
}





/*------------------------------------------------------------------
[Function Name]:  getPasswordConfirmation
[Description]:  function to check if the password is Right or Wrong
[Args]:
[in]	uint8 * pass:
					Pointer to the password array
[out]	-NONE
[in/out] -NONE
[Returns]: whether the password is Right or Wrong
------------------------------------------------------------------*/
uint8 checkPassword(uint8 * pass)
{
	/* counter variable for FOR Loop */
	uint8 i;

	UART_sendByte(PASS_CHECK);
	/* send the password through UART to check it */
	for(i=0;i<PASSWORD_SIZE;i++)
	{
		UART_sendByte(pass[i]);
	}
	if(UART_receiveByte() == PASS_CORRECT)
		return RIGHT_PASSWORD;
	else
		return WRONG_PASSWORD;
}




/*------------------------------------------------------------------
[Function Name]:  openDoor
[Description]:  Function to Open the door
[Args]:
[in]	-NONE
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void openDoor(void)
{


	UART_sendByte(OPEN_DOOR);
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Door is");
	LCD_displayStringRowColumn(1, 0, "Unlocking");
	delaySeconds(15);

	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Door is Open");
	delaySeconds(3);

	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Door is Locking");
	delaySeconds(15);
}





/*------------------------------------------------------------------
[Function Name]:  activateAlarm
[Description]:  Function to Activate the alarm
[Args]:
[in]	-NONE
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void activateAlarm(void)
{
	UART_sendByte(ACTIVATE_THE_ALERT);
	passWrongCounter = 0;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "!!!! ERROR !!!!");

	/* keep alert on for a minute */
	delaySeconds(60);
}





/*------------------------------------------------------------------
[Function Name]:  delaySeconds
[Description]:  Function to wait a certain amount of seconds
[Args]:
[in]	uint8 sec:
					number of seconds you want to wait
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void delaySeconds(uint8 sec)
{
	/* setting the callBack function to count seconds */
	Timer1_setCallBack(countSec);
	/* timer1 configurations to count sec per interrupt */
	Timer1_ConfigType timer1Config = {0,31250,CLK_256,COMPARE_MODE};

	Timer1_init(&timer1Config);
	while(g_sec < sec);
	g_sec = 0;
	Timer1_deInit();

}


