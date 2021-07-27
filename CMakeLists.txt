# Include all modules of the sdk so we only have to include the sdk cmake subdirectory

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/platform/CMSIS)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/platform/emlib)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/platform/Device)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/protocol)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/hardware)