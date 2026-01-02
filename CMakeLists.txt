cmake_minimum_required(VERSION 3.21)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE FILEPATH "Vcpkg toolchain file")

project(c-tris
    VERSION 0.1
    LANGUAGES C
)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(SDL2 CONFIG REQUIRED)

# Create the executable
add_executable(c-tris
    src/main.c
)

if(MSVC)
    target_compile_options(c-tris PRIVATE /W4)
    target_compile_definitions(c-tris PRIVATE WIN32 _WINDOWS)
else()
    target_compile_options(c-tris PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Link SDL2
target_link_libraries(c-tris
    PRIVATE SDL2::SDL2main SDL2::SDL2 
)
