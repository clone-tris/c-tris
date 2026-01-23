cmake_minimum_required(VERSION 3.21)

project(c-tris VERSION 0.1 LANGUAGES C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

# Dependencies -------------------------

# # RayLib
# FetchContent_Declare(
#     raylib
#     GIT_REPOSITORY https://github.com/raysan5/raylib.git
#     GIT_TAG 5.5
#     GIT_SHALLOW TRUE
#     GIT_PROGRESS TRUE
# )
# FetchContent_MakeAvailable(raylib)
# set_property(DIRECTORY "${raylib_SOURCE_DIR}" PROPERTY EXCLUDE_FROM_ALL TRUE)

# SDL 
set(SDL_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL_SHARED ON CACHE BOOL "" FORCE)
set(SDL_STATIC OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.4.0
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(SDL3)
set_property(DIRECTORY "${sdl_SOURCE_DIR}" PROPERTY EXCLUDE_FROM_ALL TRUE)

# SDL_ttf
set(SDLTTF_VENDORED ON CACHE BOOL "" FORCE)
set(SDLTTF_HARFBUZZ OFF CACHE BOOL "" FORCE)
set(SDLTTF_PLUTOSVG OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    SDL3_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-3.2.2
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(SDL3_ttf)
set_property(DIRECTORY "${sdl3_ttf_SOURCE_DIR}" PROPERTY EXCLUDE_FROM_ALL TRUE)

# STB
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(stb)

# Compilation --------------------------
 
add_executable(${PROJECT_NAME}
    src/main.c
    src/helpers.c
    src/colors.c
    src/engine/screen.c
    src/engine/painter.c
    src/screens/game/game_screen.c
    src/screens/game/painter.c
    src/screens/game/components/shape.c
    src/screens/game/components/square.c
    src/screens/game/components/tetromino.c
    src/screens/game/components/score.c
    src/screens/menu/menu_screen.c
    src/screens/over/over_screen.c
)


target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3::SDL3
    SDL3_ttf::SDL3_ttf
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE
    $<TARGET_PROPERTY:SDL3::SDL3,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:SDL3_ttf::SDL3_ttf,INTERFACE_INCLUDE_DIRECTORIES>
    ${stb_SOURCE_DIR}
)

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/jetbrainsmono.ttf
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/jetbrainsmono.ttf
    COMMENT "Copying font to build directory"
)
