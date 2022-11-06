 /******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.c
 *
 * Description: Source file for the ATmega32 Timer Driver
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/

#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(* g_callBackPtr)();
	}
}

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(* g_callBackPtr)();
	}
}

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void Timer1_init(const Timer1_ConfigType * config)
{
	if(config->mode == NORMAL_MODE)
	{
		TCCR1A = 0x0C;
	}
	else
	{
		TCCR1A = 0x0C;
		TCCR1B = 0x08;
		OCR1A = config->compare_value;
	}
	TCNT1 = config->initial_value;
	TCCR1B = (TCCR1B & 0xF8) | (config->prescaler & 0x07);

	if(config->mode == NORMAL_MODE)
	{
		TIMSK = (1<<TOIE1);
	}
	else
	{
		TIMSK = (1<<OCIE1A);
	}
}

void Timer1_deInit(void)
{
	TCCR1B = 0;
	TCCR1A = 0;
	TCCR1B = 0;
	OCR1A = 0;
	TCNT1 = 0;
}

void Timer1_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = (volatile void (*)(void))a_ptr;
}
