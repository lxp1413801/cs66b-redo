#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/cs66b.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/cs66b.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=mcc_generated_files/rtcc.c mcc_generated_files/pin_manager.c mcc_generated_files/interrupt_manager.c mcc_generated_files/mcc.c mcc_generated_files/tmr2.c mcc_generated_files/tmr1.c src/app/main.c src/app/event.c src/app/sample.c src/depend/crc16.c src/depend/m_string.c src/driver/lcd.c src/driver/gpio.c src/driver/ads1148.c src/driver/ads1148_hal.c src/driver/ex_eeprom.c src/driver/i2c.c src/global/globle.c src/soc/delay.c src/soc/ticker.c src/soc/flash.c src/soc/m_asm.s

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/mcc_generated_files/rtcc.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/tmr2.o ${OBJECTDIR}/mcc_generated_files/tmr1.o ${OBJECTDIR}/src/app/main.o ${OBJECTDIR}/src/app/event.o ${OBJECTDIR}/src/app/sample.o ${OBJECTDIR}/src/depend/crc16.o ${OBJECTDIR}/src/depend/m_string.o ${OBJECTDIR}/src/driver/lcd.o ${OBJECTDIR}/src/driver/gpio.o ${OBJECTDIR}/src/driver/ads1148.o ${OBJECTDIR}/src/driver/ads1148_hal.o ${OBJECTDIR}/src/driver/ex_eeprom.o ${OBJECTDIR}/src/driver/i2c.o ${OBJECTDIR}/src/global/globle.o ${OBJECTDIR}/src/soc/delay.o ${OBJECTDIR}/src/soc/ticker.o ${OBJECTDIR}/src/soc/flash.o ${OBJECTDIR}/src/soc/m_asm.o
POSSIBLE_DEPFILES=${OBJECTDIR}/mcc_generated_files/rtcc.o.d ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d ${OBJECTDIR}/mcc_generated_files/mcc.o.d ${OBJECTDIR}/mcc_generated_files/tmr2.o.d ${OBJECTDIR}/mcc_generated_files/tmr1.o.d ${OBJECTDIR}/src/app/main.o.d ${OBJECTDIR}/src/app/event.o.d ${OBJECTDIR}/src/app/sample.o.d ${OBJECTDIR}/src/depend/crc16.o.d ${OBJECTDIR}/src/depend/m_string.o.d ${OBJECTDIR}/src/driver/lcd.o.d ${OBJECTDIR}/src/driver/gpio.o.d ${OBJECTDIR}/src/driver/ads1148.o.d ${OBJECTDIR}/src/driver/ads1148_hal.o.d ${OBJECTDIR}/src/driver/ex_eeprom.o.d ${OBJECTDIR}/src/driver/i2c.o.d ${OBJECTDIR}/src/global/globle.o.d ${OBJECTDIR}/src/soc/delay.o.d ${OBJECTDIR}/src/soc/ticker.o.d ${OBJECTDIR}/src/soc/flash.o.d ${OBJECTDIR}/src/soc/m_asm.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/mcc_generated_files/rtcc.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/tmr2.o ${OBJECTDIR}/mcc_generated_files/tmr1.o ${OBJECTDIR}/src/app/main.o ${OBJECTDIR}/src/app/event.o ${OBJECTDIR}/src/app/sample.o ${OBJECTDIR}/src/depend/crc16.o ${OBJECTDIR}/src/depend/m_string.o ${OBJECTDIR}/src/driver/lcd.o ${OBJECTDIR}/src/driver/gpio.o ${OBJECTDIR}/src/driver/ads1148.o ${OBJECTDIR}/src/driver/ads1148_hal.o ${OBJECTDIR}/src/driver/ex_eeprom.o ${OBJECTDIR}/src/driver/i2c.o ${OBJECTDIR}/src/global/globle.o ${OBJECTDIR}/src/soc/delay.o ${OBJECTDIR}/src/soc/ticker.o ${OBJECTDIR}/src/soc/flash.o ${OBJECTDIR}/src/soc/m_asm.o

# Source Files
SOURCEFILES=mcc_generated_files/rtcc.c mcc_generated_files/pin_manager.c mcc_generated_files/interrupt_manager.c mcc_generated_files/mcc.c mcc_generated_files/tmr2.c mcc_generated_files/tmr1.c src/app/main.c src/app/event.c src/app/sample.c src/depend/crc16.c src/depend/m_string.c src/driver/lcd.c src/driver/gpio.c src/driver/ads1148.c src/driver/ads1148_hal.c src/driver/ex_eeprom.c src/driver/i2c.c src/global/globle.c src/soc/delay.c src/soc/ticker.c src/soc/flash.c src/soc/m_asm.s


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/cs66b.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ128GA310
MP_LINKER_FILE_OPTION=,--script=p24FJ128GA310.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/mcc_generated_files/rtcc.o: mcc_generated_files/rtcc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/rtcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/rtcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/rtcc.c  -o ${OBJECTDIR}/mcc_generated_files/rtcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mcc_generated_files/rtcc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/rtcc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/mcc.c  -o ${OBJECTDIR}/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/mcc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mcc_generated_files/tmr2.o: mcc_generated_files/tmr2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr2.c  -o ${OBJECTDIR}/mcc_generated_files/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr2.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/tmr2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mcc_generated_files/tmr1.o: mcc_generated_files/tmr1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/mcc_generated_files/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/tmr1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/app/main.o: src/app/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/app" 
	@${RM} ${OBJECTDIR}/src/app/main.o.d 
	@${RM} ${OBJECTDIR}/src/app/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/app/main.c  -o ${OBJECTDIR}/src/app/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/app/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/app/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/app/event.o: src/app/event.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/app" 
	@${RM} ${OBJECTDIR}/src/app/event.o.d 
	@${RM} ${OBJECTDIR}/src/app/event.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/app/event.c  -o ${OBJECTDIR}/src/app/event.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/app/event.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/app/event.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/app/sample.o: src/app/sample.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/app" 
	@${RM} ${OBJECTDIR}/src/app/sample.o.d 
	@${RM} ${OBJECTDIR}/src/app/sample.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/app/sample.c  -o ${OBJECTDIR}/src/app/sample.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/app/sample.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/app/sample.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/depend/crc16.o: src/depend/crc16.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/depend" 
	@${RM} ${OBJECTDIR}/src/depend/crc16.o.d 
	@${RM} ${OBJECTDIR}/src/depend/crc16.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/depend/crc16.c  -o ${OBJECTDIR}/src/depend/crc16.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/depend/crc16.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/depend/crc16.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/depend/m_string.o: src/depend/m_string.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/depend" 
	@${RM} ${OBJECTDIR}/src/depend/m_string.o.d 
	@${RM} ${OBJECTDIR}/src/depend/m_string.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/depend/m_string.c  -o ${OBJECTDIR}/src/depend/m_string.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/depend/m_string.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/depend/m_string.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/driver/lcd.o: src/driver/lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/driver" 
	@${RM} ${OBJECTDIR}/src/driver/lcd.o.d 
	@${RM} ${OBJECTDIR}/src/driver/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/driver/lcd.c  -o ${OBJECTDIR}/src/driver/lcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/driver/lcd.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/driver/lcd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/driver/gpio.o: src/driver/gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/driver" 
	@${RM} ${OBJECTDIR}/src/driver/gpio.o.d 
	@${RM} ${OBJECTDIR}/src/driver/gpio.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/driver/gpio.c  -o ${OBJECTDIR}/src/driver/gpio.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/driver/gpio.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/driver/gpio.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/driver/ads1148.o: src/driver/ads1148.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/driver" 
	@${RM} ${OBJECTDIR}/src/driver/ads1148.o.d 
	@${RM} ${OBJECTDIR}/src/driver/ads1148.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/driver/ads1148.c  -o ${OBJECTDIR}/src/driver/ads1148.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/driver/ads1148.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/driver/ads1148.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/driver/ads1148_hal.o: src/driver/ads1148_hal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/driver" 
	@${RM} ${OBJECTDIR}/src/driver/ads1148_hal.o.d 
	@${RM} ${OBJECTDIR}/src/driver/ads1148_hal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/driver/ads1148_hal.c  -o ${OBJECTDIR}/src/driver/ads1148_hal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/driver/ads1148_hal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/driver/ads1148_hal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/driver/ex_eeprom.o: src/driver/ex_eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/driver" 
	@${RM} ${OBJECTDIR}/src/driver/ex_eeprom.o.d 
	@${RM} ${OBJECTDIR}/src/driver/ex_eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/driver/ex_eeprom.c  -o ${OBJECTDIR}/src/driver/ex_eeprom.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/driver/ex_eeprom.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/driver/ex_eeprom.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/driver/i2c.o: src/driver/i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/driver" 
	@${RM} ${OBJECTDIR}/src/driver/i2c.o.d 
	@${RM} ${OBJECTDIR}/src/driver/i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/driver/i2c.c  -o ${OBJECTDIR}/src/driver/i2c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/driver/i2c.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/driver/i2c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/global/globle.o: src/global/globle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/global" 
	@${RM} ${OBJECTDIR}/src/global/globle.o.d 
	@${RM} ${OBJECTDIR}/src/global/globle.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/global/globle.c  -o ${OBJECTDIR}/src/global/globle.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/global/globle.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/global/globle.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/soc/delay.o: src/soc/delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/soc" 
	@${RM} ${OBJECTDIR}/src/soc/delay.o.d 
	@${RM} ${OBJECTDIR}/src/soc/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/soc/delay.c  -o ${OBJECTDIR}/src/soc/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/soc/delay.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/soc/delay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/soc/ticker.o: src/soc/ticker.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/soc" 
	@${RM} ${OBJECTDIR}/src/soc/ticker.o.d 
	@${RM} ${OBJECTDIR}/src/soc/ticker.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/soc/ticker.c  -o ${OBJECTDIR}/src/soc/ticker.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/soc/ticker.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/soc/ticker.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/soc/flash.o: src/soc/flash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/soc" 
	@${RM} ${OBJECTDIR}/src/soc/flash.o.d 
	@${RM} ${OBJECTDIR}/src/soc/flash.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/soc/flash.c  -o ${OBJECTDIR}/src/soc/flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/soc/flash.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/soc/flash.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/mcc_generated_files/rtcc.o: mcc_generated_files/rtcc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/rtcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/rtcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/rtcc.c  -o ${OBJECTDIR}/mcc_generated_files/rtcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mcc_generated_files/rtcc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/rtcc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/mcc.c  -o ${OBJECTDIR}/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/mcc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mcc_generated_files/tmr2.o: mcc_generated_files/tmr2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr2.c  -o ${OBJECTDIR}/mcc_generated_files/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/tmr2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mcc_generated_files/tmr1.o: mcc_generated_files/tmr1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/mcc_generated_files/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/tmr1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/app/main.o: src/app/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/app" 
	@${RM} ${OBJECTDIR}/src/app/main.o.d 
	@${RM} ${OBJECTDIR}/src/app/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/app/main.c  -o ${OBJECTDIR}/src/app/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/app/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/app/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/app/event.o: src/app/event.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/app" 
	@${RM} ${OBJECTDIR}/src/app/event.o.d 
	@${RM} ${OBJECTDIR}/src/app/event.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/app/event.c  -o ${OBJECTDIR}/src/app/event.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/app/event.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/app/event.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/app/sample.o: src/app/sample.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/app" 
	@${RM} ${OBJECTDIR}/src/app/sample.o.d 
	@${RM} ${OBJECTDIR}/src/app/sample.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/app/sample.c  -o ${OBJECTDIR}/src/app/sample.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/app/sample.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/app/sample.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/depend/crc16.o: src/depend/crc16.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/depend" 
	@${RM} ${OBJECTDIR}/src/depend/crc16.o.d 
	@${RM} ${OBJECTDIR}/src/depend/crc16.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/depend/crc16.c  -o ${OBJECTDIR}/src/depend/crc16.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/depend/crc16.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/depend/crc16.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/depend/m_string.o: src/depend/m_string.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/depend" 
	@${RM} ${OBJECTDIR}/src/depend/m_string.o.d 
	@${RM} ${OBJECTDIR}/src/depend/m_string.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/depend/m_string.c  -o ${OBJECTDIR}/src/depend/m_string.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/depend/m_string.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/depend/m_string.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/driver/lcd.o: src/driver/lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/driver" 
	@${RM} ${OBJECTDIR}/src/driver/lcd.o.d 
	@${RM} ${OBJECTDIR}/src/driver/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/driver/lcd.c  -o ${OBJECTDIR}/src/driver/lcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/driver/lcd.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/driver/lcd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/driver/gpio.o: src/driver/gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/driver" 
	@${RM} ${OBJECTDIR}/src/driver/gpio.o.d 
	@${RM} ${OBJECTDIR}/src/driver/gpio.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/driver/gpio.c  -o ${OBJECTDIR}/src/driver/gpio.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/driver/gpio.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/driver/gpio.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/driver/ads1148.o: src/driver/ads1148.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/driver" 
	@${RM} ${OBJECTDIR}/src/driver/ads1148.o.d 
	@${RM} ${OBJECTDIR}/src/driver/ads1148.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/driver/ads1148.c  -o ${OBJECTDIR}/src/driver/ads1148.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/driver/ads1148.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/driver/ads1148.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/driver/ads1148_hal.o: src/driver/ads1148_hal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/driver" 
	@${RM} ${OBJECTDIR}/src/driver/ads1148_hal.o.d 
	@${RM} ${OBJECTDIR}/src/driver/ads1148_hal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/driver/ads1148_hal.c  -o ${OBJECTDIR}/src/driver/ads1148_hal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/driver/ads1148_hal.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/driver/ads1148_hal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/driver/ex_eeprom.o: src/driver/ex_eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/driver" 
	@${RM} ${OBJECTDIR}/src/driver/ex_eeprom.o.d 
	@${RM} ${OBJECTDIR}/src/driver/ex_eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/driver/ex_eeprom.c  -o ${OBJECTDIR}/src/driver/ex_eeprom.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/driver/ex_eeprom.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/driver/ex_eeprom.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/driver/i2c.o: src/driver/i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/driver" 
	@${RM} ${OBJECTDIR}/src/driver/i2c.o.d 
	@${RM} ${OBJECTDIR}/src/driver/i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/driver/i2c.c  -o ${OBJECTDIR}/src/driver/i2c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/driver/i2c.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/driver/i2c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/global/globle.o: src/global/globle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/global" 
	@${RM} ${OBJECTDIR}/src/global/globle.o.d 
	@${RM} ${OBJECTDIR}/src/global/globle.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/global/globle.c  -o ${OBJECTDIR}/src/global/globle.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/global/globle.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/global/globle.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/soc/delay.o: src/soc/delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/soc" 
	@${RM} ${OBJECTDIR}/src/soc/delay.o.d 
	@${RM} ${OBJECTDIR}/src/soc/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/soc/delay.c  -o ${OBJECTDIR}/src/soc/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/soc/delay.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/soc/delay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/soc/ticker.o: src/soc/ticker.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/soc" 
	@${RM} ${OBJECTDIR}/src/soc/ticker.o.d 
	@${RM} ${OBJECTDIR}/src/soc/ticker.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/soc/ticker.c  -o ${OBJECTDIR}/src/soc/ticker.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/soc/ticker.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/soc/ticker.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/soc/flash.o: src/soc/flash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/soc" 
	@${RM} ${OBJECTDIR}/src/soc/flash.o.d 
	@${RM} ${OBJECTDIR}/src/soc/flash.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/soc/flash.c  -o ${OBJECTDIR}/src/soc/flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/soc/flash.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/soc/flash.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/soc/m_asm.o: src/soc/m_asm.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/soc" 
	@${RM} ${OBJECTDIR}/src/soc/m_asm.o.d 
	@${RM} ${OBJECTDIR}/src/soc/m_asm.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/soc/m_asm.s  -o ${OBJECTDIR}/src/soc/m_asm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -Wa,-MD,"${OBJECTDIR}/src/soc/m_asm.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/soc/m_asm.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/src/soc/m_asm.o: src/soc/m_asm.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/soc" 
	@${RM} ${OBJECTDIR}/src/soc/m_asm.o.d 
	@${RM} ${OBJECTDIR}/src/soc/m_asm.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/soc/m_asm.s  -o ${OBJECTDIR}/src/soc/m_asm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -Wa,-MD,"${OBJECTDIR}/src/soc/m_asm.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/soc/m_asm.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/cs66b.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/cs66b.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang"  -mreserve=data@0x800:0x81B -mreserve=data@0x81C:0x81D -mreserve=data@0x81E:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x827 -mreserve=data@0x82A:0x84F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/cs66b.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/cs66b.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"os_configs" -I"os_kernel/include" -I"os_portable" -I"os_portable/memmang" -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/cs66b.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
