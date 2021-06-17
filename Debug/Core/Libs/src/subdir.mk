################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Libs/src/ADS131A0x.c \
../Core/Libs/src/fonts.c \
../Core/Libs/src/mbutils.c \
../Core/Libs/src/modbus.c \
../Core/Libs/src/st7735.c \
../Core/Libs/src/tmp116.c 

OBJS += \
./Core/Libs/src/ADS131A0x.o \
./Core/Libs/src/fonts.o \
./Core/Libs/src/mbutils.o \
./Core/Libs/src/modbus.o \
./Core/Libs/src/st7735.o \
./Core/Libs/src/tmp116.o 

C_DEPS += \
./Core/Libs/src/ADS131A0x.d \
./Core/Libs/src/fonts.d \
./Core/Libs/src/mbutils.d \
./Core/Libs/src/modbus.d \
./Core/Libs/src/st7735.d \
./Core/Libs/src/tmp116.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Libs/src/ADS131A0x.o: ../Core/Libs/src/ADS131A0x.c Core/Libs/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L451xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/Libs/inc" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/include" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/port" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/rtu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Libs/src/ADS131A0x.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Libs/src/fonts.o: ../Core/Libs/src/fonts.c Core/Libs/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L451xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/Libs/inc" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/include" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/port" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/rtu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Libs/src/fonts.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Libs/src/mbutils.o: ../Core/Libs/src/mbutils.c Core/Libs/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L451xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/Libs/inc" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/include" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/port" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/rtu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Libs/src/mbutils.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Libs/src/modbus.o: ../Core/Libs/src/modbus.c Core/Libs/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L451xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/Libs/inc" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/include" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/port" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/rtu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Libs/src/modbus.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Libs/src/st7735.o: ../Core/Libs/src/st7735.c Core/Libs/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L451xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/Libs/inc" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/include" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/port" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/rtu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Libs/src/st7735.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Libs/src/tmp116.o: ../Core/Libs/src/tmp116.c Core/Libs/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L451xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/Libs/inc" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/include" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/port" -I"C:/Nextcloud/STM32/PowerMeter_v3/Core/modbus/rtu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Libs/src/tmp116.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

