################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/USER/AUTOSAR/Mcal/Can/Can.c \
E:/USER/AUTOSAR/Mcal/Can/Can_Cfg.c \
E:/USER/AUTOSAR/Mcal/Can/Can_PBcfg.c 

OBJS += \
./Mcal/Can/Can.o \
./Mcal/Can/Can_Cfg.o \
./Mcal/Can/Can_PBcfg.o 

C_DEPS += \
./Mcal/Can/Can.d \
./Mcal/Can/Can_Cfg.d \
./Mcal/Can/Can_PBcfg.d 


# Each subdirectory must supply rules for building sources it contributes
Mcal/Can/Can.o: E:/USER/AUTOSAR/Mcal/Can/Can.c Mcal/Can/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VETx -c -I../Inc -I"E:/USER/AUTOSAR/Integration" -I"E:/USER/AUTOSAR/Target/STM32F407XXX/Registers/Core" -I"E:/USER/AUTOSAR/Target/STM32F407XXX/Registers/Peripherals" -I"E:/USER/AUTOSAR/Mcal/Dio" -I"E:/USER/AUTOSAR/Mcal/Mcu" -I"E:/USER/AUTOSAR/Mcal/Port" -I"E:/USER/AUTOSAR/Target/STM32F407XXX/Utilities/SysTick" -I"E:/USER/AUTOSAR/Mcal/Can" -I"E:/USER/AUTOSAR/Bsw/Communication/Com_Stack" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Mcal/Can/Can_Cfg.o: E:/USER/AUTOSAR/Mcal/Can/Can_Cfg.c Mcal/Can/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VETx -c -I../Inc -I"E:/USER/AUTOSAR/Integration" -I"E:/USER/AUTOSAR/Target/STM32F407XXX/Registers/Core" -I"E:/USER/AUTOSAR/Target/STM32F407XXX/Registers/Peripherals" -I"E:/USER/AUTOSAR/Mcal/Dio" -I"E:/USER/AUTOSAR/Mcal/Mcu" -I"E:/USER/AUTOSAR/Mcal/Port" -I"E:/USER/AUTOSAR/Target/STM32F407XXX/Utilities/SysTick" -I"E:/USER/AUTOSAR/Mcal/Can" -I"E:/USER/AUTOSAR/Bsw/Communication/Com_Stack" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Mcal/Can/Can_PBcfg.o: E:/USER/AUTOSAR/Mcal/Can/Can_PBcfg.c Mcal/Can/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VETx -c -I../Inc -I"E:/USER/AUTOSAR/Integration" -I"E:/USER/AUTOSAR/Target/STM32F407XXX/Registers/Core" -I"E:/USER/AUTOSAR/Target/STM32F407XXX/Registers/Peripherals" -I"E:/USER/AUTOSAR/Mcal/Dio" -I"E:/USER/AUTOSAR/Mcal/Mcu" -I"E:/USER/AUTOSAR/Mcal/Port" -I"E:/USER/AUTOSAR/Target/STM32F407XXX/Utilities/SysTick" -I"E:/USER/AUTOSAR/Mcal/Can" -I"E:/USER/AUTOSAR/Bsw/Communication/Com_Stack" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Mcal-2f-Can

clean-Mcal-2f-Can:
	-$(RM) ./Mcal/Can/Can.cyclo ./Mcal/Can/Can.d ./Mcal/Can/Can.o ./Mcal/Can/Can.su ./Mcal/Can/Can_Cfg.cyclo ./Mcal/Can/Can_Cfg.d ./Mcal/Can/Can_Cfg.o ./Mcal/Can/Can_Cfg.su ./Mcal/Can/Can_PBcfg.cyclo ./Mcal/Can/Can_PBcfg.d ./Mcal/Can/Can_PBcfg.o ./Mcal/Can/Can_PBcfg.su

.PHONY: clean-Mcal-2f-Can

