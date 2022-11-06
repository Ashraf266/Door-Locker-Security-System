 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the Buzzer Driver
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/

#include "buzzer.h"
#include "gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*------------------------------------------------------------------
[Function Name]:  Buzzer_init
[Description]:  Setup the direction for the buzzer pin as output pin through the GPIO driver.
[Args]:
[in]	-NONE
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void Buzzer_init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT);
}





/*------------------------------------------------------------------
[Function Name]:  Buzzer_on
[Description]:   Function to enable the Buzzer through the GPIO
[Args]:
[in]	-NONE
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void Buzzer_on(void)
{
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, BUZZER_ACTIVATE);
}





/*------------------------------------------------------------------
[Function Name]:  Buzzer_off
[Description]:    Function to disable the Buzzer through the GPIO.
[Args]:
[in]	-NONE
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void Buzzer_off(void)
{
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, BUZZER_DEACTIVATE);
}
