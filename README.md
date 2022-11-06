# Door-Locker-Security-Systems
Door Locker Security System to unlock a door using a password.
The Project Based on ATmega32 using two ECUs.

First one: HMI_ECU (Human Machine Interface) with 2x16 LCD and 4x4 keypad.
HMI_ECU is just responsible for interaction with the user just takes inputs through keypad and display 
messages on the LCD.

Second one: Control_ECU with EEPROM, Buzzer, and Dc-Motor.
CONTROL_ECU is responsible for all the processing and decisions in the system like password 
checking, open the door and activate the system alarm.

The two ECUs send commands to each other using UART.

Drivers Used in this Project:
GPIO Driver,LCD Driver,Keypad Driver,DC_Motor Driver,EEPROM Driver,I2C Driver,UART Driver,Timer Driver,Buzzer Driver.
