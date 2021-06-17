################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/modbus/functions/mbfunccoils.c \
../Core/modbus/functions/mbfuncdiag.c \
../Core/modbus/functions/mbfuncdisc.c \
../Core/modbus/functions/mbfuncholding.c \
../Core/modbus/functions/mbfuncinput.c \
../Core/modbus/functions/mbfuncother.c \
../Core/modbus/functions/mbutils.c 

OBJS += \
./Core/modbus/functions/mbfunccoils.o \
./Core/modbus/functions/mbfuncdiag.o \
./Core/modbus/functions/mbfuncdisc.o \
./Core/modbus/functions/mbfuncholding.o \
./Core/modbus/functions/mbfuncinput.o \
./Core/modbus/functions/mbfuncother.o \
./Core/modbus/functions/mbutils.o 

C_DEPS += \
./Core/modbus/functions/mbfunccoils.d \
./Core/modbus/functions/mbfuncdiag.d \
./Core/modbus/functions/mbfuncdisc.d \
./Core/modbus/functions/mbfuncholding.d \
./Core/modbus/functions/mbfuncinput.d \
./Core/modbus/functions/mbfuncother.d \
./Core/modbus/functions/mbutils.d 


# Each subdirectory must supply rules for building sources it contributes
Core/modbus/functions/mbfunccoils.o: ../Core/modbus/functions/mbfunccoils.c Core/modbus/functions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L451xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/Libs/inc" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/include" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/port" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/rtu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/modbus/functions/mbfunccoils.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/modbus/functions/mbfuncdiag.o: ../Core/modbus/functions/mbfuncdiag.c Core/modbus/functions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L451xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/Libs/inc" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/include" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/port" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/rtu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/modbus/functions/mbfuncdiag.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/modbus/functions/mbfuncdisc.o: ../Core/modbus/functions/mbfuncdisc.c Core/modbus/functions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L451xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/Libs/inc" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/include" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/port" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/rtu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/modbus/functions/mbfuncdisc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/modbus/functions/mbfuncholding.o: ../Core/modbus/functions/mbfuncholding.c Core/modbus/functions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L451xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/Libs/inc" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/include" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/port" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/rtu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/modbus/functions/mbfuncholding.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/modbus/functions/mbfuncinput.o: ../Core/modbus/functions/mbfuncinput.c Core/modbus/functions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L451xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/Libs/inc" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/include" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/port" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/rtu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/modbus/functions/mbfuncinput.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/modbus/functions/mbfuncother.o: ../Core/modbus/functions/mbfuncother.c Core/modbus/functions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L451xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/Libs/inc" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/include" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/port" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/rtu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/modbus/functions/mbfuncother.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/modbus/functions/mbutils.o: ../Core/modbus/functions/mbutils.c Core/modbus/functions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L451xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/Libs/inc" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/include" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/port" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/rtu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/modbus/functions/mbutils.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

