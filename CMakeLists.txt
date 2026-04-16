cmake_minimum_required(VERSION 3.14)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)


FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master
)
FetchContent_MakeAvailable(raylib)


set(IS_PI FALSE)

if(UNIX AND NOT APPLE AND 
   (CMAKE_SYSTEM_PROCESSOR MATCHES "arm" OR CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64"))
    set(IS_PI TRUE)
endif()

message(STATUS "Processor: ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "IS_PI: ${IS_PI}")


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
    src/Components/Spst.cpp
    src/Components/Transistor.cpp

    src/Circuits/Circuit1.cpp
    src/Circuits/Circuit2.cpp
    src/Circuits/Circuit3.cpp
    src/Circuits/Circuit4.cpp
    src/Circuits/Circuit5.cpp
    src/Circuits/CircuitUnderConstruction.cpp

    src/UI/Dropdown.cpp
    src/AppState.cpp
)

# =========================
# 🍓 Raspberry Pi GPIO
# =========================
if(IS_PI)
    message(STATUS "Building with Raspberry Pi GPIO")

    target_sources(${PROJECT_NAME} PRIVATE
        src/Components/GPIO/RaspberryGPIO.cpp
    )

    target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_RPI)

    find_library(GPIOD_LIB gpiod)
    if(NOT GPIOD_LIB)
        message(FATAL_ERROR "libgpiod not found! Install with: sudo apt install libgpiod-dev")
    endif()

    target_link_libraries(${PROJECT_NAME} PRIVATE ${GPIOD_LIB})
else()
    message(STATUS "Building in SIMULATOR mode (DummyGPIO)")
endif()


target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Linux extra libs (ej Mac)
if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${X11_LIBRARIES} pthread dl m)
endif()