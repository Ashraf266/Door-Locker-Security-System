/******************************************************************************
 *
 * Module: APP
 *
 * File Name: app.c
 *
 * Description: Source file for the Final_Project Control_ECU application
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/
#include "app.h"
#include "uart.h"
#include "timer.h"
#include "external_eeprom.h"
#include "dc_motor.h"
#include "i2c.h"
#include "buzzer.h"
#include <util/delay.h>
#include <avr/io.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

uint8 g_sec = 0;

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

	/* contains the command received through UART */
	uint8 command;

	/* array to store first password entered */
	uint8 pass1arr[PASSWORD_SIZE];

	/* array to store second password entered */
	uint8 pass2arr[PASSWORD_SIZE];

	/* set I-Bit to enable interrupts */
	SREG = (1<<7);

	/* UART configurations structure */
	UART_ConfigType uartConfig = {DISABLE_PARITY,ONE_STOPBIT,EIGHT_DATABITS,9600};

	/* initialize UART */
	UART_init(&uartConfig);

	/* I2C configurations structure */
	I2C_ConfigType i2cConfig = {FAST_MODE,0b0000001};

	/* initialize I2C */
	I2C_init(&i2cConfig);

	/* initialize Motor */
	DC_MOTOR_init();

	/* initialize Buzzer */
	Buzzer_init();

	/* wait till the HMI ECU is ready */
	while(UART_receiveByte() != HMI_READY);

	while(1)
	{
		/* receive a command */
		command = UART_receiveByte();

		switch(command)
		{
		case SETTING_UP_A_NEW_PASS:
			setupNewPassword(pass1arr,pass2arr);
			break;

		case PASS_CHECK:
			checkPassword(pass1arr, pass2arr);
			break;

		case OPEN_DOOR:
			openDoor();
			break;

		case ACTIVATE_THE_ALERT:
			activateAlarm();
			break;

		case CHECK_IF_PASS_EXIST:
			/* Checks if there is a password stored in the EEPROM */
			checkIfPassExist();
			break;

		case RESET_PASS:
			/* Deletes old password */
			resetPass();
			break;
		}
	}
}





/*------------------------------------------------------------------
[Function Name]:  compareTwoPasswords
[Description]:  function to check the two password Matched
[Args]:
[in]	uint8 * pass1:
					Pointer to the password1 array
		uint8 * pass2:
					Pointer to the password2 array
[out]	-NONE
[in/out] -NONE
[Returns]: whether the passwords matched or not
------------------------------------------------------------------*/
uint8 compareTwoPasswords(uint8 * pass1,uint8 * pass2)
{
	uint8 i;
	for(i=0;i<PASSWORD_SIZE;i++)
	{
		/* check if pass1 = pass2 */
		if(pass1[i] == pass2[i])
			continue;
		else
			return ERROR;
	}
	return OK;
}





/*------------------------------------------------------------------
[Function Name]:  activateAlarm
[Description]:  Function to Check if the there is a password saved already or not
[Args]:
[in]	-NONE
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void checkIfPassExist(void)
{
	uint8 check;
	/* check if the password exist or not */
	EEPROM_readByte(0x00F0 - 1, &check);
	_delay_ms(10);
	/* if it exist tell the HMI ECU that there is a password saved */
	if(check == PASS_EXIST)
		UART_sendByte(PASS_EXIST);
	else
		UART_sendByte(ERROR);
}





/*------------------------------------------------------------------
[Function Name]:  resetPass
[Description]:  Function to delete the old Password
[Args]:
[in]	-NONE
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void resetPass(void)
{
	/* Delete the OLD password  " Deletes the password_exist byte " */
	EEPROM_writeByte(0x00F0 - 1, 0x00);
	_delay_ms(10);
	UART_sendByte(RESET_COMPLETE);
}





/*------------------------------------------------------------------
[Function Name]:  setupNewPassword
[Description]:  function to check if the two passwords you entered matched and setup a new the password and save it
[Args]:
[in]	uint8 * pass1:
					Pointer to the password1 array
		uint8 * pass2:
					Pointer to the password2 array
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void setupNewPassword(uint8 * pass1, uint8 * pass2)
{
	uint8 i;
	/* get the password */
	for(i=0;i<PASSWORD_SIZE;i++)
	{
		pass1[i] = UART_receiveByte();
	}
	/* get the password confirmation */
	for(i=0;i<PASSWORD_SIZE;i++)
	{
		pass2[i] = UART_receiveByte();
	}
	/* compare the two passwords */
	if(compareTwoPasswords(pass1, pass2) == OK)
	{
		/* if they Matched save the password */
		for(i=0;i<PASSWORD_SIZE;i++)
		{
			EEPROM_writeByte(0x00F0+i, pass1[i]);
			_delay_ms(10);
		}
		/* sets a byte before the current password to say that password exists ... used in case of power off */
		EEPROM_writeByte(0x00F0 - 1, PASS_EXIST);
		_delay_ms(10);
		UART_sendByte(NEW_PASS_SAVED);
	}
	/* if they don't match send error */
	else
	{
		UART_sendByte(ERROR);
	}
}





/*------------------------------------------------------------------
[Function Name]:  checkPassword
[Description]:  function to check if the password is Right or Wrong
[Args]:
[in]	uint8 * pass:
					Pointer to the password array
[out]	-NONE
[in/out] -NONE
[Returns]: whether the password is Right or Wrong
------------------------------------------------------------------*/
void checkPassword(uint8 * pass1, uint8 * pass2)
{
	uint8 i;
	/* receive the first password */
	for(i=0;i<PASSWORD_SIZE;i++)
	{
		pass1[i] = UART_receiveByte();
	}
	/* read the password saved in the EEPROM */
	for(i=0;i<PASSWORD_SIZE;i++)
	{
		EEPROM_readByte(0x00F0+i, pass2+i);
		_delay_ms(10);
	}
	/* if they matched tell the HMI_ECU that passwrod is right */
	if(compareTwoPasswords(pass1, pass2) == OK)
	{
		UART_sendByte(PASS_CORRECT);
	}
	else
	{
		UART_sendByte(ERROR);
	}
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
	/* unlock the door for 15 sec */
	DC_MOTOR_rotate(CW, 100);
	delaySeconds(15);

	/* Hold the door for 3 sec */
	DC_MOTOR_rotate(STOP, 100);
	delaySeconds(3);

	/* lock the door for 15 sec */
	DC_MOTOR_rotate(A_CW, 100);
	delaySeconds(15);

	/* Stop the motor */
	DC_MOTOR_rotate(STOP, 100);
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
	/* Turn on the buzzer for a minute */
	Buzzer_on();
	delaySeconds(60);
	Buzzer_off();
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
