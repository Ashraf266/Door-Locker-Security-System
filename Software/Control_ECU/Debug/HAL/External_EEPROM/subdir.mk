################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/External_EEPROM/external_eeprom.c 

OBJS += \
./HAL/External_EEPROM/external_eeprom.o 

C_DEPS += \
./HAL/External_EEPROM/external_eeprom.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/External_EEPROM/%.o: ../HAL/External_EEPROM/%.c HAL/External_EEPROM/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\Study\Embedded\MT Diploma\Projects\Final_Project\Final_Project_CODE\Control_ECU\LIBRARIES\Common" -I"D:\Study\Embedded\MT Diploma\Projects\Final_Project\Final_Project_CODE\Control_ECU\APP" -I"D:\Study\Embedded\MT Diploma\Projects\Final_Project\Final_Project_CODE\Control_ECU\HAL\Buzzer_Module" -I"D:\Study\Embedded\MT Diploma\Projects\Final_Project\Final_Project_CODE\Control_ECU\HAL\DC_MOTOR_Module" -I"D:\Study\Embedded\MT Diploma\Projects\Final_Project\Final_Project_CODE\Control_ECU\MCAL\PWM_Module" -I"D:\Study\Embedded\MT Diploma\Projects\Final_Project\Final_Project_CODE\Control_ECU\MCAL\GPIO_Module" -I"D:\Study\Embedded\MT Diploma\Projects\Final_Project\Final_Project_CODE\Control_ECU\MCAL\I2C_Module" -I"D:\Study\Embedded\MT Diploma\Projects\Final_Project\Final_Project_CODE\Control_ECU\MCAL\Timer_Module" -I"D:\Study\Embedded\MT Diploma\Projects\Final_Project\Final_Project_CODE\Control_ECU\MCAL\UART_Module" -I"D:\Study\Embedded\MT Diploma\Projects\Final_Project\Final_Project_CODE\Control_ECU\HAL\External_EEPROM" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


