################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Wiznet/Src/socket.c \
../Wiznet/Src/tcp_handler.c \
../Wiznet/Src/w5500.c \
../Wiznet/Src/w5500_spi_handler.c \
../Wiznet/Src/wizchip_conf.c 

OBJS += \
./Wiznet/Src/socket.o \
./Wiznet/Src/tcp_handler.o \
./Wiznet/Src/w5500.o \
./Wiznet/Src/w5500_spi_handler.o \
./Wiznet/Src/wizchip_conf.o 

C_DEPS += \
./Wiznet/Src/socket.d \
./Wiznet/Src/tcp_handler.d \
./Wiznet/Src/w5500.d \
./Wiznet/Src/w5500_spi_handler.d \
./Wiznet/Src/wizchip_conf.d 


# Each subdirectory must supply rules for building sources it contributes
Wiznet/Src/%.o Wiznet/Src/%.su Wiznet/Src/%.cyclo: ../Wiznet/Src/%.c Wiznet/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/User/Documents/STM_32/Workspace_1/toll_controller_bluepil/Wiznet/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Wiznet-2f-Src

clean-Wiznet-2f-Src:
	-$(RM) ./Wiznet/Src/socket.cyclo ./Wiznet/Src/socket.d ./Wiznet/Src/socket.o ./Wiznet/Src/socket.su ./Wiznet/Src/tcp_handler.cyclo ./Wiznet/Src/tcp_handler.d ./Wiznet/Src/tcp_handler.o ./Wiznet/Src/tcp_handler.su ./Wiznet/Src/w5500.cyclo ./Wiznet/Src/w5500.d ./Wiznet/Src/w5500.o ./Wiznet/Src/w5500.su ./Wiznet/Src/w5500_spi_handler.cyclo ./Wiznet/Src/w5500_spi_handler.d ./Wiznet/Src/w5500_spi_handler.o ./Wiznet/Src/w5500_spi_handler.su ./Wiznet/Src/wizchip_conf.cyclo ./Wiznet/Src/wizchip_conf.d ./Wiznet/Src/wizchip_conf.o ./Wiznet/Src/wizchip_conf.su

.PHONY: clean-Wiznet-2f-Src

