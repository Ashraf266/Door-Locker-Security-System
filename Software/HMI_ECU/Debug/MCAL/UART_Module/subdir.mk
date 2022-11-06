################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/UART_Module/uart.c 

OBJS += \
./MCAL/UART_Module/uart.o 

C_DEPS += \
./MCAL/UART_Module/uart.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/UART_Module/%.o: ../MCAL/UART_Module/%.c MCAL/UART_Module/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\Study\Embedded\MT Diploma\Projects\Final_Project\Final_Project_CODE\HMI_ECU\HAL\Keypad_Module" -I"D:\Study\Embedded\MT Diploma\Projects\Final_Project\Final_Project_CODE\HMI_ECU\APP" -I"D:\Study\Embedded\MT Diploma\Projects\Final_Project\Final_Project_CODE\HMI_ECU\MCAL\Timer_Module" -I"D:\Study\Embedded\MT Diploma\Projects\Final_Project\Final_Project_CODE\HMI_ECU\LIBRARIES\Common" -I"D:\Study\Embedded\MT Diploma\Projects\Final_Project\Final_Project_CODE\HMI_ECU\MCAL\GPIO_Module" -I"D:\Study\Embedded\MT Diploma\Projects\Final_Project\Final_Project_CODE\HMI_ECU\MCAL\UART_Module" -I"D:\Study\Embedded\MT Diploma\Projects\Final_Project\Final_Project_CODE\HMI_ECU\HAL\LCD_Module" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


