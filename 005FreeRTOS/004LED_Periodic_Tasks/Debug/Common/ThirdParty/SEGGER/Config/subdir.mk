################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.c 

OBJS += \
./Common/ThirdParty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.o 

C_DEPS += \
./Common/ThirdParty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.d 


# Each subdirectory must supply rules for building sources it contributes
Common/ThirdParty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.o: /home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.c Common/ThirdParty/SEGGER/Config/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/include -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/Config -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/OS -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/SEGGER -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Common/ThirdParty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

