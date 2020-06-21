################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/config.c \
../src/date.c \
../src/date_check.c \
../src/date_days.c \
../src/days_date.c \
../src/event.c \
../src/lahzeh.c \
../src/leap_year.c \
../src/option.c \
../src/time.c 

OBJS += \
./src/config.o \
./src/date.o \
./src/date_check.o \
./src/date_days.o \
./src/days_date.o \
./src/event.o \
./src/lahzeh.o \
./src/leap_year.o \
./src/option.o \
./src/time.o 

C_DEPS += \
./src/config.d \
./src/date.d \
./src/date_check.d \
./src/date_days.d \
./src/days_date.d \
./src/event.d \
./src/lahzeh.d \
./src/leap_year.d \
./src/option.d \
./src/time.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


