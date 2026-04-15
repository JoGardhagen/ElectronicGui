cmake_minimum_required(VERSION 3.14)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# Raylib
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master
)
FetchContent_MakeAvailable(raylib)

# --- Kolla om vi är på Raspberry Pi ---
set(IS_PI FALSE)
if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm" OR CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
    set(IS_PI TRUE)
endif()

# --- Skapa executable ---
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Circuits/Circuits.cpp
    src/Panels/GPIOPanel.cpp
    src/Utilities/Util.cpp   
    src/Components/GPIOPin.cpp
    src/Components/Resistor.cpp
    src/Components/LightEmittingDiode.cpp
    src/Components/Capacitor.cpp
    src/Components/Wire.cpp
    src/Circuits/Circuit1.cpp
    src/Circuits/Circuit2.cpp
    src/Circuits/Circuit3.cpp
    src/Circuits/Circuit4.cpp
    src/AppState
    src/Circuits/CircuitUnderConstruction.cpp
    src/UI/Dropdown.cpp
    src/Components/Spst.cpp
)

# 🔥 Lägg till RaspberryGPIO endast på Pi
if(IS_PI)
    target_sources(${PROJECT_NAME} PRIVATE
        src/Components/GPIO/RaspberryGPIO.cpp
    )
endif()

# Raylib
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Linux / X11
if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${X11_LIBRARIES} pthread dl m)
endif()

# 🔥 GPIO (DETTA VAR DITT PROBLEM)
if(IS_PI)
    target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_RPI)

    find_library(GPIOD_LIB gpiod)
    if(NOT GPIOD_LIB)
        message(FATAL_ERROR "libgpiod not found! Install with: sudo apt install libgpiod-dev")
    endif()

    target_link_libraries(${PROJECT_NAME} PRIVATE ${GPIOD_LIB})
endif()