 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the Buzzer Driver
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/
#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* Buzzer pin & port */
#define BUZZER_PORT		 			PORTD_ID
#define BUZZER_PIN		 			PIN7_ID

/* Activation state Depends on the transistor that activates the buzzer */
#define BUZZER_ACTIVATE				LOGIC_HIGH
#define BUZZER_DEACTIVATE			LOGIC_LOW

/*******************************************************************************
 *                              Functions Prototypes                           *
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
void Buzzer_init(void);





/*------------------------------------------------------------------
[Function Name]:  Buzzer_on
[Description]:   Function to enable the Buzzer through the GPIO
[Args]:
[in]	-NONE
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void Buzzer_on(void);





/*------------------------------------------------------------------
[Function Name]:  Buzzer_off
[Description]:    Function to disable the Buzzer through the GPIO.
[Args]:
[in]	-NONE
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void Buzzer_off(void);



#endif
