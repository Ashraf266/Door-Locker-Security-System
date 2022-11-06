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

/* callback function pointer */
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

/*------------------------------------------------------------------
[Function Name]:  Timer1_init
[Description]: Function to initialize the Timer driver
[Args]:
[in]	Timer1_ConfigType * config:
					pointer to configuration structure
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void Timer1_init(const Timer1_ConfigType * config)
{
	if(config->mode == NORMAL_MODE)
	{
		TCCR1A = 0x0C;
	}
	else
	{
		/* compare mode configurations */
		TCCR1A = 0x0C;
		TCCR1B = 0x08;
		OCR1A = config->compare_value;
	}
	/* sets initial value in TCNT1 register */
	TCNT1 = config->initial_value;

	/* setup prescaller */
	TCCR1B = (TCCR1B & 0xF8) | (config->prescaler & 0x07);

	if(config->mode == NORMAL_MODE)
	{
		/* Enable Over Flow interrupt for Normal mode configurations */
		TIMSK = (1<<TOIE1);
	}
	else
	{
		/* Enable Compare interrupt for Compare mode configurations */
		TIMSK = (1<<OCIE1A);
	}
}






/*------------------------------------------------------------------
[Function Name]:  Timer1_deInit
[Description]: Function to disable the Timer1
[Args]:
[in]	-NONE
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void Timer1_deInit(void)
{
	/* Disable Timer1 */
	TCCR1B = 0;
	TCCR1A = 0;
	TCCR1B = 0;
	OCR1A = 0;
	TCNT1 = 0;
}





/*------------------------------------------------------------------
[Function Name]:  Timer1_setCallBack
[Description]: Function to set the Call Back function address
[Args]:
[in]	-NONE
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void Timer1_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = (volatile void (*)(void))a_ptr;
}
