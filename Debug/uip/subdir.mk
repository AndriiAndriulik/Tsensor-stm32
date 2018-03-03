################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../uip/psock.c \
../uip/timer.c \
../uip/uip-fw.c \
../uip/uip-neighbor.c \
../uip/uip-split.c \
../uip/uip.c \
../uip/uip_arp.c \
../uip/uiplib.c 

OBJS += \
./uip/psock.o \
./uip/timer.o \
./uip/uip-fw.o \
./uip/uip-neighbor.o \
./uip/uip-split.o \
./uip/uip.o \
./uip/uip_arp.o \
./uip/uiplib.o 

C_DEPS += \
./uip/psock.d \
./uip/timer.d \
./uip/uip-fw.d \
./uip/uip-neighbor.d \
./uip/uip-split.d \
./uip/uip.d \
./uip/uip_arp.d \
./uip/uiplib.d 


# Each subdirectory must supply rules for building sources it contributes
uip/%.o: ../uip/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I/home/andrey/eclipse-workspace/Tsensor/uip -I/home/andrey/eclipse-workspace/Tsensor/ds18b20 -I/home/andrey/eclipse-workspace/Tsensor/webserver -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


