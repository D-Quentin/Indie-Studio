cmake_minimum_required(VERSION 3.0)

set(PROJ "bomberman")
project(${PROJ})

find_package(raylib 3.7 QUIET)

set(CMAKE_C_STANDARD 14)
include_directories(boost_1_76_0)
include_directories(include)
include_directories(encapsulation/include)
LINK_DIRECTORIES(boost_1_76_0/stage/lib)

file(
    GLOB
    SRCS
    src/*.cpp
    src/*/*.cpp
    encapsulation/*/*.cpp
)

if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)

  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/master.tar.gz
  )

  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)

    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples

    # build raylib
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})

  endif()

endif()

add_executable(${PROJ} ${SRCS})
target_link_libraries(${PROJ} raylib)

if (UNIX)
    target_compile_options(${PROJ} PRIVATE -Wall -Wextra)

elseif (WIN32)
    target_compile_options(${PROJ} PRIVATE -Wall)

endif()