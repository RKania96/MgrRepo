################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/modbus/tcp/mbtcp.c 

OBJS += \
./Core/modbus/tcp/mbtcp.o 

C_DEPS += \
./Core/modbus/tcp/mbtcp.d 


# Each subdirectory must supply rules for building sources it contributes
Core/modbus/tcp/mbtcp.o: ../Core/modbus/tcp/mbtcp.c Core/modbus/tcp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L451xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/Libs/inc" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/include" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/port" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/rtu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/modbus/tcp/mbtcp.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
