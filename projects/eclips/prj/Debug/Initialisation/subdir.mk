################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Initialisation/Init.c 

OBJS += \
./Initialisation/Init.o 

C_DEPS += \
./Initialisation/Init.d 


# Each subdirectory must supply rules for building sources it contributes
Initialisation/%.o: ../Initialisation/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:\Users\Redud1\Desktop\����� �����\projects\eclips\prj\Drivers\STM32F4xx_HAL_Driver\Inc" -I"C:\Users\Redud1\Desktop\����� �����\projects\eclips\prj\Drivers\STM32F4xx_HAL_Driver\Src" -I"C:\Users\Redud1\Desktop\����� �����\projects\eclips\prj\Drivers\CMSIS\Include" -I"C:\Users\Redud1\Desktop\����� �����\projects\eclips\prj\Drivers\CMSIS\Device\ST\STM32F4xx\Source" -I"C:\Users\Redud1\Desktop\����� �����\projects\eclips\prj\Initialisation" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


