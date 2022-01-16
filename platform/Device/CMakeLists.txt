# EFR32 Device Library CMake file
#
# Checks if the device folder is present and adds linker script, system files 
# and compiler flags for the device to the build

project(efr32_device)

if (NOT DEFINED EFR32_DEVICE)
	error("No Device defined!")
endif()



string(TOUPPER ${EFR32_DEVICE} DEVICE_U)
message("Processor: ${DEVICE_U}")

set(DEVICE_FOUND FALSE)
set(TEMP_DEVICE "${DEVICE_U}")

while (NOT DEVICE_FOUND)
    if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/SiliconLabs/${TEMP_DEVICE}")
        set(DEVICE_FOUND TRUE)
    else ()
        string(LENGTH ${TEMP_DEVICE} TEMP_DEVICE_LEN)
        math(EXPR TEMP_DEVICE_LEN "${TEMP_DEVICE_LEN}-1")
        string(SUBSTRING ${TEMP_DEVICE} 0 ${TEMP_DEVICE_LEN} TEMP_DEVICE)
    endif ()

    if (${TEMP_DEVICE_LEN} EQUAL "0")
        break()
    endif ()
endwhile ()

if (NOT DEVICE_FOUND)
    message(FATAL_ERROR "failed to find device")
endif ()

set(CPU_FAMILY_U ${TEMP_DEVICE})
set(CPU_FAMILY_U ${CPU_FAMILY_U} PARENT_SCOPE ) #<-- set in the parent scope too
string(TOLOWER ${CPU_FAMILY_U} CPU_FAMILY_L)
message("Family: ${CPU_FAMILY_U}")

# TODO: Complete list and check CPUs
if (CPU_FAMILY_U STREQUAL "EFR32BG1B" OR CPU_FAMILY_U STREQUAL "EFR32BG1P"
        OR CPU_FAMILY_U STREQUAL "EFR32BG1V" OR CPU_FAMILY_U STREQUAL "EFR32BG12P"
        OR CPU_FAMILY_U STREQUAL "EFR32BG13P" OR CPU_FAMILY_U STREQUAL "EFR32BG21"
        OR CPU_FAMILY_U STREQUAL "EFR32BG122" OR CPU_FAMILY_U STREQUAL "EFR32FG1P"
        OR CPU_FAMILY_U STREQUAL "EFR32FG1V" OR CPU_FAMILY_U STREQUAL "EFR32FG12P"
        OR CPU_FAMILY_U STREQUAL "EFR32FG1V" OR CPU_FAMILY_U STREQUAL "EFR32FG12P"
        OR CPU_FAMILY_U STREQUAL "EFR32FG13P" OR CPU_FAMILY_U STREQUAL "EFR32FG14P"
        OR CPU_FAMILY_U STREQUAL "EFR32FG14V" OR CPU_FAMILY_U STREQUAL "EFR32FG22"
        OR CPU_FAMILY_U STREQUAL "EFR32FG23" OR CPU_FAMILY_U STREQUAL "EFR32MG1B"
        OR CPU_FAMILY_U STREQUAL "EFR32MG1P" OR CPU_FAMILY_U STREQUAL "EFR32MG1V"
        OR CPU_FAMILY_U STREQUAL "EFR32MG12P" OR CPU_FAMILY_U STREQUAL "EFR32MG13P"
        OR CPU_FAMILY_U STREQUAL "EFR32MG14P" OR CPU_FAMILY_U STREQUAL "EFR32FG22")
    message("Architecture: cortex-m4")
    set(CPU_TYPE "m4")
    set(CPU_FIX -mfpu=fpv4-sp-d16 
                -mfloat-abi=softfp)

elseif (CPU_FAMILY_U STREQUAL "EFR32MG21" OR CPU_FAMILY_U STREQUAL "EFR32BG21"
        OR CPU_FAMILY_U STREQUAL "EFR32MG22" OR CPU_FAMILY_U STREQUAL "EFR32BG22")
    message("Architecture: cortex-m33")
    set(CPU_TYPE "m33")
    set(CPU_FIX -march=armv8-m.main+dsp 
                -mcmse 
                -mfpu=fpv5-sp-d16 
                -mfloat-abi=hard 
                -falign-functions=2)
else ()
    message("Architecture: cortex-m3 (default)")
    set(CPU_TYPE "m3")
    set(CPU_FIX -mfix-cortex-m3-ldrd)
endif ()

add_library(${PROJECT_NAME} STATIC
			${CMAKE_CURRENT_LIST_DIR}/SiliconLabs/${CPU_FAMILY_U}/Source/GCC/startup_${CPU_FAMILY_L}.c
			${CMAKE_CURRENT_LIST_DIR}/SiliconLabs/${CPU_FAMILY_U}/Source/system_${CPU_FAMILY_L}.c)

target_include_directories(${PROJECT_NAME} 
							PUBLIC 
							${CMAKE_CURRENT_LIST_DIR}/SiliconLabs/${CPU_FAMILY_U}/Include)


# Set linker definitions
set(EFR32_LINKER_FILE 
		${CMAKE_CURRENT_LIST_DIR}/SiliconLabs/${CPU_FAMILY_U}/Source/GCC/${CPU_FAMILY_L}.ld)

		
# C Flags
set(EFR32_DEVICE_C_FLAGS 
    -mthumb 
    -mcpu=cortex-${CPU_TYPE}
    -D${EFR32_DEVICE}
    ${CPU_FIX}
    )
    
set(EFR32_DEVICE_C_LFLAGS
    ${EFR32_DEVICE_C_FLAGS}
    -Wl,-Map=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.map
	-Wl,-T${EFR32_LINKER_FILE})
    

# C++ Flags
set(EFR32_DEVICE_CXX_FLAGS 
        ${EFR32_DEVICE_C_FLAGS}
        -fno-exceptions 
        -fno-rtti
        )

set(EFR32_DEVICE_CXX_LFLAGS
    ${EFR32_DEVICE_CXX_FLAGS}
    -Wl,-Map=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.map
	-Wl,-T${EFR32_LINKER_FILE})


# Assembler Flags
set(EFR32_ASM_FLAGS
	${EFR32_C_FLAGS} 
	-x assembler-with-cpp)


target_compile_options(${PROJECT_NAME}
	PUBLIC
    $<$<COMPILE_LANGUAGE:ASM>:${EFR32_ASM_FLAGS}>
	$<$<COMPILE_LANGUAGE:C>:${EFR32_DEVICE_C_FLAGS}>
	$<$<COMPILE_LANGUAGE:CXX>:${EFR32_DEVICE_CXX_FLAGS}>)

target_link_options(${PROJECT_NAME}
    PUBLIC 
	$<$<COMPILE_LANGUAGE:C>:${EFR32_DEVICE_C_LFLAGS}>
	$<$<COMPILE_LANGUAGE:CXX>:${EFR32_DEVICE_CXX_LFLAGS}>)

    
target_link_libraries(${PROJECT_NAME} cmsis kit_common_bsp)