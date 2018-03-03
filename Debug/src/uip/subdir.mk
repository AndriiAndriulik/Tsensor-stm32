################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/uip/psock.c \
../src/uip/timer.c \
../src/uip/uip-fw.c \
../src/uip/uip-neighbor.c \
../src/uip/uip-split.c \
../src/uip/uip.c \
../src/uip/uip_arp.c \
../src/uip/uiplib.c 

OBJS += \
./src/uip/psock.o \
./src/uip/timer.o \
./src/uip/uip-fw.o \
./src/uip/uip-neighbor.o \
./src/uip/uip-split.o \
./src/uip/uip.o \
./src/uip/uip_arp.o \
./src/uip/uiplib.o 

C_DEPS += \
./src/uip/psock.d \
./src/uip/timer.d \
./src/uip/uip-fw.d \
./src/uip/uip-neighbor.d \
./src/uip/uip-split.d \
./src/uip/uip.d \
./src/uip/uip_arp.d \
./src/uip/uiplib.d 


# Each subdirectory must supply rules for building sources it contributes
src/uip/%.o: ../src/uip/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -I/home/andrey/eclipse-workspace/Tsensor/include/uip -I/home/andrey/eclipse-workspace/Tsensor/include/ds18b20 -I/home/andrey/eclipse-workspace/Tsensor/include/webserver -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


