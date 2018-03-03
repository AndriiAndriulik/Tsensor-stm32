################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ds18b20/ds18b20.c 

OBJS += \
./ds18b20/ds18b20.o 

C_DEPS += \
./ds18b20/ds18b20.d 


# Each subdirectory must supply rules for building sources it contributes
ds18b20/%.o: ../ds18b20/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I/home/andrey/eclipse-workspace/Tsensor/uip -I/home/andrey/eclipse-workspace/Tsensor/ds18b20 -I/home/andrey/eclipse-workspace/Tsensor/webserver -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


