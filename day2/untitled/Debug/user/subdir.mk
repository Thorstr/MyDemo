################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../user/user_data.c \
../user/user_debug.c \
../user/user_gpio.c \
../user/user_task.c \
../user/user_usart.c \
../user/user_usb.c 

OBJS += \
./user/user_data.o \
./user/user_debug.o \
./user/user_gpio.o \
./user/user_task.o \
./user/user_usart.o \
./user/user_usb.o 

C_DEPS += \
./user/user_data.d \
./user/user_debug.d \
./user/user_gpio.d \
./user/user_task.d \
./user/user_usart.d \
./user/user_usb.d 


# Each subdirectory must supply rules for building sources it contributes
user/%.o user/%.su user/%.cyclo: ../user/%.c user/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I"D:/thor_work/2024/MyDemo/day2/untitled/user" -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-user

clean-user:
	-$(RM) ./user/user_data.cyclo ./user/user_data.d ./user/user_data.o ./user/user_data.su ./user/user_debug.cyclo ./user/user_debug.d ./user/user_debug.o ./user/user_debug.su ./user/user_gpio.cyclo ./user/user_gpio.d ./user/user_gpio.o ./user/user_gpio.su ./user/user_task.cyclo ./user/user_task.d ./user/user_task.o ./user/user_task.su ./user/user_usart.cyclo ./user/user_usart.d ./user/user_usart.o ./user/user_usart.su ./user/user_usb.cyclo ./user/user_usb.d ./user/user_usb.o ./user/user_usb.su

.PHONY: clean-user

