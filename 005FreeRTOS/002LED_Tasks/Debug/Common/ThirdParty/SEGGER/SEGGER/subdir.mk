################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/SEGGER/SEGGER_RTT.c \
/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/SEGGER/SEGGER_RTT_printf.c \
/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/SEGGER/SEGGER_SYSVIEW.c 

S_UPPER_SRCS += \
/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.S 

OBJS += \
./Common/ThirdParty/SEGGER/SEGGER/SEGGER_RTT.o \
./Common/ThirdParty/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.o \
./Common/ThirdParty/SEGGER/SEGGER/SEGGER_RTT_printf.o \
./Common/ThirdParty/SEGGER/SEGGER/SEGGER_SYSVIEW.o 

S_UPPER_DEPS += \
./Common/ThirdParty/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.d 

C_DEPS += \
./Common/ThirdParty/SEGGER/SEGGER/SEGGER_RTT.d \
./Common/ThirdParty/SEGGER/SEGGER/SEGGER_RTT_printf.d \
./Common/ThirdParty/SEGGER/SEGGER/SEGGER_SYSVIEW.d 


# Each subdirectory must supply rules for building sources it contributes
Common/ThirdParty/SEGGER/SEGGER/SEGGER_RTT.o: /home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/SEGGER/SEGGER_RTT.c Common/ThirdParty/SEGGER/SEGGER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/include -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/Config -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/OS -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/SEGGER -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Common/ThirdParty/SEGGER/SEGGER/SEGGER_RTT.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Common/ThirdParty/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.o: /home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.S Common/ThirdParty/SEGGER/SEGGER/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/Config -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/SEGGER -I"/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/include" -x assembler-with-cpp -MMD -MP -MF"Common/ThirdParty/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
Common/ThirdParty/SEGGER/SEGGER/SEGGER_RTT_printf.o: /home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/SEGGER/SEGGER_RTT_printf.c Common/ThirdParty/SEGGER/SEGGER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/include -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/Config -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/OS -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/SEGGER -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Common/ThirdParty/SEGGER/SEGGER/SEGGER_RTT_printf.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Common/ThirdParty/SEGGER/SEGGER/SEGGER_SYSVIEW.o: /home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/SEGGER/SEGGER_SYSVIEW.c Common/ThirdParty/SEGGER/SEGGER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/include -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/Config -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/OS -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/SEGGER -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Common/ThirdParty/SEGGER/SEGGER/SEGGER_SYSVIEW.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

