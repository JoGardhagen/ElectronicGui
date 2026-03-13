cmake_minimum_required(VERSION 3.14)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# Hämta Raylib automatiskt
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master
)
FetchContent_MakeAvailable(raylib)

# Lägg till din källa
add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/Circuits.cpp
    src/GPIOPanel.cpp
    src/Components.cpp   
)

# Länka Raylib
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Linux / X11
if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${X11_LIBRARIES} pthread dl m)
endif()

# Raspberry Pi define (valfritt)
if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
    target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_RPI)
endif()