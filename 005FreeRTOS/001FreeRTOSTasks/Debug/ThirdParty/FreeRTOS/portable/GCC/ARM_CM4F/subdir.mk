################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F/port.c 

OBJS += \
./ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F/port.o 

C_DEPS += \
./ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F/port.d 


# Each subdirectory must supply rules for building sources it contributes
ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F/port.o: ../ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F/port.c ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/001FreeRTOSTasks/ThirdParty/SEGGER/Config" -I"/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/001FreeRTOSTasks/ThirdParty/SEGGER/OS" -I"/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/001FreeRTOSTasks/ThirdParty/SEGGER/SEGGER" -I"/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/001FreeRTOSTasks/ThirdParty/FreeRTOS" -I"/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/001FreeRTOSTasks/ThirdParty/FreeRTOS/include" -I"/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/001FreeRTOSTasks/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F/port.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

