################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Types/Time/Time.cpp 

OBJS += \
./Source/Types/Time/Time.o 

CPP_DEPS += \
./Source/Types/Time/Time.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Types/Time/%.o: ../Source/Types/Time/%.cpp Source/Types/Time/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -c -I"/home/braden/STM32CubeIDE/workspace_1.4.0/RiBearMBed/Include" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

