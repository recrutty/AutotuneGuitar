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
ifeq "$(wildcard nbproject/Makefile-local-dspic33ep256mu806.mk)" "nbproject/Makefile-local-dspic33ep256mu806.mk"
include nbproject/Makefile-local-dspic33ep256mu806.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=dspic33ep256mu806
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/fft_dsplib.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/fft_dsplib.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../src/twiddle_factors.c ../src/inputsignal_square1khz.c ../src/system_config/exp16/dspic33ep256gp506/main_fft_example.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1360937237/twiddle_factors.o ${OBJECTDIR}/_ext/1360937237/inputsignal_square1khz.o ${OBJECTDIR}/_ext/1509574111/main_fft_example.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1360937237/twiddle_factors.o.d ${OBJECTDIR}/_ext/1360937237/inputsignal_square1khz.o.d ${OBJECTDIR}/_ext/1509574111/main_fft_example.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1360937237/twiddle_factors.o ${OBJECTDIR}/_ext/1360937237/inputsignal_square1khz.o ${OBJECTDIR}/_ext/1509574111/main_fft_example.o

# Source Files
SOURCEFILES=../src/twiddle_factors.c ../src/inputsignal_square1khz.c ../src/system_config/exp16/dspic33ep256gp506/main_fft_example.c


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
	${MAKE}  -f nbproject/Makefile-dspic33ep256mu806.mk dist/${CND_CONF}/${IMAGE_TYPE}/fft_dsplib.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP256MU806
MP_LINKER_FILE_OPTION=,--script=p33EP256MU806.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1360937237/twiddle_factors.o: ../src/twiddle_factors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/twiddle_factors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/twiddle_factors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/twiddle_factors.c  -o ${OBJECTDIR}/_ext/1360937237/twiddle_factors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/twiddle_factors.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -mno-eds-warn  -omf=elf -DXPRJ_dspic33ep256mu806=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I"../src" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/twiddle_factors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/inputsignal_square1khz.o: ../src/inputsignal_square1khz.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/inputsignal_square1khz.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/inputsignal_square1khz.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/inputsignal_square1khz.c  -o ${OBJECTDIR}/_ext/1360937237/inputsignal_square1khz.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/inputsignal_square1khz.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -mno-eds-warn  -omf=elf -DXPRJ_dspic33ep256mu806=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I"../src" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/inputsignal_square1khz.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1509574111/main_fft_example.o: ../src/system_config/exp16/dspic33ep256gp506/main_fft_example.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1509574111" 
	@${RM} ${OBJECTDIR}/_ext/1509574111/main_fft_example.o.d 
	@${RM} ${OBJECTDIR}/_ext/1509574111/main_fft_example.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/system_config/exp16/dspic33ep256gp506/main_fft_example.c  -o ${OBJECTDIR}/_ext/1509574111/main_fft_example.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1509574111/main_fft_example.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -mno-eds-warn  -omf=elf -DXPRJ_dspic33ep256mu806=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I"../src" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1509574111/main_fft_example.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1360937237/twiddle_factors.o: ../src/twiddle_factors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/twiddle_factors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/twiddle_factors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/twiddle_factors.c  -o ${OBJECTDIR}/_ext/1360937237/twiddle_factors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/twiddle_factors.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_dspic33ep256mu806=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I"../src" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/twiddle_factors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360937237/inputsignal_square1khz.o: ../src/inputsignal_square1khz.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/inputsignal_square1khz.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/inputsignal_square1khz.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/inputsignal_square1khz.c  -o ${OBJECTDIR}/_ext/1360937237/inputsignal_square1khz.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/inputsignal_square1khz.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_dspic33ep256mu806=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I"../src" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/inputsignal_square1khz.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1509574111/main_fft_example.o: ../src/system_config/exp16/dspic33ep256gp506/main_fft_example.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1509574111" 
	@${RM} ${OBJECTDIR}/_ext/1509574111/main_fft_example.o.d 
	@${RM} ${OBJECTDIR}/_ext/1509574111/main_fft_example.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../src/system_config/exp16/dspic33ep256gp506/main_fft_example.c  -o ${OBJECTDIR}/_ext/1509574111/main_fft_example.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1509574111/main_fft_example.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_dspic33ep256mu806=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I"../src" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1509574111/main_fft_example.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/fft_dsplib.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/fft_dsplib.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -omf=elf -DXPRJ_dspic33ep256mu806=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)      -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library=dsp,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/fft_dsplib.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/fft_dsplib.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_dspic33ep256mu806=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library=dsp,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/fft_dsplib.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/dspic33ep256mu806
	${RM} -r dist/dspic33ep256mu806

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
