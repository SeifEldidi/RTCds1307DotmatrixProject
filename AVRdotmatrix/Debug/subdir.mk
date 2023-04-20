################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../I2C.c \
../MAX7219.c \
../RTCDS1307.c \
../SPI.c \
../main.c 

OBJS += \
./I2C.o \
./MAX7219.o \
./RTCDS1307.o \
./SPI.o \
./main.o 

C_DEPS += \
./I2C.d \
./MAX7219.d \
./RTCDS1307.d \
./SPI.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g3 -gdwarf-2 -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


