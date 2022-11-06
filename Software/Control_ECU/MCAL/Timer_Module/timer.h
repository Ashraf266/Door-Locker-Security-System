 /******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.h
 *
 * Description: Header file for the ATmega32 Timer Driver
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/*------------------------------------------------------------------
[ENUM Name]: Timer1_Prescaler
[ENUM Description]: it's used to define timer1 pre-scaler
------------------------------------------------------------------*/
typedef enum
{
	CLK_1 = 1,
	CLK_8,
	CLK_64,
	CLK_256,
	CLK_1024,
}Timer1_Prescaler;

/*------------------------------------------------------------------
[ENUM Name]: Timer1_Mode
[ENUM Description]: it's used to define timer1 Mode
------------------------------------------------------------------*/
typedef enum
{
	NORMAL_MODE,COMPARE_MODE
}Timer1_Mode;

/*------------------------------------------------------------------
[Structure Name]: Timer1_ConfigType
[Structure Description]: it's used to define Timer1 configurations
------------------------------------------------------------------*/
typedef struct {
 uint16 initial_value;
 uint16 compare_value; // it will be used in compare mode only.
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;




/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void Timer1_init(const Timer1_ConfigType * config);

void Timer1_deInit(void);

void Timer1_setCallBack(void(*a_ptr)(void));


#endif /* TIMER_H_ */
