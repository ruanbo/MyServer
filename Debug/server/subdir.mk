################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../server/SimpleServer.cpp \
../server/main.cpp 

OBJS += \
./server/SimpleServer.o \
./server/main.o 

CPP_DEPS += \
./server/SimpleServer.d \
./server/main.d 


# Each subdirectory must supply rules for building sources it contributes
server/%.o: ../server/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DLOCAL_DEBUG -I"/home/Job/MyServer" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


