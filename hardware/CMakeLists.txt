project(efr32_hardware)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/kit/${CPU_FAMILY_U}_${BOARD}/config
        ${CMAKE_CURRENT_LIST_DIR}/kit/common/bsp
        ${CMAKE_CURRENT_LIST_DIR}/kit/common/bsp/thunderboard
        ${CMAKE_CURRENT_LIST_DIR}/kit/common/drivers
        ${CMAKE_CURRENT_LIST_DIR}/kit/common/halconfig
        ${CMAKE_CURRENT_LIST_DIR}/module/config)

