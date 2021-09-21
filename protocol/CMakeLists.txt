project(efr32_protocol)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/bluetooth/inc
    ${CMAKE_CURRENT_LIST_DIR}/bluetooth/config)

target_link_options(${PROJECT_NAME} INTERFACE -L${CMAKE_CURRENT_LIST_DIR}/bluetooth/lib/${CPU_FAMILY_U}/GCC)

add_library(bluetooth STATIC IMPORTED)
set_target_properties(bluetooth PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/bluetooth/lib/${CPU_FAMILY_U}/GCC/libbluetooth.a)
target_link_libraries(${PROJECT_NAME} INTERFACE bluetooth)

if (BL_MESH)
    add_library(bluetooth_mesh STATIC IMPORTED)
    set_target_properties(bluetooth_mesh PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/bluetooth/lib/${CPU_FAMILY_U}/GCC/libbluetooth_mesh.a)
    target_link_libraries(${PROJECT_NAME} INTERFACE bluetooth_mesh)
endif()

if (BL_PSSTORE)
    add_library(psstore STATIC IMPORTED)
    set_target_properties(psstore PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/bluetooth/lib/${CPU_FAMILY_U}/GCC/libpsstore.a)
    target_link_libraries(${PROJECT_NAME} INTERFACE psstore)
endif()
