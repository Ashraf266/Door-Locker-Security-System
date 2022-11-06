 /******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio.c
 *
 * Description: Source file for the ATmega32 GPIO Driver
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/

#include "gpio.h"
#include "common_macros.h"
#include "io_ports_registers.h"



/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


/*------------------------------------------------------------------
[Function Name]:  GPIO_setupPinDirection
[Description]: Setup the direction of the required pin input/output
If the input port number or pin number are not correct, The function will not handle the request.
[Args]:
[in]	uint8 port_num:
					Takes selected PORT_ID
		uint8 pin_num:
					Takes selected PIN_ID
		GPIO_PinDirectionType direction:
					Takes selected PIN data direction
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if( (port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORT) )
	{
		/*Do Nothing*/
	}
	else
	{
		/* Setup the pin direction as required*/
		switch(port_num)
		{
		case PORTA_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRA,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRA,pin_num);
			}
			break;
		case PORTB_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRB,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRB,pin_num);
			}
			break;
		case PORTC_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRC,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRC,pin_num);
			}
			break;
		case PORTD_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRD,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRD,pin_num);
			}
			break;
		}
	}
}

/*------------------------------------------------------------------
[Function Name]:  GPIO_writePin
[Description]: Write the value Logic High or Logic Low on the required pin.
 If the input port number or pin number are not correct, The function will not handle the request.
 If the pin is input, this function will enable/disable the internal pull-up resistor.
[Args]:
[in]	uint8 port_num:
					Takes selected PORT_ID
		uint8 pin_num:
					Takes selected PIN_ID
		uint8 value:
					Takes the value you want to write into the pin
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if( (port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORT) )
	{
		/*Do Nothing*/
	}
	else
	{
		/*Write the pin value as required*/
		switch(port_num)
		{
		case PORTA_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTA,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTA,pin_num);
			}
			break;
		case PORTB_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTB,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTB,pin_num);
			}
			break;
		case PORTC_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTC,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTC,pin_num);
			}
			break;
		case PORTD_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTD,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTD,pin_num);
			}
			break;
		}
	}
}

/*------------------------------------------------------------------
[Function Name]:  GPIO_readPin
[Description]: Read and return the value for the required pin, it should be Logic High or Logic Low.
If the input port number or pin number are not correct, The function will return Logic Low.
[Args]:
[in]	uint8 port_num:
					Takes selected PORT_ID
		uint8 pin_num:
					Takes selected PIN_ID
[out]	-NONE
[in/out] -NONE
[Returns]: the value of the pin in a uint8 variable
------------------------------------------------------------------*/
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num)
{
	uint8 value = LOGIC_LOW;

	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if( (port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORT) )
	{
		/* Do Nothing */
	}
	else
	{
		/* Read the selected pin */
		switch(port_num)
		{
		case PORTA_ID:
			value = GET_BIT(PINA,pin_num);
			break;
		case PORTB_ID:
			value = GET_BIT(PINB,pin_num);
			break;
		case PORTC_ID:
			value = GET_BIT(PINC,pin_num);
			break;
		case PORTD_ID:
			value = GET_BIT(PIND,pin_num);
			break;
		}
	}

	return value;
}

/*------------------------------------------------------------------
[Function Name]:  GPIO_setupPortDirection
[Description]: Setup the direction of the required port all pins input/output.
If the direction value is PORT_INPUT all pins in this port should be input pins.
If the direction value is PORT_OUTPUT all pins in this port should be output pins.
If the input port number is not correct, The function will not handle the request.
[Args]:
[in]	uint8 port_num:
					Takes selected PORT_ID
		GPIO_PinDirectionType direction:
					Takes selected PORT data direction
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the port direction */
		switch(port_num)
		{
		case PORTA_ID:
			DDRA = direction;
			break;
		case PORTB_ID:
			DDRB = direction;
			break;
		case PORTC_ID:
			DDRC = direction;
			break;
		case PORTD_ID:
			DDRD = direction;
			break;
		}
	}
}

/*------------------------------------------------------------------
[Function Name]:  GPIO_writePort
[Description]: Write the value on the required port.
If any pin in the port is output pin the value will be written.
If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
If the input port number is not correct, The function will not handle the request.
[Args]:
[in]	uint8 port_num:
					Takes selected PORT_ID
		uint8 value:
					Takes the value you want to write into the port
[out]	-NONE
[in/out] -NONE
[Returns]: Nothing
------------------------------------------------------------------*/
void GPIO_writePort(uint8 port_num, uint8 value)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* assign the port with the value */
		switch(port_num)
		{
		case PORTA_ID:
			PORTA = value;
			break;
		case PORTB_ID:
			PORTB = value;
			break;
		case PORTC_ID:
			PORTC = value;
			break;
		case PORTD_ID:
			PORTD = value;
			break;
		}
	}
}

/*------------------------------------------------------------------
[Function Name]:  GPIO_readPort
[Description]: Read and return the value of the required port.
If the input port number is not correct, The function will return ZERO value.
[Args]:
[in]	uint8 port_num:
					Takes selected PORT_ID
[out]	-NONE
[in/out] -NONE
[Returns]: the value of the port in a uint8 variable
------------------------------------------------------------------*/
uint8 GPIO_readPort(uint8 port_num)
{
	uint8 value = LOGIC_LOW;

	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* get the value in the selected port */
		switch(port_num)
		{
		case PORTA_ID:
			value = PINA;
			break;
		case PORTB_ID:
			value = PINB;
			break;
		case PORTC_ID:
			value = PINC;
			break;
		case PORTD_ID:
			value = PIND;
			break;
		}
	}

	return value;
}
