 /******************************************************************************
 *
 * Module: DC_MOTOR
 *
 * File Name: dc_motor.h
 *
 * Description: Header file for the DC_MOTOR Driver
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/
#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define DC_MOTOR_IN1_PORT_ID           PORTB_ID
#define DC_MOTOR_IN1_PIN_ID            PIN0_ID

#define DC_MOTOR_IN2_PORT_ID           PORTB_ID
#define DC_MOTOR_IN2_PIN_ID            PIN1_ID

#define DC_MOTOR_E_PORT_ID             PORTB_ID
#define DC_MOTOR_E_PIN_ID              PIN3_ID

/* can choose between PWM_MODE and FIXED_SPEED_MODE
*  if FIXED_SPEED_MODE is applied you must attach a fixed voltage to EN pin in motor Driver IC
*  in FIXED_SPEED_MODE the "speed" value is neglected
*/
#define DC_MOTOR_SPEED_MODE 		   PWM_MODE/*this is for timer 0 only ,can be edited to fit all timers in a future update*/

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/*------------------------------------------------------------------
[ENUM Name]: DC_MOTOR_State
[ENUM Description]: DC_MOTOR_State data type, it is used to define the Dc Motor state
------------------------------------------------------------------*/
typedef enum
{
	STOP,CW,A_CW
}DC_MOTOR_State;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*------------------------------------------------------------------
[Function Name]:  DC_MOTOR_init
[Description]: The Function responsible for setup the direction for the two
				motor pins through the GPIO driver.
 	 	 	 	 Stop the DC-Motor at the beginning through the GPIO driver.
[Args]:
[in]	-EMPTY
[out]	-EMPTY
[in/out] -EMPTY
[Returns]: Nothing
------------------------------------------------------------------*/
void DC_MOTOR_init(void);





/*------------------------------------------------------------------
[Function Name]:  DC_MOTOR_init
[Description]: The function responsible for rotate the DC Motor CW/ or A-CW or
				stop the motor based on the state input state value.
				Send the required duty cycle to the PWM driver based on the
				required speed value.
[Args]:
[in]	DC_MOTOR_State state:
					Takes The required DC Motor state
		uint8 speed:
					 decimal value for the required motor speed, it should be from 0 → 100
[out]	-EMPTY
[in/out] -EMPTY
[Returns]: Nothing
------------------------------------------------------------------*/
void DC_MOTOR_rotate(DC_MOTOR_State state,uint8 speed);





#endif /* DC_MOTOR_H_ */
