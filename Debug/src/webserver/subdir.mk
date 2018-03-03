################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/webserver/http-strings.c \
../src/webserver/httpd-cgi.c \
../src/webserver/httpd-fs.c \
../src/webserver/httpd.c 

OBJS += \
./src/webserver/http-strings.o \
./src/webserver/httpd-cgi.o \
./src/webserver/httpd-fs.o \
./src/webserver/httpd.o 

C_DEPS += \
./src/webserver/http-strings.d \
./src/webserver/httpd-cgi.d \
./src/webserver/httpd-fs.d \
./src/webserver/httpd.d 


# Each subdirectory must supply rules for building sources it contributes
src/webserver/%.o: ../src/webserver/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -I/home/andrey/eclipse-workspace/Tsensor/include/uip -I/home/andrey/eclipse-workspace/Tsensor/include/ds18b20 -I/home/andrey/eclipse-workspace/Tsensor/include/webserver -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


