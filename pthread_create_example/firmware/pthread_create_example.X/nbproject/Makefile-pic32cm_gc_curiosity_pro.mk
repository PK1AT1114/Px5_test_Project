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
ifeq "$(wildcard nbproject/Makefile-local-pic32cm_gc_curiosity_pro.mk)" "nbproject/Makefile-local-pic32cm_gc_curiosity_pro.mk"
include nbproject/Makefile-local-pic32cm_gc_curiosity_pro.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=pic32cm_gc_curiosity_pro
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/pthread_create_example.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/pthread_create_example.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/click/Ambient/Ambient.c ../src/click/Proximity3/Proximity3.c ../src/click/Servo/RcServo.c ../src/click/Weather/Bme280.c ../src/click/Weather/WeatherClick.c ../src/config/pic32cm_gc_curiosity_pro/bsp/bsp.c ../src/config/pic32cm_gc_curiosity_pro/driver/spi/src/drv_spi.c ../src/config/pic32cm_gc_curiosity_pro/driver/usart/src/drv_usart.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/adc/plib_adc.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/clock/plib_clock.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/dmac/plib_dmac.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/eic/plib_eic.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/evsys/plib_evsys.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/nvic/plib_nvic.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/pm/plib_pm.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/port/plib_port.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/sercom/i2c_master/plib_sercom1_i2c_master.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/sercom/spi_master/plib_sercom2_spi_master.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/sercom/usart/plib_sercom3_usart.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/sercom/usart/plib_sercom4_usart.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/tcc/plib_tcc0.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/tcc/plib_tcc1.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/tcc/plib_tcc3.c ../src/config/pic32cm_gc_curiosity_pro/sdl/common/drv_common/sdl_drv_common.c ../src/config/pic32cm_gc_curiosity_pro/sdl/common/sdl_common.c ../src/config/pic32cm_gc_curiosity_pro/sdl/port/drv_port/sdl_drv_port.c ../src/config/pic32cm_gc_curiosity_pro/sdl/port/sdl_port.c ../src/config/pic32cm_gc_curiosity_pro/sdl/systick/drv_systick/sdl_drv_systick.c ../src/config/pic32cm_gc_curiosity_pro/stdio/xc32_monitor.c ../src/config/pic32cm_gc_curiosity_pro/system/dma/sys_dma.c ../src/config/pic32cm_gc_curiosity_pro/system/int/src/sys_int.c ../src/config/pic32cm_gc_curiosity_pro/libc_syscalls.c ../src/config/pic32cm_gc_curiosity_pro/initialization.c ../src/config/pic32cm_gc_curiosity_pro/exceptions.c ../src/config/pic32cm_gc_curiosity_pro/interrupts.c ../src/config/pic32cm_gc_curiosity_pro/startup_xc32.c ../src/pwm_driver/pwm_driver.c ../src/spi_driver/spi_async_driver.c ../src/platform_setup.c ../src/pthread_create_example.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/can/plib_can0.c ../src/can_driver/can_driver.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/803290761/Ambient.o ${OBJECTDIR}/_ext/949596075/Proximity3.o ${OBJECTDIR}/_ext/471585352/RcServo.o ${OBJECTDIR}/_ext/1312294611/Bme280.o ${OBJECTDIR}/_ext/1312294611/WeatherClick.o ${OBJECTDIR}/_ext/853750373/bsp.o ${OBJECTDIR}/_ext/1448873790/drv_spi.o ${OBJECTDIR}/_ext/1523867863/drv_usart.o ${OBJECTDIR}/_ext/714998607/plib_adc.o ${OBJECTDIR}/_ext/83206111/plib_clock.o ${OBJECTDIR}/_ext/690022278/plib_dmac.o ${OBJECTDIR}/_ext/714994608/plib_eic.o ${OBJECTDIR}/_ext/85355597/plib_evsys.o ${OBJECTDIR}/_ext/689715471/plib_nvic.o ${OBJECTDIR}/_ext/392577996/plib_pm.o ${OBJECTDIR}/_ext/689662320/plib_port.o ${OBJECTDIR}/_ext/1527759270/plib_sercom1_i2c_master.o ${OBJECTDIR}/_ext/1036524628/plib_sercom2_spi_master.o ${OBJECTDIR}/_ext/2020896858/plib_sercom3_usart.o ${OBJECTDIR}/_ext/2020896858/plib_sercom4_usart.o ${OBJECTDIR}/_ext/714980379/plib_tcc0.o ${OBJECTDIR}/_ext/714980379/plib_tcc1.o ${OBJECTDIR}/_ext/714980379/plib_tcc3.o ${OBJECTDIR}/_ext/2062074510/sdl_drv_common.o ${OBJECTDIR}/_ext/8787811/sdl_common.o ${OBJECTDIR}/_ext/731817458/sdl_drv_port.o ${OBJECTDIR}/_ext/1496808455/sdl_port.o ${OBJECTDIR}/_ext/532237110/sdl_drv_systick.o ${OBJECTDIR}/_ext/99633435/xc32_monitor.o ${OBJECTDIR}/_ext/1183487548/sys_dma.o ${OBJECTDIR}/_ext/1106506504/sys_int.o ${OBJECTDIR}/_ext/1291214997/libc_syscalls.o ${OBJECTDIR}/_ext/1291214997/initialization.o ${OBJECTDIR}/_ext/1291214997/exceptions.o ${OBJECTDIR}/_ext/1291214997/interrupts.o ${OBJECTDIR}/_ext/1291214997/startup_xc32.o ${OBJECTDIR}/_ext/603174789/pwm_driver.o ${OBJECTDIR}/_ext/193257301/spi_async_driver.o ${OBJECTDIR}/_ext/1360937237/platform_setup.o ${OBJECTDIR}/_ext/1360937237/pthread_create_example.o ${OBJECTDIR}/_ext/714996767/plib_can0.o ${OBJECTDIR}/_ext/508636337/can_driver.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/803290761/Ambient.o.d ${OBJECTDIR}/_ext/949596075/Proximity3.o.d ${OBJECTDIR}/_ext/471585352/RcServo.o.d ${OBJECTDIR}/_ext/1312294611/Bme280.o.d ${OBJECTDIR}/_ext/1312294611/WeatherClick.o.d ${OBJECTDIR}/_ext/853750373/bsp.o.d ${OBJECTDIR}/_ext/1448873790/drv_spi.o.d ${OBJECTDIR}/_ext/1523867863/drv_usart.o.d ${OBJECTDIR}/_ext/714998607/plib_adc.o.d ${OBJECTDIR}/_ext/83206111/plib_clock.o.d ${OBJECTDIR}/_ext/690022278/plib_dmac.o.d ${OBJECTDIR}/_ext/714994608/plib_eic.o.d ${OBJECTDIR}/_ext/85355597/plib_evsys.o.d ${OBJECTDIR}/_ext/689715471/plib_nvic.o.d ${OBJECTDIR}/_ext/392577996/plib_pm.o.d ${OBJECTDIR}/_ext/689662320/plib_port.o.d ${OBJECTDIR}/_ext/1527759270/plib_sercom1_i2c_master.o.d ${OBJECTDIR}/_ext/1036524628/plib_sercom2_spi_master.o.d ${OBJECTDIR}/_ext/2020896858/plib_sercom3_usart.o.d ${OBJECTDIR}/_ext/2020896858/plib_sercom4_usart.o.d ${OBJECTDIR}/_ext/714980379/plib_tcc0.o.d ${OBJECTDIR}/_ext/714980379/plib_tcc1.o.d ${OBJECTDIR}/_ext/714980379/plib_tcc3.o.d ${OBJECTDIR}/_ext/2062074510/sdl_drv_common.o.d ${OBJECTDIR}/_ext/8787811/sdl_common.o.d ${OBJECTDIR}/_ext/731817458/sdl_drv_port.o.d ${OBJECTDIR}/_ext/1496808455/sdl_port.o.d ${OBJECTDIR}/_ext/532237110/sdl_drv_systick.o.d ${OBJECTDIR}/_ext/99633435/xc32_monitor.o.d ${OBJECTDIR}/_ext/1183487548/sys_dma.o.d ${OBJECTDIR}/_ext/1106506504/sys_int.o.d ${OBJECTDIR}/_ext/1291214997/libc_syscalls.o.d ${OBJECTDIR}/_ext/1291214997/initialization.o.d ${OBJECTDIR}/_ext/1291214997/exceptions.o.d ${OBJECTDIR}/_ext/1291214997/interrupts.o.d ${OBJECTDIR}/_ext/1291214997/startup_xc32.o.d ${OBJECTDIR}/_ext/603174789/pwm_driver.o.d ${OBJECTDIR}/_ext/193257301/spi_async_driver.o.d ${OBJECTDIR}/_ext/1360937237/platform_setup.o.d ${OBJECTDIR}/_ext/1360937237/pthread_create_example.o.d ${OBJECTDIR}/_ext/714996767/plib_can0.o.d ${OBJECTDIR}/_ext/508636337/can_driver.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/803290761/Ambient.o ${OBJECTDIR}/_ext/949596075/Proximity3.o ${OBJECTDIR}/_ext/471585352/RcServo.o ${OBJECTDIR}/_ext/1312294611/Bme280.o ${OBJECTDIR}/_ext/1312294611/WeatherClick.o ${OBJECTDIR}/_ext/853750373/bsp.o ${OBJECTDIR}/_ext/1448873790/drv_spi.o ${OBJECTDIR}/_ext/1523867863/drv_usart.o ${OBJECTDIR}/_ext/714998607/plib_adc.o ${OBJECTDIR}/_ext/83206111/plib_clock.o ${OBJECTDIR}/_ext/690022278/plib_dmac.o ${OBJECTDIR}/_ext/714994608/plib_eic.o ${OBJECTDIR}/_ext/85355597/plib_evsys.o ${OBJECTDIR}/_ext/689715471/plib_nvic.o ${OBJECTDIR}/_ext/392577996/plib_pm.o ${OBJECTDIR}/_ext/689662320/plib_port.o ${OBJECTDIR}/_ext/1527759270/plib_sercom1_i2c_master.o ${OBJECTDIR}/_ext/1036524628/plib_sercom2_spi_master.o ${OBJECTDIR}/_ext/2020896858/plib_sercom3_usart.o ${OBJECTDIR}/_ext/2020896858/plib_sercom4_usart.o ${OBJECTDIR}/_ext/714980379/plib_tcc0.o ${OBJECTDIR}/_ext/714980379/plib_tcc1.o ${OBJECTDIR}/_ext/714980379/plib_tcc3.o ${OBJECTDIR}/_ext/2062074510/sdl_drv_common.o ${OBJECTDIR}/_ext/8787811/sdl_common.o ${OBJECTDIR}/_ext/731817458/sdl_drv_port.o ${OBJECTDIR}/_ext/1496808455/sdl_port.o ${OBJECTDIR}/_ext/532237110/sdl_drv_systick.o ${OBJECTDIR}/_ext/99633435/xc32_monitor.o ${OBJECTDIR}/_ext/1183487548/sys_dma.o ${OBJECTDIR}/_ext/1106506504/sys_int.o ${OBJECTDIR}/_ext/1291214997/libc_syscalls.o ${OBJECTDIR}/_ext/1291214997/initialization.o ${OBJECTDIR}/_ext/1291214997/exceptions.o ${OBJECTDIR}/_ext/1291214997/interrupts.o ${OBJECTDIR}/_ext/1291214997/startup_xc32.o ${OBJECTDIR}/_ext/603174789/pwm_driver.o ${OBJECTDIR}/_ext/193257301/spi_async_driver.o ${OBJECTDIR}/_ext/1360937237/platform_setup.o ${OBJECTDIR}/_ext/1360937237/pthread_create_example.o ${OBJECTDIR}/_ext/714996767/plib_can0.o ${OBJECTDIR}/_ext/508636337/can_driver.o

# Source Files
SOURCEFILES=../src/click/Ambient/Ambient.c ../src/click/Proximity3/Proximity3.c ../src/click/Servo/RcServo.c ../src/click/Weather/Bme280.c ../src/click/Weather/WeatherClick.c ../src/config/pic32cm_gc_curiosity_pro/bsp/bsp.c ../src/config/pic32cm_gc_curiosity_pro/driver/spi/src/drv_spi.c ../src/config/pic32cm_gc_curiosity_pro/driver/usart/src/drv_usart.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/adc/plib_adc.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/clock/plib_clock.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/dmac/plib_dmac.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/eic/plib_eic.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/evsys/plib_evsys.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/nvic/plib_nvic.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/pm/plib_pm.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/port/plib_port.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/sercom/i2c_master/plib_sercom1_i2c_master.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/sercom/spi_master/plib_sercom2_spi_master.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/sercom/usart/plib_sercom3_usart.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/sercom/usart/plib_sercom4_usart.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/tcc/plib_tcc0.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/tcc/plib_tcc1.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/tcc/plib_tcc3.c ../src/config/pic32cm_gc_curiosity_pro/sdl/common/drv_common/sdl_drv_common.c ../src/config/pic32cm_gc_curiosity_pro/sdl/common/sdl_common.c ../src/config/pic32cm_gc_curiosity_pro/sdl/port/drv_port/sdl_drv_port.c ../src/config/pic32cm_gc_curiosity_pro/sdl/port/sdl_port.c ../src/config/pic32cm_gc_curiosity_pro/sdl/systick/drv_systick/sdl_drv_systick.c ../src/config/pic32cm_gc_curiosity_pro/stdio/xc32_monitor.c ../src/config/pic32cm_gc_curiosity_pro/system/dma/sys_dma.c ../src/config/pic32cm_gc_curiosity_pro/system/int/src/sys_int.c ../src/config/pic32cm_gc_curiosity_pro/libc_syscalls.c ../src/config/pic32cm_gc_curiosity_pro/initialization.c ../src/config/pic32cm_gc_curiosity_pro/exceptions.c ../src/config/pic32cm_gc_curiosity_pro/interrupts.c ../src/config/pic32cm_gc_curiosity_pro/startup_xc32.c ../src/pwm_driver/pwm_driver.c ../src/spi_driver/spi_async_driver.c ../src/platform_setup.c ../src/pthread_create_example.c ../src/config/pic32cm_gc_curiosity_pro/peripheral/can/plib_can0.c ../src/can_driver/can_driver.c

# Pack Options 
PACK_COMMON_OPTIONS=-I "${CMSIS_DIR}/CMSIS/Core/Include"



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
	${MAKE}  -f nbproject/Makefile-pic32cm_gc_curiosity_pro.mk ${DISTDIR}/pthread_create_example.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32CM5112GC00100
MP_LINKER_FILE_OPTION=,--script="..\src\config\pic32cm_gc_curiosity_pro\PIC32CM5112GC00100.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/803290761/Ambient.o: ../src/click/Ambient/Ambient.c  .generated_files/flags/pic32cm_gc_curiosity_pro/eb5f4fe90ca66d0de93b104b65130d1f563eb705 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/803290761" 
	@${RM} ${OBJECTDIR}/_ext/803290761/Ambient.o.d 
	@${RM} ${OBJECTDIR}/_ext/803290761/Ambient.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/803290761/Ambient.o.d" -o ${OBJECTDIR}/_ext/803290761/Ambient.o ../src/click/Ambient/Ambient.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/949596075/Proximity3.o: ../src/click/Proximity3/Proximity3.c  .generated_files/flags/pic32cm_gc_curiosity_pro/fb03f64e4ce23b2a7472620570a3950bf286618f .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/949596075" 
	@${RM} ${OBJECTDIR}/_ext/949596075/Proximity3.o.d 
	@${RM} ${OBJECTDIR}/_ext/949596075/Proximity3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/949596075/Proximity3.o.d" -o ${OBJECTDIR}/_ext/949596075/Proximity3.o ../src/click/Proximity3/Proximity3.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/471585352/RcServo.o: ../src/click/Servo/RcServo.c  .generated_files/flags/pic32cm_gc_curiosity_pro/a1c375bab71135010e997ecd75bde4c6c8f3da5d .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/471585352" 
	@${RM} ${OBJECTDIR}/_ext/471585352/RcServo.o.d 
	@${RM} ${OBJECTDIR}/_ext/471585352/RcServo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/471585352/RcServo.o.d" -o ${OBJECTDIR}/_ext/471585352/RcServo.o ../src/click/Servo/RcServo.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1312294611/Bme280.o: ../src/click/Weather/Bme280.c  .generated_files/flags/pic32cm_gc_curiosity_pro/f3bb35b0158dd8e7f612b926082247bd8bd7f50 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1312294611" 
	@${RM} ${OBJECTDIR}/_ext/1312294611/Bme280.o.d 
	@${RM} ${OBJECTDIR}/_ext/1312294611/Bme280.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1312294611/Bme280.o.d" -o ${OBJECTDIR}/_ext/1312294611/Bme280.o ../src/click/Weather/Bme280.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1312294611/WeatherClick.o: ../src/click/Weather/WeatherClick.c  .generated_files/flags/pic32cm_gc_curiosity_pro/81e398b5dd73348fb2f17c22f8aa54c838db230 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1312294611" 
	@${RM} ${OBJECTDIR}/_ext/1312294611/WeatherClick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1312294611/WeatherClick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1312294611/WeatherClick.o.d" -o ${OBJECTDIR}/_ext/1312294611/WeatherClick.o ../src/click/Weather/WeatherClick.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/853750373/bsp.o: ../src/config/pic32cm_gc_curiosity_pro/bsp/bsp.c  .generated_files/flags/pic32cm_gc_curiosity_pro/6832097d9164cef3e267e450d36610a8247d37d3 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/853750373" 
	@${RM} ${OBJECTDIR}/_ext/853750373/bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/853750373/bsp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/853750373/bsp.o.d" -o ${OBJECTDIR}/_ext/853750373/bsp.o ../src/config/pic32cm_gc_curiosity_pro/bsp/bsp.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1448873790/drv_spi.o: ../src/config/pic32cm_gc_curiosity_pro/driver/spi/src/drv_spi.c  .generated_files/flags/pic32cm_gc_curiosity_pro/751558eae42b7ab0a88fa1cee6c76696f6823caf .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1448873790" 
	@${RM} ${OBJECTDIR}/_ext/1448873790/drv_spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1448873790/drv_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1448873790/drv_spi.o.d" -o ${OBJECTDIR}/_ext/1448873790/drv_spi.o ../src/config/pic32cm_gc_curiosity_pro/driver/spi/src/drv_spi.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1523867863/drv_usart.o: ../src/config/pic32cm_gc_curiosity_pro/driver/usart/src/drv_usart.c  .generated_files/flags/pic32cm_gc_curiosity_pro/1195a2103cf6ee3b90baa9a0ce3cb9f1c7c8cc73 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1523867863" 
	@${RM} ${OBJECTDIR}/_ext/1523867863/drv_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1523867863/drv_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1523867863/drv_usart.o.d" -o ${OBJECTDIR}/_ext/1523867863/drv_usart.o ../src/config/pic32cm_gc_curiosity_pro/driver/usart/src/drv_usart.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/714998607/plib_adc.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/adc/plib_adc.c  .generated_files/flags/pic32cm_gc_curiosity_pro/37b6319481c04d5d559215a4746d1e7a5a30ac7b .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/714998607" 
	@${RM} ${OBJECTDIR}/_ext/714998607/plib_adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/714998607/plib_adc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/714998607/plib_adc.o.d" -o ${OBJECTDIR}/_ext/714998607/plib_adc.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/adc/plib_adc.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/83206111/plib_clock.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/clock/plib_clock.c  .generated_files/flags/pic32cm_gc_curiosity_pro/63578ae39264427e2928e4e1d4d3d0f0752de672 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/83206111" 
	@${RM} ${OBJECTDIR}/_ext/83206111/plib_clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/83206111/plib_clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/83206111/plib_clock.o.d" -o ${OBJECTDIR}/_ext/83206111/plib_clock.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/clock/plib_clock.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/690022278/plib_dmac.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/dmac/plib_dmac.c  .generated_files/flags/pic32cm_gc_curiosity_pro/ecf50a87009d05af0d6247117a0f55625acd1c87 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/690022278" 
	@${RM} ${OBJECTDIR}/_ext/690022278/plib_dmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/690022278/plib_dmac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/690022278/plib_dmac.o.d" -o ${OBJECTDIR}/_ext/690022278/plib_dmac.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/dmac/plib_dmac.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/714994608/plib_eic.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/eic/plib_eic.c  .generated_files/flags/pic32cm_gc_curiosity_pro/aeae5247c8a0b96e7bbc10a2218db8099567c78b .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/714994608" 
	@${RM} ${OBJECTDIR}/_ext/714994608/plib_eic.o.d 
	@${RM} ${OBJECTDIR}/_ext/714994608/plib_eic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/714994608/plib_eic.o.d" -o ${OBJECTDIR}/_ext/714994608/plib_eic.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/eic/plib_eic.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/85355597/plib_evsys.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/evsys/plib_evsys.c  .generated_files/flags/pic32cm_gc_curiosity_pro/804e071e4196797a2f8bce190f2f2bdbb8ec5184 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/85355597" 
	@${RM} ${OBJECTDIR}/_ext/85355597/plib_evsys.o.d 
	@${RM} ${OBJECTDIR}/_ext/85355597/plib_evsys.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/85355597/plib_evsys.o.d" -o ${OBJECTDIR}/_ext/85355597/plib_evsys.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/evsys/plib_evsys.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/689715471/plib_nvic.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/nvic/plib_nvic.c  .generated_files/flags/pic32cm_gc_curiosity_pro/ff60ae3409d3caf32d2788e122db741e70f1f3ca .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/689715471" 
	@${RM} ${OBJECTDIR}/_ext/689715471/plib_nvic.o.d 
	@${RM} ${OBJECTDIR}/_ext/689715471/plib_nvic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/689715471/plib_nvic.o.d" -o ${OBJECTDIR}/_ext/689715471/plib_nvic.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/nvic/plib_nvic.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/392577996/plib_pm.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/pm/plib_pm.c  .generated_files/flags/pic32cm_gc_curiosity_pro/1f5a31fdb84aa101b202c6a828371ad5dd962ef8 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/392577996" 
	@${RM} ${OBJECTDIR}/_ext/392577996/plib_pm.o.d 
	@${RM} ${OBJECTDIR}/_ext/392577996/plib_pm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/392577996/plib_pm.o.d" -o ${OBJECTDIR}/_ext/392577996/plib_pm.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/pm/plib_pm.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/689662320/plib_port.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/port/plib_port.c  .generated_files/flags/pic32cm_gc_curiosity_pro/ea5c8137c7eaff83580fa27d2b5750c8681515df .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/689662320" 
	@${RM} ${OBJECTDIR}/_ext/689662320/plib_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/689662320/plib_port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/689662320/plib_port.o.d" -o ${OBJECTDIR}/_ext/689662320/plib_port.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/port/plib_port.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1527759270/plib_sercom1_i2c_master.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/sercom/i2c_master/plib_sercom1_i2c_master.c  .generated_files/flags/pic32cm_gc_curiosity_pro/ae99783a6f899f5c4a0a9b969928b3c386138dc7 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1527759270" 
	@${RM} ${OBJECTDIR}/_ext/1527759270/plib_sercom1_i2c_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/1527759270/plib_sercom1_i2c_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1527759270/plib_sercom1_i2c_master.o.d" -o ${OBJECTDIR}/_ext/1527759270/plib_sercom1_i2c_master.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/sercom/i2c_master/plib_sercom1_i2c_master.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1036524628/plib_sercom2_spi_master.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/sercom/spi_master/plib_sercom2_spi_master.c  .generated_files/flags/pic32cm_gc_curiosity_pro/652b28b377b769a98367e87869f238c5089edabb .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1036524628" 
	@${RM} ${OBJECTDIR}/_ext/1036524628/plib_sercom2_spi_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/1036524628/plib_sercom2_spi_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1036524628/plib_sercom2_spi_master.o.d" -o ${OBJECTDIR}/_ext/1036524628/plib_sercom2_spi_master.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/sercom/spi_master/plib_sercom2_spi_master.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/2020896858/plib_sercom3_usart.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/sercom/usart/plib_sercom3_usart.c  .generated_files/flags/pic32cm_gc_curiosity_pro/6dbaa6961626c4b72a1bdf0b52df019ef7734c37 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2020896858" 
	@${RM} ${OBJECTDIR}/_ext/2020896858/plib_sercom3_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/2020896858/plib_sercom3_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2020896858/plib_sercom3_usart.o.d" -o ${OBJECTDIR}/_ext/2020896858/plib_sercom3_usart.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/sercom/usart/plib_sercom3_usart.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/2020896858/plib_sercom4_usart.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/sercom/usart/plib_sercom4_usart.c  .generated_files/flags/pic32cm_gc_curiosity_pro/763cda70230ee50b871e66e7695efde1f63877dc .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2020896858" 
	@${RM} ${OBJECTDIR}/_ext/2020896858/plib_sercom4_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/2020896858/plib_sercom4_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2020896858/plib_sercom4_usart.o.d" -o ${OBJECTDIR}/_ext/2020896858/plib_sercom4_usart.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/sercom/usart/plib_sercom4_usart.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/714980379/plib_tcc0.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/tcc/plib_tcc0.c  .generated_files/flags/pic32cm_gc_curiosity_pro/98a2aa380b7ae6d6d59570f73605f15527448c6f .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/714980379" 
	@${RM} ${OBJECTDIR}/_ext/714980379/plib_tcc0.o.d 
	@${RM} ${OBJECTDIR}/_ext/714980379/plib_tcc0.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/714980379/plib_tcc0.o.d" -o ${OBJECTDIR}/_ext/714980379/plib_tcc0.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/tcc/plib_tcc0.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/714980379/plib_tcc1.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/tcc/plib_tcc1.c  .generated_files/flags/pic32cm_gc_curiosity_pro/e61d9739f95634e5a4e7af5c73283becf6f661b8 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/714980379" 
	@${RM} ${OBJECTDIR}/_ext/714980379/plib_tcc1.o.d 
	@${RM} ${OBJECTDIR}/_ext/714980379/plib_tcc1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/714980379/plib_tcc1.o.d" -o ${OBJECTDIR}/_ext/714980379/plib_tcc1.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/tcc/plib_tcc1.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/714980379/plib_tcc3.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/tcc/plib_tcc3.c  .generated_files/flags/pic32cm_gc_curiosity_pro/6637b79d106aec06f8ff63af0a9e42645e5f1ebe .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/714980379" 
	@${RM} ${OBJECTDIR}/_ext/714980379/plib_tcc3.o.d 
	@${RM} ${OBJECTDIR}/_ext/714980379/plib_tcc3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/714980379/plib_tcc3.o.d" -o ${OBJECTDIR}/_ext/714980379/plib_tcc3.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/tcc/plib_tcc3.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/2062074510/sdl_drv_common.o: ../src/config/pic32cm_gc_curiosity_pro/sdl/common/drv_common/sdl_drv_common.c  .generated_files/flags/pic32cm_gc_curiosity_pro/60f61de1a5ae6ea6d0a9da1a3fa9013145f3e85c .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2062074510" 
	@${RM} ${OBJECTDIR}/_ext/2062074510/sdl_drv_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/2062074510/sdl_drv_common.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2062074510/sdl_drv_common.o.d" -o ${OBJECTDIR}/_ext/2062074510/sdl_drv_common.o ../src/config/pic32cm_gc_curiosity_pro/sdl/common/drv_common/sdl_drv_common.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/8787811/sdl_common.o: ../src/config/pic32cm_gc_curiosity_pro/sdl/common/sdl_common.c  .generated_files/flags/pic32cm_gc_curiosity_pro/7c7281497bab2d39c1896c804b99fb29f2b1ce68 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/8787811" 
	@${RM} ${OBJECTDIR}/_ext/8787811/sdl_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/8787811/sdl_common.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8787811/sdl_common.o.d" -o ${OBJECTDIR}/_ext/8787811/sdl_common.o ../src/config/pic32cm_gc_curiosity_pro/sdl/common/sdl_common.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/731817458/sdl_drv_port.o: ../src/config/pic32cm_gc_curiosity_pro/sdl/port/drv_port/sdl_drv_port.c  .generated_files/flags/pic32cm_gc_curiosity_pro/e05fea382d99d9254062624a17c77d8503100c77 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/731817458" 
	@${RM} ${OBJECTDIR}/_ext/731817458/sdl_drv_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/731817458/sdl_drv_port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/731817458/sdl_drv_port.o.d" -o ${OBJECTDIR}/_ext/731817458/sdl_drv_port.o ../src/config/pic32cm_gc_curiosity_pro/sdl/port/drv_port/sdl_drv_port.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1496808455/sdl_port.o: ../src/config/pic32cm_gc_curiosity_pro/sdl/port/sdl_port.c  .generated_files/flags/pic32cm_gc_curiosity_pro/567ef510dec8fa40323aa32bc4c84fad9415ae67 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1496808455" 
	@${RM} ${OBJECTDIR}/_ext/1496808455/sdl_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1496808455/sdl_port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1496808455/sdl_port.o.d" -o ${OBJECTDIR}/_ext/1496808455/sdl_port.o ../src/config/pic32cm_gc_curiosity_pro/sdl/port/sdl_port.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/532237110/sdl_drv_systick.o: ../src/config/pic32cm_gc_curiosity_pro/sdl/systick/drv_systick/sdl_drv_systick.c  .generated_files/flags/pic32cm_gc_curiosity_pro/9609203e1a81304045af256209539f388e852da0 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/532237110" 
	@${RM} ${OBJECTDIR}/_ext/532237110/sdl_drv_systick.o.d 
	@${RM} ${OBJECTDIR}/_ext/532237110/sdl_drv_systick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/532237110/sdl_drv_systick.o.d" -o ${OBJECTDIR}/_ext/532237110/sdl_drv_systick.o ../src/config/pic32cm_gc_curiosity_pro/sdl/systick/drv_systick/sdl_drv_systick.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/99633435/xc32_monitor.o: ../src/config/pic32cm_gc_curiosity_pro/stdio/xc32_monitor.c  .generated_files/flags/pic32cm_gc_curiosity_pro/fe206361c771d6b742e4b8187f11874bbaaea69a .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/99633435" 
	@${RM} ${OBJECTDIR}/_ext/99633435/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/99633435/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/99633435/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/99633435/xc32_monitor.o ../src/config/pic32cm_gc_curiosity_pro/stdio/xc32_monitor.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1183487548/sys_dma.o: ../src/config/pic32cm_gc_curiosity_pro/system/dma/sys_dma.c  .generated_files/flags/pic32cm_gc_curiosity_pro/c7b2e8ddb56fb85bc1328a4692d215e0edf8890c .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1183487548" 
	@${RM} ${OBJECTDIR}/_ext/1183487548/sys_dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/1183487548/sys_dma.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1183487548/sys_dma.o.d" -o ${OBJECTDIR}/_ext/1183487548/sys_dma.o ../src/config/pic32cm_gc_curiosity_pro/system/dma/sys_dma.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1106506504/sys_int.o: ../src/config/pic32cm_gc_curiosity_pro/system/int/src/sys_int.c  .generated_files/flags/pic32cm_gc_curiosity_pro/15035d09b435e0aec34ab0ad8dd530ecf5a9deb7 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1106506504" 
	@${RM} ${OBJECTDIR}/_ext/1106506504/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1106506504/sys_int.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1106506504/sys_int.o.d" -o ${OBJECTDIR}/_ext/1106506504/sys_int.o ../src/config/pic32cm_gc_curiosity_pro/system/int/src/sys_int.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1291214997/libc_syscalls.o: ../src/config/pic32cm_gc_curiosity_pro/libc_syscalls.c  .generated_files/flags/pic32cm_gc_curiosity_pro/c9383f12f7faa46fb2a540b9d8e82ead314b84f5 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1291214997" 
	@${RM} ${OBJECTDIR}/_ext/1291214997/libc_syscalls.o.d 
	@${RM} ${OBJECTDIR}/_ext/1291214997/libc_syscalls.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1291214997/libc_syscalls.o.d" -o ${OBJECTDIR}/_ext/1291214997/libc_syscalls.o ../src/config/pic32cm_gc_curiosity_pro/libc_syscalls.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1291214997/initialization.o: ../src/config/pic32cm_gc_curiosity_pro/initialization.c  .generated_files/flags/pic32cm_gc_curiosity_pro/326a663b891f75a0d0eb36ccdf044567ff2aa923 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1291214997" 
	@${RM} ${OBJECTDIR}/_ext/1291214997/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1291214997/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1291214997/initialization.o.d" -o ${OBJECTDIR}/_ext/1291214997/initialization.o ../src/config/pic32cm_gc_curiosity_pro/initialization.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1291214997/exceptions.o: ../src/config/pic32cm_gc_curiosity_pro/exceptions.c  .generated_files/flags/pic32cm_gc_curiosity_pro/3bf6ca5c989de01e27687775af0be98f291e8000 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1291214997" 
	@${RM} ${OBJECTDIR}/_ext/1291214997/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1291214997/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1291214997/exceptions.o.d" -o ${OBJECTDIR}/_ext/1291214997/exceptions.o ../src/config/pic32cm_gc_curiosity_pro/exceptions.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1291214997/interrupts.o: ../src/config/pic32cm_gc_curiosity_pro/interrupts.c  .generated_files/flags/pic32cm_gc_curiosity_pro/5425e36b4ac78e48079f1bca6321487f38a3f5e1 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1291214997" 
	@${RM} ${OBJECTDIR}/_ext/1291214997/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1291214997/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1291214997/interrupts.o.d" -o ${OBJECTDIR}/_ext/1291214997/interrupts.o ../src/config/pic32cm_gc_curiosity_pro/interrupts.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1291214997/startup_xc32.o: ../src/config/pic32cm_gc_curiosity_pro/startup_xc32.c  .generated_files/flags/pic32cm_gc_curiosity_pro/1e1c96f15333ab772a63867a0766e0c13e225137 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1291214997" 
	@${RM} ${OBJECTDIR}/_ext/1291214997/startup_xc32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1291214997/startup_xc32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1291214997/startup_xc32.o.d" -o ${OBJECTDIR}/_ext/1291214997/startup_xc32.o ../src/config/pic32cm_gc_curiosity_pro/startup_xc32.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/603174789/pwm_driver.o: ../src/pwm_driver/pwm_driver.c  .generated_files/flags/pic32cm_gc_curiosity_pro/8ffca5aad79018b4efe439738e6eeb3b9ad18e8e .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/603174789" 
	@${RM} ${OBJECTDIR}/_ext/603174789/pwm_driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/603174789/pwm_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/603174789/pwm_driver.o.d" -o ${OBJECTDIR}/_ext/603174789/pwm_driver.o ../src/pwm_driver/pwm_driver.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/193257301/spi_async_driver.o: ../src/spi_driver/spi_async_driver.c  .generated_files/flags/pic32cm_gc_curiosity_pro/a3930c32ae6c3d883a4e01b8e6ad073f260b04eb .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/193257301" 
	@${RM} ${OBJECTDIR}/_ext/193257301/spi_async_driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/193257301/spi_async_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/193257301/spi_async_driver.o.d" -o ${OBJECTDIR}/_ext/193257301/spi_async_driver.o ../src/spi_driver/spi_async_driver.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/platform_setup.o: ../src/platform_setup.c  .generated_files/flags/pic32cm_gc_curiosity_pro/558ea00b8a3fb45a59eebbbfbb7c5a9ba1ee825b .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/platform_setup.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/platform_setup.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/platform_setup.o.d" -o ${OBJECTDIR}/_ext/1360937237/platform_setup.o ../src/platform_setup.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/pthread_create_example.o: ../src/pthread_create_example.c  .generated_files/flags/pic32cm_gc_curiosity_pro/8d0699ad02ba32f40e9a04a43b4b8b807caff5f3 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pthread_create_example.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pthread_create_example.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/pthread_create_example.o.d" -o ${OBJECTDIR}/_ext/1360937237/pthread_create_example.o ../src/pthread_create_example.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/714996767/plib_can0.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/can/plib_can0.c  .generated_files/flags/pic32cm_gc_curiosity_pro/63e020926363a315cced209ee1aa96d252c69177 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/714996767" 
	@${RM} ${OBJECTDIR}/_ext/714996767/plib_can0.o.d 
	@${RM} ${OBJECTDIR}/_ext/714996767/plib_can0.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/714996767/plib_can0.o.d" -o ${OBJECTDIR}/_ext/714996767/plib_can0.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/can/plib_can0.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/508636337/can_driver.o: ../src/can_driver/can_driver.c  .generated_files/flags/pic32cm_gc_curiosity_pro/8230166d4b2406999095c87f71d306892e9865a4 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/508636337" 
	@${RM} ${OBJECTDIR}/_ext/508636337/can_driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/508636337/can_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/508636337/can_driver.o.d" -o ${OBJECTDIR}/_ext/508636337/can_driver.o ../src/can_driver/can_driver.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
else
${OBJECTDIR}/_ext/803290761/Ambient.o: ../src/click/Ambient/Ambient.c  .generated_files/flags/pic32cm_gc_curiosity_pro/3ec6dec45ca523dae79b4e3834151d32cfd4a0e5 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/803290761" 
	@${RM} ${OBJECTDIR}/_ext/803290761/Ambient.o.d 
	@${RM} ${OBJECTDIR}/_ext/803290761/Ambient.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/803290761/Ambient.o.d" -o ${OBJECTDIR}/_ext/803290761/Ambient.o ../src/click/Ambient/Ambient.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/949596075/Proximity3.o: ../src/click/Proximity3/Proximity3.c  .generated_files/flags/pic32cm_gc_curiosity_pro/9e663c3c3499be4afc9b03cfcba2448266d8452 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/949596075" 
	@${RM} ${OBJECTDIR}/_ext/949596075/Proximity3.o.d 
	@${RM} ${OBJECTDIR}/_ext/949596075/Proximity3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/949596075/Proximity3.o.d" -o ${OBJECTDIR}/_ext/949596075/Proximity3.o ../src/click/Proximity3/Proximity3.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/471585352/RcServo.o: ../src/click/Servo/RcServo.c  .generated_files/flags/pic32cm_gc_curiosity_pro/61d12fe68ef055febbc3843165951d4807386938 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/471585352" 
	@${RM} ${OBJECTDIR}/_ext/471585352/RcServo.o.d 
	@${RM} ${OBJECTDIR}/_ext/471585352/RcServo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/471585352/RcServo.o.d" -o ${OBJECTDIR}/_ext/471585352/RcServo.o ../src/click/Servo/RcServo.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1312294611/Bme280.o: ../src/click/Weather/Bme280.c  .generated_files/flags/pic32cm_gc_curiosity_pro/6bdef62dc29fc1127dd73dd85ec095f8eb9b42d6 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1312294611" 
	@${RM} ${OBJECTDIR}/_ext/1312294611/Bme280.o.d 
	@${RM} ${OBJECTDIR}/_ext/1312294611/Bme280.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1312294611/Bme280.o.d" -o ${OBJECTDIR}/_ext/1312294611/Bme280.o ../src/click/Weather/Bme280.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1312294611/WeatherClick.o: ../src/click/Weather/WeatherClick.c  .generated_files/flags/pic32cm_gc_curiosity_pro/c1f01babdc180fdb9fcf01cc9a05264b392329b .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1312294611" 
	@${RM} ${OBJECTDIR}/_ext/1312294611/WeatherClick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1312294611/WeatherClick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1312294611/WeatherClick.o.d" -o ${OBJECTDIR}/_ext/1312294611/WeatherClick.o ../src/click/Weather/WeatherClick.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/853750373/bsp.o: ../src/config/pic32cm_gc_curiosity_pro/bsp/bsp.c  .generated_files/flags/pic32cm_gc_curiosity_pro/a09e21259cd9699a9d81e1f947f290e1756a092b .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/853750373" 
	@${RM} ${OBJECTDIR}/_ext/853750373/bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/853750373/bsp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/853750373/bsp.o.d" -o ${OBJECTDIR}/_ext/853750373/bsp.o ../src/config/pic32cm_gc_curiosity_pro/bsp/bsp.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1448873790/drv_spi.o: ../src/config/pic32cm_gc_curiosity_pro/driver/spi/src/drv_spi.c  .generated_files/flags/pic32cm_gc_curiosity_pro/59d477789280ee69b3c91a621e23f16ed336d918 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1448873790" 
	@${RM} ${OBJECTDIR}/_ext/1448873790/drv_spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1448873790/drv_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1448873790/drv_spi.o.d" -o ${OBJECTDIR}/_ext/1448873790/drv_spi.o ../src/config/pic32cm_gc_curiosity_pro/driver/spi/src/drv_spi.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1523867863/drv_usart.o: ../src/config/pic32cm_gc_curiosity_pro/driver/usart/src/drv_usart.c  .generated_files/flags/pic32cm_gc_curiosity_pro/8bf4fc64b8623268edbf47977aa7153201e279c3 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1523867863" 
	@${RM} ${OBJECTDIR}/_ext/1523867863/drv_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1523867863/drv_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1523867863/drv_usart.o.d" -o ${OBJECTDIR}/_ext/1523867863/drv_usart.o ../src/config/pic32cm_gc_curiosity_pro/driver/usart/src/drv_usart.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/714998607/plib_adc.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/adc/plib_adc.c  .generated_files/flags/pic32cm_gc_curiosity_pro/ec2d0aa8a9ffda6b3fec4fe6f8e046ac167e6030 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/714998607" 
	@${RM} ${OBJECTDIR}/_ext/714998607/plib_adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/714998607/plib_adc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/714998607/plib_adc.o.d" -o ${OBJECTDIR}/_ext/714998607/plib_adc.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/adc/plib_adc.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/83206111/plib_clock.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/clock/plib_clock.c  .generated_files/flags/pic32cm_gc_curiosity_pro/6ca21b17ebe63a3083979ff47f3cb2efb9a68d26 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/83206111" 
	@${RM} ${OBJECTDIR}/_ext/83206111/plib_clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/83206111/plib_clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/83206111/plib_clock.o.d" -o ${OBJECTDIR}/_ext/83206111/plib_clock.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/clock/plib_clock.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/690022278/plib_dmac.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/dmac/plib_dmac.c  .generated_files/flags/pic32cm_gc_curiosity_pro/a7648a5d59298e47e19f703d56c37c7672842e3a .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/690022278" 
	@${RM} ${OBJECTDIR}/_ext/690022278/plib_dmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/690022278/plib_dmac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/690022278/plib_dmac.o.d" -o ${OBJECTDIR}/_ext/690022278/plib_dmac.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/dmac/plib_dmac.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/714994608/plib_eic.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/eic/plib_eic.c  .generated_files/flags/pic32cm_gc_curiosity_pro/fb782002abcf29528b6a8adaf50dd2f2f2862d83 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/714994608" 
	@${RM} ${OBJECTDIR}/_ext/714994608/plib_eic.o.d 
	@${RM} ${OBJECTDIR}/_ext/714994608/plib_eic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/714994608/plib_eic.o.d" -o ${OBJECTDIR}/_ext/714994608/plib_eic.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/eic/plib_eic.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/85355597/plib_evsys.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/evsys/plib_evsys.c  .generated_files/flags/pic32cm_gc_curiosity_pro/87475fc238017226e88cc9de6087b2166bdeb1fb .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/85355597" 
	@${RM} ${OBJECTDIR}/_ext/85355597/plib_evsys.o.d 
	@${RM} ${OBJECTDIR}/_ext/85355597/plib_evsys.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/85355597/plib_evsys.o.d" -o ${OBJECTDIR}/_ext/85355597/plib_evsys.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/evsys/plib_evsys.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/689715471/plib_nvic.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/nvic/plib_nvic.c  .generated_files/flags/pic32cm_gc_curiosity_pro/cab2d8d712e584ea7002920ca751e370b6333596 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/689715471" 
	@${RM} ${OBJECTDIR}/_ext/689715471/plib_nvic.o.d 
	@${RM} ${OBJECTDIR}/_ext/689715471/plib_nvic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/689715471/plib_nvic.o.d" -o ${OBJECTDIR}/_ext/689715471/plib_nvic.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/nvic/plib_nvic.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/392577996/plib_pm.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/pm/plib_pm.c  .generated_files/flags/pic32cm_gc_curiosity_pro/7f0fd8b32eb1c374b0911ff65900367bdcbd7f61 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/392577996" 
	@${RM} ${OBJECTDIR}/_ext/392577996/plib_pm.o.d 
	@${RM} ${OBJECTDIR}/_ext/392577996/plib_pm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/392577996/plib_pm.o.d" -o ${OBJECTDIR}/_ext/392577996/plib_pm.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/pm/plib_pm.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/689662320/plib_port.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/port/plib_port.c  .generated_files/flags/pic32cm_gc_curiosity_pro/2b6d425ba1218c16227b458c3330c6977fe47b4c .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/689662320" 
	@${RM} ${OBJECTDIR}/_ext/689662320/plib_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/689662320/plib_port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/689662320/plib_port.o.d" -o ${OBJECTDIR}/_ext/689662320/plib_port.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/port/plib_port.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1527759270/plib_sercom1_i2c_master.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/sercom/i2c_master/plib_sercom1_i2c_master.c  .generated_files/flags/pic32cm_gc_curiosity_pro/a04453c1bf104e566b605ea5b17c00967b5fbb42 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1527759270" 
	@${RM} ${OBJECTDIR}/_ext/1527759270/plib_sercom1_i2c_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/1527759270/plib_sercom1_i2c_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1527759270/plib_sercom1_i2c_master.o.d" -o ${OBJECTDIR}/_ext/1527759270/plib_sercom1_i2c_master.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/sercom/i2c_master/plib_sercom1_i2c_master.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1036524628/plib_sercom2_spi_master.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/sercom/spi_master/plib_sercom2_spi_master.c  .generated_files/flags/pic32cm_gc_curiosity_pro/b63c42eae6ca81b07af0d777c973e6288248929 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1036524628" 
	@${RM} ${OBJECTDIR}/_ext/1036524628/plib_sercom2_spi_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/1036524628/plib_sercom2_spi_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1036524628/plib_sercom2_spi_master.o.d" -o ${OBJECTDIR}/_ext/1036524628/plib_sercom2_spi_master.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/sercom/spi_master/plib_sercom2_spi_master.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/2020896858/plib_sercom3_usart.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/sercom/usart/plib_sercom3_usart.c  .generated_files/flags/pic32cm_gc_curiosity_pro/806a347cc7befb4fc6f1c9464d5eef0f9189da08 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2020896858" 
	@${RM} ${OBJECTDIR}/_ext/2020896858/plib_sercom3_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/2020896858/plib_sercom3_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2020896858/plib_sercom3_usart.o.d" -o ${OBJECTDIR}/_ext/2020896858/plib_sercom3_usart.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/sercom/usart/plib_sercom3_usart.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/2020896858/plib_sercom4_usart.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/sercom/usart/plib_sercom4_usart.c  .generated_files/flags/pic32cm_gc_curiosity_pro/162efb7d9017e4b00751baa92e93252c0c790fc1 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2020896858" 
	@${RM} ${OBJECTDIR}/_ext/2020896858/plib_sercom4_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/2020896858/plib_sercom4_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2020896858/plib_sercom4_usart.o.d" -o ${OBJECTDIR}/_ext/2020896858/plib_sercom4_usart.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/sercom/usart/plib_sercom4_usart.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/714980379/plib_tcc0.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/tcc/plib_tcc0.c  .generated_files/flags/pic32cm_gc_curiosity_pro/4b649dfc0952ae2544cd481a3490184fe241af4a .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/714980379" 
	@${RM} ${OBJECTDIR}/_ext/714980379/plib_tcc0.o.d 
	@${RM} ${OBJECTDIR}/_ext/714980379/plib_tcc0.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/714980379/plib_tcc0.o.d" -o ${OBJECTDIR}/_ext/714980379/plib_tcc0.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/tcc/plib_tcc0.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/714980379/plib_tcc1.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/tcc/plib_tcc1.c  .generated_files/flags/pic32cm_gc_curiosity_pro/1ffbbddb462ef4dd02dc4352a16f093e4784ebea .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/714980379" 
	@${RM} ${OBJECTDIR}/_ext/714980379/plib_tcc1.o.d 
	@${RM} ${OBJECTDIR}/_ext/714980379/plib_tcc1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/714980379/plib_tcc1.o.d" -o ${OBJECTDIR}/_ext/714980379/plib_tcc1.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/tcc/plib_tcc1.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/714980379/plib_tcc3.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/tcc/plib_tcc3.c  .generated_files/flags/pic32cm_gc_curiosity_pro/a3f99963731ccfa245d583dab882f49d9bc80736 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/714980379" 
	@${RM} ${OBJECTDIR}/_ext/714980379/plib_tcc3.o.d 
	@${RM} ${OBJECTDIR}/_ext/714980379/plib_tcc3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/714980379/plib_tcc3.o.d" -o ${OBJECTDIR}/_ext/714980379/plib_tcc3.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/tcc/plib_tcc3.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/2062074510/sdl_drv_common.o: ../src/config/pic32cm_gc_curiosity_pro/sdl/common/drv_common/sdl_drv_common.c  .generated_files/flags/pic32cm_gc_curiosity_pro/1c6b6052d156f0dab255f94e190ee19ef1b32928 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2062074510" 
	@${RM} ${OBJECTDIR}/_ext/2062074510/sdl_drv_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/2062074510/sdl_drv_common.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2062074510/sdl_drv_common.o.d" -o ${OBJECTDIR}/_ext/2062074510/sdl_drv_common.o ../src/config/pic32cm_gc_curiosity_pro/sdl/common/drv_common/sdl_drv_common.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/8787811/sdl_common.o: ../src/config/pic32cm_gc_curiosity_pro/sdl/common/sdl_common.c  .generated_files/flags/pic32cm_gc_curiosity_pro/a1adc7a21edd0d5dfde2dff406b79076daf9fb79 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/8787811" 
	@${RM} ${OBJECTDIR}/_ext/8787811/sdl_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/8787811/sdl_common.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8787811/sdl_common.o.d" -o ${OBJECTDIR}/_ext/8787811/sdl_common.o ../src/config/pic32cm_gc_curiosity_pro/sdl/common/sdl_common.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/731817458/sdl_drv_port.o: ../src/config/pic32cm_gc_curiosity_pro/sdl/port/drv_port/sdl_drv_port.c  .generated_files/flags/pic32cm_gc_curiosity_pro/4319e2838c20a59f1a1a34227373762533c06a39 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/731817458" 
	@${RM} ${OBJECTDIR}/_ext/731817458/sdl_drv_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/731817458/sdl_drv_port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/731817458/sdl_drv_port.o.d" -o ${OBJECTDIR}/_ext/731817458/sdl_drv_port.o ../src/config/pic32cm_gc_curiosity_pro/sdl/port/drv_port/sdl_drv_port.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1496808455/sdl_port.o: ../src/config/pic32cm_gc_curiosity_pro/sdl/port/sdl_port.c  .generated_files/flags/pic32cm_gc_curiosity_pro/c82cf62a716c30b303c0aa193f05d848a9debafb .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1496808455" 
	@${RM} ${OBJECTDIR}/_ext/1496808455/sdl_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1496808455/sdl_port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1496808455/sdl_port.o.d" -o ${OBJECTDIR}/_ext/1496808455/sdl_port.o ../src/config/pic32cm_gc_curiosity_pro/sdl/port/sdl_port.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/532237110/sdl_drv_systick.o: ../src/config/pic32cm_gc_curiosity_pro/sdl/systick/drv_systick/sdl_drv_systick.c  .generated_files/flags/pic32cm_gc_curiosity_pro/421b0a38028afec46ef86ab1029f58b982656abf .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/532237110" 
	@${RM} ${OBJECTDIR}/_ext/532237110/sdl_drv_systick.o.d 
	@${RM} ${OBJECTDIR}/_ext/532237110/sdl_drv_systick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/532237110/sdl_drv_systick.o.d" -o ${OBJECTDIR}/_ext/532237110/sdl_drv_systick.o ../src/config/pic32cm_gc_curiosity_pro/sdl/systick/drv_systick/sdl_drv_systick.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/99633435/xc32_monitor.o: ../src/config/pic32cm_gc_curiosity_pro/stdio/xc32_monitor.c  .generated_files/flags/pic32cm_gc_curiosity_pro/b5afca197a2be8179e633b7e7b102d8d73079704 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/99633435" 
	@${RM} ${OBJECTDIR}/_ext/99633435/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/99633435/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/99633435/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/99633435/xc32_monitor.o ../src/config/pic32cm_gc_curiosity_pro/stdio/xc32_monitor.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1183487548/sys_dma.o: ../src/config/pic32cm_gc_curiosity_pro/system/dma/sys_dma.c  .generated_files/flags/pic32cm_gc_curiosity_pro/b9de0eeb1eefb4c1979bee16df663f5a1f6359ed .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1183487548" 
	@${RM} ${OBJECTDIR}/_ext/1183487548/sys_dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/1183487548/sys_dma.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1183487548/sys_dma.o.d" -o ${OBJECTDIR}/_ext/1183487548/sys_dma.o ../src/config/pic32cm_gc_curiosity_pro/system/dma/sys_dma.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1106506504/sys_int.o: ../src/config/pic32cm_gc_curiosity_pro/system/int/src/sys_int.c  .generated_files/flags/pic32cm_gc_curiosity_pro/c20a0ccbaecf8c44c43489f2fd2f4551771702b5 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1106506504" 
	@${RM} ${OBJECTDIR}/_ext/1106506504/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1106506504/sys_int.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1106506504/sys_int.o.d" -o ${OBJECTDIR}/_ext/1106506504/sys_int.o ../src/config/pic32cm_gc_curiosity_pro/system/int/src/sys_int.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1291214997/libc_syscalls.o: ../src/config/pic32cm_gc_curiosity_pro/libc_syscalls.c  .generated_files/flags/pic32cm_gc_curiosity_pro/4d59d1b8328cc19344fd8779e2b5ced33a0ae940 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1291214997" 
	@${RM} ${OBJECTDIR}/_ext/1291214997/libc_syscalls.o.d 
	@${RM} ${OBJECTDIR}/_ext/1291214997/libc_syscalls.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1291214997/libc_syscalls.o.d" -o ${OBJECTDIR}/_ext/1291214997/libc_syscalls.o ../src/config/pic32cm_gc_curiosity_pro/libc_syscalls.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1291214997/initialization.o: ../src/config/pic32cm_gc_curiosity_pro/initialization.c  .generated_files/flags/pic32cm_gc_curiosity_pro/22f4b3d3e82edd440f8d613777bc4105fca40da3 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1291214997" 
	@${RM} ${OBJECTDIR}/_ext/1291214997/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1291214997/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1291214997/initialization.o.d" -o ${OBJECTDIR}/_ext/1291214997/initialization.o ../src/config/pic32cm_gc_curiosity_pro/initialization.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1291214997/exceptions.o: ../src/config/pic32cm_gc_curiosity_pro/exceptions.c  .generated_files/flags/pic32cm_gc_curiosity_pro/c29c7629adef21fd1b97dcc523968c2364cd72bf .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1291214997" 
	@${RM} ${OBJECTDIR}/_ext/1291214997/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1291214997/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1291214997/exceptions.o.d" -o ${OBJECTDIR}/_ext/1291214997/exceptions.o ../src/config/pic32cm_gc_curiosity_pro/exceptions.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1291214997/interrupts.o: ../src/config/pic32cm_gc_curiosity_pro/interrupts.c  .generated_files/flags/pic32cm_gc_curiosity_pro/dd8fa0e9599c47c9430cbd44546a02158d8a168f .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1291214997" 
	@${RM} ${OBJECTDIR}/_ext/1291214997/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1291214997/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1291214997/interrupts.o.d" -o ${OBJECTDIR}/_ext/1291214997/interrupts.o ../src/config/pic32cm_gc_curiosity_pro/interrupts.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1291214997/startup_xc32.o: ../src/config/pic32cm_gc_curiosity_pro/startup_xc32.c  .generated_files/flags/pic32cm_gc_curiosity_pro/26abf996ada2373027fe382b60c102e72f8c0df .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1291214997" 
	@${RM} ${OBJECTDIR}/_ext/1291214997/startup_xc32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1291214997/startup_xc32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1291214997/startup_xc32.o.d" -o ${OBJECTDIR}/_ext/1291214997/startup_xc32.o ../src/config/pic32cm_gc_curiosity_pro/startup_xc32.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/603174789/pwm_driver.o: ../src/pwm_driver/pwm_driver.c  .generated_files/flags/pic32cm_gc_curiosity_pro/ef817a98aae4290a67a5913e3e4c272297ccf395 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/603174789" 
	@${RM} ${OBJECTDIR}/_ext/603174789/pwm_driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/603174789/pwm_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/603174789/pwm_driver.o.d" -o ${OBJECTDIR}/_ext/603174789/pwm_driver.o ../src/pwm_driver/pwm_driver.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/193257301/spi_async_driver.o: ../src/spi_driver/spi_async_driver.c  .generated_files/flags/pic32cm_gc_curiosity_pro/bb938be56e8d5c9ab1e27d3d937dd759264fc7a1 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/193257301" 
	@${RM} ${OBJECTDIR}/_ext/193257301/spi_async_driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/193257301/spi_async_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/193257301/spi_async_driver.o.d" -o ${OBJECTDIR}/_ext/193257301/spi_async_driver.o ../src/spi_driver/spi_async_driver.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/platform_setup.o: ../src/platform_setup.c  .generated_files/flags/pic32cm_gc_curiosity_pro/cf2758818985c6abc0a7d1f03341d8e0d5f3d185 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/platform_setup.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/platform_setup.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/platform_setup.o.d" -o ${OBJECTDIR}/_ext/1360937237/platform_setup.o ../src/platform_setup.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/pthread_create_example.o: ../src/pthread_create_example.c  .generated_files/flags/pic32cm_gc_curiosity_pro/722926b75d464c58dce851435ec6c3fffacc0dd5 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pthread_create_example.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/pthread_create_example.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/pthread_create_example.o.d" -o ${OBJECTDIR}/_ext/1360937237/pthread_create_example.o ../src/pthread_create_example.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/714996767/plib_can0.o: ../src/config/pic32cm_gc_curiosity_pro/peripheral/can/plib_can0.c  .generated_files/flags/pic32cm_gc_curiosity_pro/8541bea49fbcad1d86cad09b61f70c78dd4f0c2b .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/714996767" 
	@${RM} ${OBJECTDIR}/_ext/714996767/plib_can0.o.d 
	@${RM} ${OBJECTDIR}/_ext/714996767/plib_can0.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/714996767/plib_can0.o.d" -o ${OBJECTDIR}/_ext/714996767/plib_can0.o ../src/config/pic32cm_gc_curiosity_pro/peripheral/can/plib_can0.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/508636337/can_driver.o: ../src/can_driver/can_driver.c  .generated_files/flags/pic32cm_gc_curiosity_pro/a3991525aeb2289b1ea110320972b359c4995129 .generated_files/flags/pic32cm_gc_curiosity_pro/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/508636337" 
	@${RM} ${OBJECTDIR}/_ext/508636337/can_driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/508636337/can_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/pic32cm_gc_curiosity_pro" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5112GC00100_DFP" -I"../../../px5_rtos" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/508636337/can_driver.o.d" -o ${OBJECTDIR}/_ext/508636337/can_driver.o ../src/can_driver/can_driver.c    -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/pthread_create_example.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../src/config/pic32cm_gc_curiosity_pro/PIC32CM5112GC00100.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-device-startup-code -o ${DISTDIR}/pthread_create_example.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=512,--defsym=_min_stack_size=1024,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",-DVECTOR_REGION=boot_rom,--memorysummary,${DISTDIR}/memoryfile.xml,../../../px5_rtos/px5.o,../../../px5_rtos/px5_binding.o -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/pthread_create_example.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../src/config/pic32cm_gc_curiosity_pro/PIC32CM5112GC00100.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-device-startup-code -o ${DISTDIR}/pthread_create_example.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_pic32cm_gc_curiosity_pro=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=512,--defsym=_min_stack_size=1024,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",-DVECTOR_REGION=boot_rom,--memorysummary,${DISTDIR}/memoryfile.xml,../../../px5_rtos/px5.o,../../../px5_rtos/px5_binding.o -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/pthread_create_example.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
