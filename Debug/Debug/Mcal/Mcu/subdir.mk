################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/USER/AUTOSAR/Mcal/Mcu/Mcu.c \
E:/USER/AUTOSAR/Mcal/Mcu/Mcu_Cfg.c 

OBJS += \
./Mcal/Mcu/Mcu.o \
./Mcal/Mcu/Mcu_Cfg.o 

C_DEPS += \
./Mcal/Mcu/Mcu.d \
./Mcal/Mcu/Mcu_Cfg.d 


# Each subdirectory must supply rules for building sources it contributes
Mcal/Mcu/Mcu.o: E:/USER/AUTOSAR/Mcal/Mcu/Mcu.c Mcal/Mcu/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VETx -c -I../Inc -I"E:/USER/AUTOSAR/Integration" -I"E:/USER/AUTOSAR/Target/STM32F407XXX/Registers/Core" -I"E:/USER/AUTOSAR/Target/STM32F407XXX/Registers/Peripherals" -I"E:/USER/AUTOSAR/Mcal/Dio" -I"E:/USER/AUTOSAR/Mcal/Mcu" -I"E:/USER/AUTOSAR/Mcal/Port" -I"E:/USER/AUTOSAR/Target/STM32F407XXX/Utilities/SysTick" -I"E:/USER/AUTOSAR/Mcal/Can" -I"E:/USER/AUTOSAR/Bsw/Communication/Com_Stack" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Mcal/Mcu/Mcu_Cfg.o: E:/USER/AUTOSAR/Mcal/Mcu/Mcu_Cfg.c Mcal/Mcu/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VETx -c -I../Inc -I"E:/USER/AUTOSAR/Integration" -I"E:/USER/AUTOSAR/Target/STM32F407XXX/Registers/Core" -I"E:/USER/AUTOSAR/Target/STM32F407XXX/Registers/Peripherals" -I"E:/USER/AUTOSAR/Mcal/Dio" -I"E:/USER/AUTOSAR/Mcal/Mcu" -I"E:/USER/AUTOSAR/Mcal/Port" -I"E:/USER/AUTOSAR/Target/STM32F407XXX/Utilities/SysTick" -I"E:/USER/AUTOSAR/Mcal/Can" -I"E:/USER/AUTOSAR/Bsw/Communication/Com_Stack" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Mcal-2f-Mcu

clean-Mcal-2f-Mcu:
	-$(RM) ./Mcal/Mcu/Mcu.cyclo ./Mcal/Mcu/Mcu.d ./Mcal/Mcu/Mcu.o ./Mcal/Mcu/Mcu.su ./Mcal/Mcu/Mcu_Cfg.cyclo ./Mcal/Mcu/Mcu_Cfg.d ./Mcal/Mcu/Mcu_Cfg.o ./Mcal/Mcu/Mcu_Cfg.su

.PHONY: clean-Mcal-2f-Mcu

