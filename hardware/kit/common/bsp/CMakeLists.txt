project(kit_common_bsp)

# find . -name '*.c' | sort -u
add_library(${PROJECT_NAME} STATIC
                ${CMAKE_CURRENT_SOURCE_DIR}/bsp_trace.c)



target_include_directories(${PROJECT_NAME}
                                PUBLIC 
                                ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC efr32_device emlib efr32_hardware)