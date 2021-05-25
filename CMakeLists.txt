cmake_minimum_required(VERSION 3.0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR})

set(PROJ "bomberman")

project(${PROJ})

include_directories(../include)

file(
    GLOB
    SRCS
    src/*.cpp
    src/*/*.cpp
)
add_executable(${PROJ} ${SRCS})

if (UNIX)
    target_compile_options(${PROJ} PRIVATE -Wall -Wextra)

elseif (WIN32)
    target_compile_options(${PROJ} PRIVATE -Wall)

endif()