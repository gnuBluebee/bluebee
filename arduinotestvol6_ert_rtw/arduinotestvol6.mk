###########################################################################
## Makefile generated for component 'arduinotestvol6'. 
## 
## Makefile     : arduinotestvol6.mk
## Generated on : Sat Jul 10 15:56:44 2021
## Final product: $(RELATIVE_PATH_TO_ANCHOR)/arduinotestvol6.elf
## Product type : executable
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile

PRODUCT_NAME              = arduinotestvol6
MAKEFILE                  = arduinotestvol6.mk
MATLAB_ROOT               = C:/PROGRA~1/MATLAB/R2021a
MATLAB_BIN                = C:/PROGRA~1/MATLAB/R2021a/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/win64
START_DIR                 = C:/Users/legok/Desktop/aaaa
SOLVER                    = 
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
TGT_FCN_LIB               = None
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 0
RELATIVE_PATH_TO_ANCHOR   = ..
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          Arduino ARM MBED
# Supported Version(s):    
# ToolchainInfo Version:   2021a
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# ARDUINO_ROOT
# ARDUINO_PACKAGES_TOOLS_ROOT
# ARDUINO_PORT
# ARDUINO_MCU
# ARDUINO_BAUD
# ARDUINO_PROTOCOL
# ARDUINO_F_CPU

#-----------
# MACROS
#-----------

SHELL                       = %SystemRoot%/system32/cmd.exe
PRODUCT_HEX                 = $(RELATIVE_PATH_TO_ANCHOR)/$(PRODUCT_NAME).hex
PRODUCT_BIN                 = $(RELATIVE_PATH_TO_ANCHOR)/$(PRODUCT_NAME).bin
ARDUINO_TOOLS               = $(ARDUINO_PACKAGES_TOOLS_ROOT)/tools/arm-none-eabi-gcc/7-2017q4/bin
SLIB_PATH                   = C:/Users/legok/DOCUME~1/MATLAB/R2021a/ARDUIN~1/ARDUIN~3/FASTER~1

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = -lcore

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# Assembler: Arduino ARM Assembler
AS_PATH = $(ARDUINO_TOOLS)
AS = "$(AS_PATH)/arm-none-eabi-gcc"

# C Compiler: Arduino ARM C Compiler
CC_PATH = $(ARDUINO_TOOLS)
CC = "$(CC_PATH)/arm-none-eabi-gcc"

# Linker: Arduino ARM Linker
LD_PATH = $(ARDUINO_TOOLS)
LD = "$(LD_PATH)/arm-none-eabi-g++"

# C++ Compiler: Arduino ARM C++ Compiler
CPP_PATH = $(ARDUINO_TOOLS)
CPP = "$(CPP_PATH)/arm-none-eabi-g++"

# C++ Linker: Arduino ARM C++ Linker
CPP_LD_PATH = $(ARDUINO_TOOLS)
CPP_LD = "$(CPP_LD_PATH)/arm-none-eabi-g++"

# Archiver: Arduino ARM Archiver
AR_PATH = $(ARDUINO_TOOLS)
AR = "$(AR_PATH)/arm-none-eabi-ar"

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Binary Converter: Binary Converter
OBJCOPY_PATH = $(ARDUINO_PACKAGES_TOOLS_ROOT)/tools/arm-none-eabi-gcc/7-2017q4/bin
OBJCOPY = "$(OBJCOPY_PATH)/arm-none-eabi-objcopy"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: Make Tool
MAKE_PATH = %MATLAB%\bin\win64
MAKE = "$(MAKE_PATH)/gmake"


#-------------------------
# Directives/Utilities
#-------------------------

ASDEBUG             = -g
AS_OUTPUT_FLAG      = -o
CDEBUG              = -g
C_OUTPUT_FLAG       = -o
LDDEBUG             = -g
OUTPUT_FLAG         = -o
CPPDEBUG            = -g
CPP_OUTPUT_FLAG     = -o
CPPLDDEBUG          = -g
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG =
MEX_DEBUG           = -g
RM                  =
ECHO                = echo
MV                  =
RUN                 =

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              = ruvs
ASFLAGS              = -MMD -MP -MF"$(@:%.o=%.dep)" -MT"$@"  \
                       -Wall \
                       -x assembler-with-cpp \
                       $(ASFLAGS_ADDITIONAL) \
                       $(DEFINES) \
                       $(INCLUDES) \
                       -c
OBJCOPYFLAGS_BIN     = -O binary $(PRODUCT) $(PRODUCT_BIN)
CFLAGS               = -c -w -g -Os -nostdlib \
                       -MMD -MP -MF"$(@:%.o=%.dep)" -MT"$@" 
CPPFLAGS             = -c -w -g -Os -nostdlib \
                       -MMD -MP -MF"$(@:%.o=%.dep)" -MT"$@" 
CPP_LDFLAGS          =  -Os -Wl,-Map="$(PRODUCT_NAME).map" -Wl,--gc-sections
CPP_SHAREDLIB_LDFLAGS  =
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              =  -Os -Wl,-Map="$(PRODUCT_NAME).map" -Wl,--gc-sections
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    =



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = $(RELATIVE_PATH_TO_ANCHOR)/arduinotestvol6.elf
PRODUCT_TYPE = "executable"
BUILD_TYPE = "Top-Level Standalone Executable"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR) -IC:/PROGRA~3/MATLAB/SUPPOR~1/R2021a/toolbox/target/SUPPOR~1/ARDUIN~2/include -I$(START_DIR)/arduinotestvol6_ert_rtw -I$(MATLAB_ROOT)/extern/include -I$(MATLAB_ROOT)/simulink/include -I$(MATLAB_ROOT)/rtw/c/src -I$(MATLAB_ROOT)/rtw/c/src/ext_mode/common -I$(MATLAB_ROOT)/rtw/c/ert -I$(ARDUINO_MBED_ROOT)/tools/CMSIS/$(MBED_CMSIS_VERSION)/CMSIS/Include -I$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/cores/arduino -I$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/variants/ARDUINO_NANO33BLE -IC:/PROGRA~3/MATLAB/SUPPOR~1/R2021a/toolbox/target/SUPPOR~1/ARDUIN~1/include -IC:/PROGRA~3/MATLAB/SUPPOR~1/R2021a/toolbox/target/SUPPOR~1/ARDUIN~1/SCHEDU~1/include -IC:/PROGRA~3/MATLAB/SUPPOR~1/R2021a/toolbox/target/SUPPOR~1/ARMCOR~1/SCHEDU~1/include -IC:/PROGRA~3/MATLAB/SUPPOR~1/R2021a/toolbox/target/shared/EXTERN~1/include -IC:/PROGRA~3/MATLAB/SUPPOR~1/R2021a/toolbox/target/SUPPOR~1/ARMCOR~1/xcp/include

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_ = -D__MW_TARGET_USE_HARDWARE_RESOURCES_H__ -D_MW_ARDUINO_LOOP_=1 -DMW_ARDUINO_STEP_SIZE=1 -DMW_ARDUINO_MICROS -DARDUINO_NUM_SERIAL_PORTS=2 -D_RTT_BAUDRATE_SERIAL0_=9600 -D_RTT_BAUDRATE_SERIAL1_=9600 -D_RTT_ANALOG_REF_=0
DEFINES_BUILD_ARGS = -DCLASSIC_INTERFACE=0 -DALLOCATIONFCN=0 -DONESTEPFCN=1 -DTERMFCN=1 -DMULTI_INSTANCE_CODE=0 -DINTEGER_CODE=0 -DMT=0
DEFINES_CUSTOM = 
DEFINES_OPTS = -DTID01EQ=0
DEFINES_SKIPFORSIL = -DXCP_CUSTOM_PLATFORM -DEXIT_FAILURE=1 -DEXTMODE_DISABLEPRINTF -DEXTMODE_DISABLETESTING -DEXTMODE_DISABLE_ARGS_PROCESSING=1 -DSTACK_SIZE=64 -DRT
DEFINES_STANDARD = -DMODEL=arduinotestvol6 -DNUMST=1 -DNCSTATES=0 -DHAVESTDIO -DMODEL_HAS_DYNAMICALLY_LOADED_SFCNS=0

DEFINES = $(DEFINES_) $(DEFINES_BUILD_ARGS) $(DEFINES_CUSTOM) $(DEFINES_OPTS) $(DEFINES_SKIPFORSIL) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = C:/ProgramData/MATLAB/SupportPackages/R2021a/toolbox/target/supportpackages/arduinobase/src/MW_SerialRead.cpp C:/ProgramData/MATLAB/SupportPackages/R2021a/toolbox/target/supportpackages/arduinobase/src/MW_SerialWrite.cpp $(START_DIR)/arduinotestvol6_ert_rtw/arduinotestvol6.c $(START_DIR)/arduinotestvol6_ert_rtw/arduinotestvol6_data.c C:/ProgramData/MATLAB/SupportPackages/R2021a/toolbox/target/supportpackages/arduinotarget/registry/../src/MW_ArduinoHWInit.cpp C:/ProgramData/MATLAB/SupportPackages/R2021a/toolbox/target/supportpackages/arduinobase/src/io_wrappers.cpp C:/ProgramData/MATLAB/SupportPackages/R2021a/toolbox/target/supportpackages/arduinotarget/registry/../scheduler/src/arduinoARMM4mbedScheduler.cpp C:/ProgramData/MATLAB/SupportPackages/R2021a/toolbox/target/supportpackages/arduinotarget/registry/../scheduler/src/MW_arduinoNano33BLE_multitasking.c

MAIN_SRC = $(START_DIR)/arduinotestvol6_ert_rtw/ert_main.c

ALL_SRCS = $(SRCS) $(MAIN_SRC)

###########################################################################
## OBJECTS
###########################################################################

OBJS = MW_SerialRead.o MW_SerialWrite.o arduinotestvol6.o arduinotestvol6_data.o MW_ArduinoHWInit.o io_wrappers.o arduinoARMM4mbedScheduler.o MW_arduinoNano33BLE_multitasking.o

MAIN_OBJ = ert_main.o

ALL_OBJS = $(OBJS) $(MAIN_OBJ)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = $(SLIB_PATH)/MW_RebuildSrc_Core.o

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_SKIPFORSIL = "@$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/variants/ARDUINO_NANO33BLE/defines.txt" "@$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/variants/ARDUINO_NANO33BLE/cxxflags.txt"  -DARDUINO_ARCH_NRF52840 -MMD -mcpu=cortex-m4 -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -DARDUINO=108013 -DARDUINO_ARDUINO_NANO33BLE -DARDUINO_ARCH_MBED "-I$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/cores/arduino" "-I$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/variants/ARDUINO_NANO33BLE" "-I$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/cores/arduino/api/deprecated" -g3  "-iprefix$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/cores/arduino" "@$(ARDUINO_TARGET_ROOT)/include/MW_arduinoBLESense_Incl.txt" 
CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_SKIPFORSIL) $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_SKIPFORSIL = "@$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/variants/ARDUINO_NANO33BLE/defines.txt" "@$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/variants/ARDUINO_NANO33BLE/cxxflags.txt"  -DARDUINO_ARCH_NRF52840 -MMD -mcpu=cortex-m4 -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -DARDUINO=108013 -DARDUINO_ARDUINO_NANO33BLE -DARDUINO_ARCH_MBED "-I$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/cores/arduino" "-I$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/variants/ARDUINO_NANO33BLE" "-I$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/cores/arduino/api/deprecated" -g3  "-iprefix$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/cores/arduino" "@$(ARDUINO_TARGET_ROOT)/include/MW_arduinoBLESense_Incl.txt" 
CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CPPFLAGS += $(CPPFLAGS_SKIPFORSIL) $(CPPFLAGS_BASIC)

#---------------
# C++ Linker
#---------------

CPP_LDFLAGS_ = -L"$(SLIB_PATH)"
CPP_LDFLAGS_SKIPFORSIL = -Wl,--gc-sections -w -Wl,--as-needed "@$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/variants/ARDUINO_NANO33BLE/ldflags.txt" "-T$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/variants/ARDUINO_NANO33BLE/linker_script.ld" --specs=nano.specs --specs=nosys.specs -Wl,--whole-archive "$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/variants/ARDUINO_NANO33BLE/libs/libcc_310_core.a" "$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/variants/ARDUINO_NANO33BLE/libs/libcc_310_ext.a" "$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/variants/ARDUINO_NANO33BLE/libs/libcc_310_trng.a" "$(ARDUINO_TARGET_ROOT)/src/MW_libmbed.a" -Wl,--no-whole-archive -Wl,--start-group -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys -Wl,--end-group

CPP_LDFLAGS += $(CPP_LDFLAGS_) $(CPP_LDFLAGS_SKIPFORSIL)

#------------------------------
# C++ Shared Library Linker
#------------------------------

CPP_SHAREDLIB_LDFLAGS_ = -L"$(SLIB_PATH)"
CPP_SHAREDLIB_LDFLAGS_SKIPFORSIL = -Wl,--gc-sections -w -Wl,--as-needed "@$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/variants/ARDUINO_NANO33BLE/ldflags.txt" "-T$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/variants/ARDUINO_NANO33BLE/linker_script.ld" --specs=nano.specs --specs=nosys.specs -Wl,--whole-archive "$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/variants/ARDUINO_NANO33BLE/libs/libcc_310_core.a" "$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/variants/ARDUINO_NANO33BLE/libs/libcc_310_ext.a" "$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/variants/ARDUINO_NANO33BLE/libs/libcc_310_trng.a" "$(ARDUINO_TARGET_ROOT)/src/MW_libmbed.a" -Wl,--no-whole-archive -Wl,--start-group -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys -Wl,--end-group

CPP_SHAREDLIB_LDFLAGS += $(CPP_SHAREDLIB_LDFLAGS_) $(CPP_SHAREDLIB_LDFLAGS_SKIPFORSIL)

#-----------
# Linker
#-----------

LDFLAGS_ = -L"$(SLIB_PATH)"
LDFLAGS_SKIPFORSIL = -Wl,--gc-sections -w -Wl,--as-needed "@$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/variants/ARDUINO_NANO33BLE/ldflags.txt" "-T$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/variants/ARDUINO_NANO33BLE/linker_script.ld" --specs=nano.specs --specs=nosys.specs -Wl,--whole-archive "$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/variants/ARDUINO_NANO33BLE/libs/libcc_310_core.a" "$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/variants/ARDUINO_NANO33BLE/libs/libcc_310_ext.a" "$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/variants/ARDUINO_NANO33BLE/libs/libcc_310_trng.a" "$(ARDUINO_TARGET_ROOT)/src/MW_libmbed.a" -Wl,--no-whole-archive -Wl,--start-group -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys -Wl,--end-group

LDFLAGS += $(LDFLAGS_) $(LDFLAGS_SKIPFORSIL)

#--------------------------
# Shared Library Linker
#--------------------------

SHAREDLIB_LDFLAGS_ = -L"$(SLIB_PATH)"
SHAREDLIB_LDFLAGS_SKIPFORSIL = -Wl,--gc-sections -w -Wl,--as-needed "@$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/variants/ARDUINO_NANO33BLE/ldflags.txt" "-T$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/variants/ARDUINO_NANO33BLE/linker_script.ld" --specs=nano.specs --specs=nosys.specs -Wl,--whole-archive "$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/variants/ARDUINO_NANO33BLE/libs/libcc_310_core.a" "$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/variants/ARDUINO_NANO33BLE/libs/libcc_310_ext.a" "$(ARDUINO_MBED_ROOT)/hardware/mbed/$(MBED_LIB_VERSION)/variants/ARDUINO_NANO33BLE/libs/libcc_310_trng.a" "$(ARDUINO_TARGET_ROOT)/src/MW_libmbed.a" -Wl,--no-whole-archive -Wl,--start-group -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys -Wl,--end-group

SHAREDLIB_LDFLAGS += $(SHAREDLIB_LDFLAGS_) $(SHAREDLIB_LDFLAGS_SKIPFORSIL)

###########################################################################
## INLINED COMMANDS
###########################################################################


DERIVED_SRCS = $(subst .o,.dep,$(OBJS))

build:

%.dep:



-include codertarget_assembly_flags.mk
-include *.dep


###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build buildobj clean info prebuild postbuild download execute


all : build postbuild
	echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


buildobj : prebuild $(OBJS) $(PREBUILT_OBJS) $(LIBS)
	echo "### Successfully generated all binary outputs."


prebuild : 


postbuild : $(PRODUCT)
	echo "### Invoking postbuild tool "Binary Converter" ..."
	$(OBJCOPY) $(OBJCOPYFLAGS_BIN)
	echo "### Done invoking postbuild tool."


download : postbuild


execute : download
	echo "### Invoking postbuild tool "Execute" ..."
	$(EXECUTE) $(EXECUTE_FLAGS)
	echo "### Done invoking postbuild tool."


###########################################################################
## FINAL TARGET
###########################################################################

#-------------------------------------------
# Create a standalone executable            
#-------------------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS) $(LIBS) $(MAIN_OBJ)
	echo "### Creating standalone executable "$(PRODUCT)" ..."
	$(CPP_LD) $(CPP_LDFLAGS) -o $(PRODUCT) $(OBJS) $(MAIN_OBJ) $(LIBS) $(SYSTEM_LIBS) $(TOOLCHAIN_LIBS)
	echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.o : %.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.S.o : %.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.S.o : %.S
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.o : %.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : %.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : %.C
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : %.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.S.o : $(RELATIVE_PATH_TO_ANCHOR)/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.S.o : $(RELATIVE_PATH_TO_ANCHOR)/%.S
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.C
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.S.o : $(START_DIR)/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.S.o : $(START_DIR)/%.S
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.C
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : C:/ProgramData/MATLAB/SupportPackages/R2021a/toolbox/target/supportpackages/arduinobase/src/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.S.o : C:/ProgramData/MATLAB/SupportPackages/R2021a/toolbox/target/supportpackages/arduinobase/src/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.S.o : C:/ProgramData/MATLAB/SupportPackages/R2021a/toolbox/target/supportpackages/arduinobase/src/%.S
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.o : C:/ProgramData/MATLAB/SupportPackages/R2021a/toolbox/target/supportpackages/arduinobase/src/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : C:/ProgramData/MATLAB/SupportPackages/R2021a/toolbox/target/supportpackages/arduinobase/src/%.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : C:/ProgramData/MATLAB/SupportPackages/R2021a/toolbox/target/supportpackages/arduinobase/src/%.C
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : C:/ProgramData/MATLAB/SupportPackages/R2021a/toolbox/target/supportpackages/arduinobase/src/%.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/arduinotestvol6_ert_rtw/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.S.o : $(START_DIR)/arduinotestvol6_ert_rtw/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.S.o : $(START_DIR)/arduinotestvol6_ert_rtw/%.S
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/arduinotestvol6_ert_rtw/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/arduinotestvol6_ert_rtw/%.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/arduinotestvol6_ert_rtw/%.C
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/arduinotestvol6_ert_rtw/%.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/rtw/c/src/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.S.o : $(MATLAB_ROOT)/rtw/c/src/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.S.o : $(MATLAB_ROOT)/rtw/c/src/%.S
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/rtw/c/src/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/rtw/c/src/%.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/rtw/c/src/%.C
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/rtw/c/src/%.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/simulink/src/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.S.o : $(MATLAB_ROOT)/simulink/src/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.S.o : $(MATLAB_ROOT)/simulink/src/%.S
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/simulink/src/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/simulink/src/%.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/simulink/src/%.C
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/simulink/src/%.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


MW_SerialRead.o : C:/ProgramData/MATLAB/SupportPackages/R2021a/toolbox/target/supportpackages/arduinobase/src/MW_SerialRead.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


MW_SerialWrite.o : C:/ProgramData/MATLAB/SupportPackages/R2021a/toolbox/target/supportpackages/arduinobase/src/MW_SerialWrite.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


arduinotestvol6.o : $(START_DIR)/arduinotestvol6_ert_rtw/arduinotestvol6.c
	$(CC) $(CFLAGS) -o "$@" "$<"


arduinotestvol6_data.o : $(START_DIR)/arduinotestvol6_ert_rtw/arduinotestvol6_data.c
	$(CC) $(CFLAGS) -o "$@" "$<"


ert_main.o : $(START_DIR)/arduinotestvol6_ert_rtw/ert_main.c
	$(CC) $(CFLAGS) -o "$@" "$<"


MW_ArduinoHWInit.o : C:/ProgramData/MATLAB/SupportPackages/R2021a/toolbox/target/supportpackages/arduinotarget/registry/../src/MW_ArduinoHWInit.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


io_wrappers.o : C:/ProgramData/MATLAB/SupportPackages/R2021a/toolbox/target/supportpackages/arduinobase/src/io_wrappers.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


arduinoARMM4mbedScheduler.o : C:/ProgramData/MATLAB/SupportPackages/R2021a/toolbox/target/supportpackages/arduinotarget/registry/../scheduler/src/arduinoARMM4mbedScheduler.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


MW_arduinoNano33BLE_multitasking.o : C:/ProgramData/MATLAB/SupportPackages/R2021a/toolbox/target/supportpackages/arduinotarget/registry/../scheduler/src/MW_arduinoNano33BLE_multitasking.c
	$(CC) $(CFLAGS) -o "$@" "$<"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	echo "### PRODUCT = $(PRODUCT)"
	echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	echo "### BUILD_TYPE = $(BUILD_TYPE)"
	echo "### INCLUDES = $(INCLUDES)"
	echo "### DEFINES = $(DEFINES)"
	echo "### ALL_SRCS = $(ALL_SRCS)"
	echo "### ALL_OBJS = $(ALL_OBJS)"
	echo "### LIBS = $(LIBS)"
	echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	echo "### ASFLAGS = $(ASFLAGS)"
	echo "### CFLAGS = $(CFLAGS)"
	echo "### LDFLAGS = $(LDFLAGS)"
	echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	echo "### CPPFLAGS = $(CPPFLAGS)"
	echo "### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	echo "### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	echo "### ARFLAGS = $(ARFLAGS)"
	echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	echo "### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	echo "### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	echo "### OBJCOPYFLAGS_BIN = $(OBJCOPYFLAGS_BIN)"
	echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	$(RM) $(PRODUCT)
	$(RM) $(ALL_OBJS)
	$(RM) *.dep
	$(ECHO) "### Deleted all derived files."


