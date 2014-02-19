cmake_minimum_required(VERSION 2.6)
project(VegetableCrushSaga CXX)

set(PROJECT_NAME "VegetableCrushSaga")
set(EXECUTABLE_NAME "Game")

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE "Debug")
endif()

# Flags
if(CMAKE_CXX_COMPILER MATCHES "clang")
  set(CMAKE_COMPILER_IS_CLANGXX 1)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Os")
endif()

set(CMAKE_EXE_LINKER_FLAGS  "-s")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})


project(${PROJECT_NAME})

# -------------------
# Source files

file(
  GLOB_RECURSE
  PROJECT_SOURCES
  src/* include/*
  )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# -------------------
# External libs

set(GAME_LIBS -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio)

# -------------------
# Executable & Link

add_executable( ${EXECUTABLE_NAME} ${PROJECT_SOURCES} )
target_link_libraries( ${EXECUTABLE_NAME} ${GAME_LIBS} )

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
