################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Types/StdTypeDefs.cpp 

OBJS += \
./Source/Types/StdTypeDefs.o 

CPP_DEPS += \
./Source/Types/StdTypeDefs.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Types/%.o: ../Source/Types/%.cpp Source/Types/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -c -I"/home/braden/STM32CubeIDE/workspace_1.4.0/RiBearMBed/Include" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

