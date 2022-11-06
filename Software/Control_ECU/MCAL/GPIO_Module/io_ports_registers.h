/******************************************************************************
 *
 * Module: ATmega32 - IO Ports Registers Definitions
 *
 * File Name: io_ports_registers.h
 *
 * Description: All Registers Definitions Needed For The ATmega32 GPIO Module
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/

#ifndef IO_PORTS_REGISTERS_H_
#define IO_PORTS_REGISTERS_H_

#include "std_types.h"

/*PORTD*/
#define PIND (*((volatile const uint8 * const)0x30))
#define DDRD (*((volatile uint8 * const)0x31))
#define PORTD (*((volatile uint8 * const)0x32))

/*PORTC*/
#define PINC (*((volatile const uint8 * const)0x33))
#define DDRC (*((volatile uint8 * const)0x34))
#define PORTC (*((volatile uint8 * const)0x35))

/*PORTB*/
#define PINB (*((volatile const uint8 * const)0x36))
#define DDRB (*((volatile uint8 * const)0x37))
#define PORTB (*((volatile uint8 * const)0x38))

/*PORTA*/
#define PINA (*((volatile const uint8 * const)0x39))
#define DDRA (*((volatile uint8 * const)0x3A))
#define PORTA (*((volatile uint8 * const)0x3B))










#endif /* IO_PORTS_REGISTERS_H_ */
