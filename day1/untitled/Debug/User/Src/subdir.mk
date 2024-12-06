################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/Src/user_dds.c \
../User/Src/user_debug.c \
../User/Src/user_gpio.c \
../User/Src/user_task.c \
../User/Src/user_usart.c 

OBJS += \
./User/Src/user_dds.o \
./User/Src/user_debug.o \
./User/Src/user_gpio.o \
./User/Src/user_task.o \
./User/Src/user_usart.o 

C_DEPS += \
./User/Src/user_dds.d \
./User/Src/user_debug.d \
./User/Src/user_gpio.d \
./User/Src/user_task.d \
./User/Src/user_usart.d 


# Each subdirectory must supply rules for building sources it contributes
User/Src/%.o User/Src/%.su User/Src/%.cyclo: ../User/Src/%.c User/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I"D:/thor_work/2024/MyDemo/day1/untitled/User/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-User-2f-Src

clean-User-2f-Src:
	-$(RM) ./User/Src/user_dds.cyclo ./User/Src/user_dds.d ./User/Src/user_dds.o ./User/Src/user_dds.su ./User/Src/user_debug.cyclo ./User/Src/user_debug.d ./User/Src/user_debug.o ./User/Src/user_debug.su ./User/Src/user_gpio.cyclo ./User/Src/user_gpio.d ./User/Src/user_gpio.o ./User/Src/user_gpio.su ./User/Src/user_task.cyclo ./User/Src/user_task.d ./User/Src/user_task.o ./User/Src/user_task.su ./User/Src/user_usart.cyclo ./User/Src/user_usart.d ./User/Src/user_usart.o ./User/Src/user_usart.su

.PHONY: clean-User-2f-Src

