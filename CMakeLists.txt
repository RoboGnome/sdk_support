# Include all modules of the sdk so we only have to include the sdk cmake subdirectory to have access to all other libaries
#
# To add a sdk module to your project, link against a library target (e.g. emlib, efr32_device, etc)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/platform/CMSIS)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/platform/emlib)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/platform/Device)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/platform/halconfig)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/protocol)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/hardware)