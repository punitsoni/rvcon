################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../controller.c \
../rvcon.c \
../ui.c 

OBJS += \
./controller.o \
./rvcon.o \
./ui.o 

C_DEPS += \
./controller.d \
./rvcon.d \
./ui.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I"/home/punits/workspace/rvcon/prebuilt/pigpio" -I"/home/punits/workspace/rvcon/prebuilt/curses" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


