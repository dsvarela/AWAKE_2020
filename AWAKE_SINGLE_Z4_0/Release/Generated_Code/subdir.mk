################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/Cpu.c \
../Generated_Code/clockMan1.c \
../Generated_Code/dmaController1.c \
../Generated_Code/eMIOS_Mc0.c \
../Generated_Code/eMIOS_Mc2.c \
../Generated_Code/eMIOS_Pwm0.c \
../Generated_Code/eMIOS_Pwm2.c \
../Generated_Code/linflexd_uart1.c \
../Generated_Code/pin_mux.c 

OBJS += \
./Generated_Code/Cpu.o \
./Generated_Code/clockMan1.o \
./Generated_Code/dmaController1.o \
./Generated_Code/eMIOS_Mc0.o \
./Generated_Code/eMIOS_Mc2.o \
./Generated_Code/eMIOS_Pwm0.o \
./Generated_Code/eMIOS_Pwm2.o \
./Generated_Code/linflexd_uart1.o \
./Generated_Code/pin_mux.o 

C_DEPS += \
./Generated_Code/Cpu.d \
./Generated_Code/clockMan1.d \
./Generated_Code/dmaController1.d \
./Generated_Code/eMIOS_Mc0.d \
./Generated_Code/eMIOS_Mc2.d \
./Generated_Code/eMIOS_Pwm0.d \
./Generated_Code/eMIOS_Pwm2.d \
./Generated_Code/linflexd_uart1.d \
./Generated_Code/pin_mux.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@Generated_Code/Cpu.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


