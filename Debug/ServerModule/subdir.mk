################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ServerModule/BasicLogic.cpp \
../ServerModule/Module.cpp \
../ServerModule/ThreadLib.cpp 

OBJS += \
./ServerModule/BasicLogic.o \
./ServerModule/Module.o \
./ServerModule/ThreadLib.o 

CPP_DEPS += \
./ServerModule/BasicLogic.d \
./ServerModule/Module.d \
./ServerModule/ThreadLib.d 


# Each subdirectory must supply rules for building sources it contributes
ServerModule/%.o: ../ServerModule/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/Job/MyServer" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


