if(NOT LINUX)
    message(FATAL_ERROR "Only Linux is supported as evdev is required for this plugin")
endif()

set(PLUGIN_NAME jstick)

# Dependencies
    # None

# Source files
set(CPPFILES src/opcodes.cpp src/joystick.cpp)
make_plugin(${PLUGIN_NAME} "${CPPFILES}")
target_include_directories(${PLUGIN_NAME} PRIVATE ${CSOUND_INCLUDE_DIRS})
