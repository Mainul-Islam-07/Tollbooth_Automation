################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/ISR_handler.c \
../Core/Src/app_main.c \
../Core/Src/commands.c \
../Core/Src/dma.c \
../Core/Src/ds3231_rtc.c \
../Core/Src/gpio.c \
../Core/Src/i2c.c \
../Core/Src/main.c \
../Core/Src/print_active.c \
../Core/Src/sensors.c \
../Core/Src/spi.c \
../Core/Src/state_machine.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/tim.c \
../Core/Src/trigger.c \
../Core/Src/uart_manager.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/ISR_handler.o \
./Core/Src/app_main.o \
./Core/Src/commands.o \
./Core/Src/dma.o \
./Core/Src/ds3231_rtc.o \
./Core/Src/gpio.o \
./Core/Src/i2c.o \
./Core/Src/main.o \
./Core/Src/print_active.o \
./Core/Src/sensors.o \
./Core/Src/spi.o \
./Core/Src/state_machine.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/tim.o \
./Core/Src/trigger.o \
./Core/Src/uart_manager.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/ISR_handler.d \
./Core/Src/app_main.d \
./Core/Src/commands.d \
./Core/Src/dma.d \
./Core/Src/ds3231_rtc.d \
./Core/Src/gpio.d \
./Core/Src/i2c.d \
./Core/Src/main.d \
./Core/Src/print_active.d \
./Core/Src/sensors.d \
./Core/Src/spi.d \
./Core/Src/state_machine.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/tim.d \
./Core/Src/trigger.d \
./Core/Src/uart_manager.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/User/Documents/STM_32/Workspace_1/toll_controller_bluepil/Wiznet/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/ISR_handler.cyclo ./Core/Src/ISR_handler.d ./Core/Src/ISR_handler.o ./Core/Src/ISR_handler.su ./Core/Src/app_main.cyclo ./Core/Src/app_main.d ./Core/Src/app_main.o ./Core/Src/app_main.su ./Core/Src/commands.cyclo ./Core/Src/commands.d ./Core/Src/commands.o ./Core/Src/commands.su ./Core/Src/dma.cyclo ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/ds3231_rtc.cyclo ./Core/Src/ds3231_rtc.d ./Core/Src/ds3231_rtc.o ./Core/Src/ds3231_rtc.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/i2c.cyclo ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/print_active.cyclo ./Core/Src/print_active.d ./Core/Src/print_active.o ./Core/Src/print_active.su ./Core/Src/sensors.cyclo ./Core/Src/sensors.d ./Core/Src/sensors.o ./Core/Src/sensors.su ./Core/Src/spi.cyclo ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/state_machine.cyclo ./Core/Src/state_machine.d ./Core/Src/state_machine.o ./Core/Src/state_machine.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/trigger.cyclo ./Core/Src/trigger.d ./Core/Src/trigger.o ./Core/Src/trigger.su ./Core/Src/uart_manager.cyclo ./Core/Src/uart_manager.d ./Core/Src/uart_manager.o ./Core/Src/uart_manager.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su

.PHONY: clean-Core-2f-Src

