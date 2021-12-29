project(efr32_hardware)

if (NOT DEFINED EFR32_DEVICE)
	error("No Device defined!")
endif()
if (NOT DEFINED BOARD)
	error("No board defined!")
endif()

string(TOUPPER ${EFR32_DEVICE} DEVICE_U)
string(TOUPPER ${BOARD} BOARD_U)
set(BSP_FOUND FALSE)
set(TEMP_DEVICE "${DEVICE_U}")
set(TEMP_BOARD "${BOARD_U}")
set(TEMP_BSP "${TEMP_DEVICE}_${TEMP_BOARD}")

while (NOT BSP_FOUND)
    if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/kit/${TEMP_BSP}")
        set(BSP_FOUND TRUE)
    else ()
        string(LENGTH ${TEMP_DEVICE} TEMP_DEVICE_LEN)
        math(EXPR TEMP_DEVICE_LEN "${TEMP_DEVICE_LEN}-1")
        string(SUBSTRING ${TEMP_DEVICE} 0 ${TEMP_DEVICE_LEN} TEMP_DEVICE)
        set(TEMP_BSP "${TEMP_DEVICE}_${TEMP_BOARD}")
    endif ()
    if (${TEMP_DEVICE_LEN} EQUAL "0")
        break()
    endif ()
endwhile ()

if (NOT BSP_FOUND)
    message(FATAL_ERROR "failed to find bsp")
endif ()

set(BSP ${TEMP_BSP})
message("BSP: " ${BSP})

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/kit/${CPU_FAMILY_U}_${BOARD}/config
        ${CMAKE_CURRENT_LIST_DIR}/kit/common/drivers
        ${CMAKE_CURRENT_LIST_DIR}/kit/common/halconfig
        ${CMAKE_CURRENT_LIST_DIR}/kit/${BSP}/config       
        ${CMAKE_CURRENT_LIST_DIR}/module/config)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/kit/common/bsp)