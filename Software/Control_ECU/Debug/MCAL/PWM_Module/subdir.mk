################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/PWM_Module/pwm.c 

OBJS += \
./MCAL/PWM_Module/pwm.o 

C_DEPS += \
./MCAL/PWM_Module/pwm.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/PWM_Module/%.o: ../MCAL/PWM_Module/%.c MCAL/PWM_Module/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\Study\Embedded\MT Diploma\Projects\Final_Project\Final_Project_CODE\Control_ECU\LIBRARIES\Common" -I"D:\Study\Embedded\MT Diploma\Projects\Final_Project\Final_Project_CODE\Control_ECU\APP" -I"D:\Study\Embedded\MT Diploma\Projects\Final_Project\Final_Project_CODE\Control_ECU\HAL\Buzzer_Module" -I"D:\Study\Embedded\MT Diploma\Projects\Final_Project\Final_Project_CODE\Control_ECU\HAL\DC_MOTOR_Module" -I"D:\Study\Embedded\MT Diploma\Projects\Final_Project\Final_Project_CODE\Control_ECU\MCAL\PWM_Module" -I"D:\Study\Embedded\MT Diploma\Projects\Final_Project\Final_Project_CODE\Control_ECU\MCAL\GPIO_Module" -I"D:\Study\Embedded\MT Diploma\Projects\Final_Project\Final_Project_CODE\Control_ECU\MCAL\I2C_Module" -I"D:\Study\Embedded\MT Diploma\Projects\Final_Project\Final_Project_CODE\Control_ECU\MCAL\Timer_Module" -I"D:\Study\Embedded\MT Diploma\Projects\Final_Project\Final_Project_CODE\Control_ECU\MCAL\UART_Module" -I"D:\Study\Embedded\MT Diploma\Projects\Final_Project\Final_Project_CODE\Control_ECU\HAL\External_EEPROM" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


