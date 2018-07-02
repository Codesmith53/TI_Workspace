################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
DIO.obj: ../DIO.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/Users/codes/Desktop/Firmware/TI/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/codes/Desktop/Firmware/TI/ccsv8/ccs_base/arm/include" --include_path="C:/Users/codes/Desktop/Firmware/TI/ccsv8/ccs_base/arm/include/CMSIS" --include_path="C:/Users/codes/Desktop/Firmware/TI/Source/MSP432Base" --include_path="C:/Users/codes/Desktop/Firmware/TI/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --advice:power=all --define=__MSP432P4111__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="DIO.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

I2C.obj: ../I2C.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/Users/codes/Desktop/Firmware/TI/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/codes/Desktop/Firmware/TI/ccsv8/ccs_base/arm/include" --include_path="C:/Users/codes/Desktop/Firmware/TI/ccsv8/ccs_base/arm/include/CMSIS" --include_path="C:/Users/codes/Desktop/Firmware/TI/Source/MSP432Base" --include_path="C:/Users/codes/Desktop/Firmware/TI/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --advice:power=all --define=__MSP432P4111__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="I2C.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/Users/codes/Desktop/Firmware/TI/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/codes/Desktop/Firmware/TI/ccsv8/ccs_base/arm/include" --include_path="C:/Users/codes/Desktop/Firmware/TI/ccsv8/ccs_base/arm/include/CMSIS" --include_path="C:/Users/codes/Desktop/Firmware/TI/Source/MSP432Base" --include_path="C:/Users/codes/Desktop/Firmware/TI/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --advice:power=all --define=__MSP432P4111__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_msp432p4111_ccs.obj: ../startup_msp432p4111_ccs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/Users/codes/Desktop/Firmware/TI/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/codes/Desktop/Firmware/TI/ccsv8/ccs_base/arm/include" --include_path="C:/Users/codes/Desktop/Firmware/TI/ccsv8/ccs_base/arm/include/CMSIS" --include_path="C:/Users/codes/Desktop/Firmware/TI/Source/MSP432Base" --include_path="C:/Users/codes/Desktop/Firmware/TI/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --advice:power=all --define=__MSP432P4111__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="startup_msp432p4111_ccs.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

system_msp432p4111.obj: ../system_msp432p4111.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/Users/codes/Desktop/Firmware/TI/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/codes/Desktop/Firmware/TI/ccsv8/ccs_base/arm/include" --include_path="C:/Users/codes/Desktop/Firmware/TI/ccsv8/ccs_base/arm/include/CMSIS" --include_path="C:/Users/codes/Desktop/Firmware/TI/Source/MSP432Base" --include_path="C:/Users/codes/Desktop/Firmware/TI/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --advice:power=all --define=__MSP432P4111__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="system_msp432p4111.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


