cmake_minimum_required(VERSION 3.21)

project(c-tris
    VERSION 0.1
    LANGUAGES C
)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG main
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)

# set(SDL_SHARED ON CACHE BOOL "Build SDL3 as shared library")
# set(SDL_STATIC OFF CACHE BOOL "Build SDL3 as shared library")
set(SDL_TESTS OFF CACHE BOOL "Disable SDL3 tests")
set(SDL_EXAMPLES OFF CACHE BOOL "Disable SDL3 tests")


FetchContent_MakeAvailable(SDL3)

add_executable(${PROJECT_NAME} src/main.c)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
