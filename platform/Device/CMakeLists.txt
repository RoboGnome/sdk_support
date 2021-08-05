# EFR32 Device Library CMake file
#
# Configures the required linker script, startup script, and system file and adds them to the build

if (NOT DEFINED EFR32_DEVICE)
	error("No Device defined!")
endif()

message("Adding device library for: ${CPU_FAMILY_U}")


add_library(efr32_device STATIC
			${CMAKE_CURRENT_LIST_DIR}/SiliconLabs/${CPU_FAMILY_U}/Source/GCC/startup_${CPU_FAMILY_L}.c
			${CMAKE_CURRENT_LIST_DIR}/SiliconLabs/${CPU_FAMILY_U}/Source/system_${CPU_FAMILY_L}.c)

target_include_directories(efr32_device 
							PUBLIC 
							${CMAKE_CURRENT_LIST_DIR}/SiliconLabs/${CPU_FAMILY_U}/Include)

target_link_libraries(efr32_device cmsis bareMetal_efr32)

# Set linker definitions
set(EFR32_LINKER_FILE 
		${CMAKE_CURRENT_LIST_DIR}/SiliconLabs/${CPU_FAMILY_U}/Source/GCC/${CPU_FAMILY_L}.ld)


# Set compiler & linke definitions
set(EFR32_DEVICE_C_FLAGS 
	-D${EFR32_DEVICE})

set(EFR32_DEVICE_CXX_FLAGS 
	-D${EFR32_DEVICE})

set(EFR32_DEVICE_C_LFLAGS 
	-Wl,-T${EFR32_LINKER_FILE})

set(EFR32_DEVICE_CXX_LFLAGS
	-Wl,-T${EFR32_LINKER_FILE})


target_compile_options(bareMetal_efr32
	INTERFACE
	$<$<COMPILE_LANGUAGE:C>:${EFR32_DEVICE_C_FLAGS}>
	$<$<COMPILE_LANGUAGE:CXX>:${EFR32_DEVICE_CXX_FLAGS}>)

target_link_options(efr32_device
	INTERFACE 
	$<$<COMPILE_LANGUAGE:C>:${EFR32_DEVICE_C_LFLAGS}>
	$<$<COMPILE_LANGUAGE:CXX>:${EFR32_DEVICE_CXX_LFLAGS}>)
