#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/CdA.main.o \
	${OBJECTDIR}/Classes/AL.o \
	${OBJECTDIR}/Classes/GL.o \
	${OBJECTDIR}/Classes/Util.o \
	${OBJECTDIR}/Libs/soil/SOIL.o \
	${OBJECTDIR}/Libs/soil/image_DXT.o \
	${OBJECTDIR}/Libs/soil/image_helper.o \
	${OBJECTDIR}/Libs/soil/stb_image_aug.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cefetinhodoapocalipse

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cefetinhodoapocalipse: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cefetinhodoapocalipse ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/CdA.main.o: CdA.main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CdA.main.o CdA.main.cpp

${OBJECTDIR}/Classes/AL.o: Classes/AL.cpp 
	${MKDIR} -p ${OBJECTDIR}/Classes
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Classes/AL.o Classes/AL.cpp

${OBJECTDIR}/Classes/GL.o: Classes/GL.cpp 
	${MKDIR} -p ${OBJECTDIR}/Classes
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Classes/GL.o Classes/GL.cpp

${OBJECTDIR}/Classes/Util.o: Classes/Util.cpp 
	${MKDIR} -p ${OBJECTDIR}/Classes
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Classes/Util.o Classes/Util.cpp

${OBJECTDIR}/Libs/soil/SOIL.o: Libs/soil/SOIL.c 
	${MKDIR} -p ${OBJECTDIR}/Libs/soil
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Libs/soil/SOIL.o Libs/soil/SOIL.c

${OBJECTDIR}/Libs/soil/image_DXT.o: Libs/soil/image_DXT.c 
	${MKDIR} -p ${OBJECTDIR}/Libs/soil
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Libs/soil/image_DXT.o Libs/soil/image_DXT.c

${OBJECTDIR}/Libs/soil/image_helper.o: Libs/soil/image_helper.c 
	${MKDIR} -p ${OBJECTDIR}/Libs/soil
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Libs/soil/image_helper.o Libs/soil/image_helper.c

${OBJECTDIR}/Libs/soil/stb_image_aug.o: Libs/soil/stb_image_aug.c 
	${MKDIR} -p ${OBJECTDIR}/Libs/soil
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Libs/soil/stb_image_aug.o Libs/soil/stb_image_aug.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cefetinhodoapocalipse

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
