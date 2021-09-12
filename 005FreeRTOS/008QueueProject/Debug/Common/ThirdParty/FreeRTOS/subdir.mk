################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/croutine.c \
/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/event_groups.c \
/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/list.c \
/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/queue.c \
/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/stream_buffer.c \
/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/tasks.c \
/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/timers.c 

OBJS += \
./Common/ThirdParty/FreeRTOS/croutine.o \
./Common/ThirdParty/FreeRTOS/event_groups.o \
./Common/ThirdParty/FreeRTOS/list.o \
./Common/ThirdParty/FreeRTOS/queue.o \
./Common/ThirdParty/FreeRTOS/stream_buffer.o \
./Common/ThirdParty/FreeRTOS/tasks.o \
./Common/ThirdParty/FreeRTOS/timers.o 

C_DEPS += \
./Common/ThirdParty/FreeRTOS/croutine.d \
./Common/ThirdParty/FreeRTOS/event_groups.d \
./Common/ThirdParty/FreeRTOS/list.d \
./Common/ThirdParty/FreeRTOS/queue.d \
./Common/ThirdParty/FreeRTOS/stream_buffer.d \
./Common/ThirdParty/FreeRTOS/tasks.d \
./Common/ThirdParty/FreeRTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Common/ThirdParty/FreeRTOS/croutine.o: /home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/croutine.c Common/ThirdParty/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/include -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/Config -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/OS -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/SEGGER -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Common/ThirdParty/FreeRTOS/croutine.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Common/ThirdParty/FreeRTOS/event_groups.o: /home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/event_groups.c Common/ThirdParty/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/include -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/Config -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/OS -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/SEGGER -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Common/ThirdParty/FreeRTOS/event_groups.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Common/ThirdParty/FreeRTOS/list.o: /home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/list.c Common/ThirdParty/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/include -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/Config -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/OS -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/SEGGER -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Common/ThirdParty/FreeRTOS/list.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Common/ThirdParty/FreeRTOS/queue.o: /home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/queue.c Common/ThirdParty/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/include -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/Config -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/OS -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/SEGGER -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Common/ThirdParty/FreeRTOS/queue.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Common/ThirdParty/FreeRTOS/stream_buffer.o: /home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/stream_buffer.c Common/ThirdParty/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/include -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/Config -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/OS -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/SEGGER -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Common/ThirdParty/FreeRTOS/stream_buffer.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Common/ThirdParty/FreeRTOS/tasks.o: /home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/tasks.c Common/ThirdParty/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/include -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/Config -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/OS -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/SEGGER -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Common/ThirdParty/FreeRTOS/tasks.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Common/ThirdParty/FreeRTOS/timers.o: /home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/timers.c Common/ThirdParty/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/include -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/Config -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/OS -I/home/igor/Documentos/microcontroladores/ARM/Cursos/005FreeRTOS/Common/ThirdParty/SEGGER/SEGGER -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Common/ThirdParty/FreeRTOS/timers.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

