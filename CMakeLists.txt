CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
project(VegetableCrushSaga CXX)

SET(PROJECT_NAME "MVC")
SET(EXECUTABLE_NAME "Game")

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE "Debug")
endif()

# Flags
if (CMAKE_CXX_COMPILER MATCHES "clang")
  set(CMAKE_COMPILER_IS_CLANGXX 1)
endif ()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Os")
endif()

SET(CMAKE_EXE_LINKER_FLAGS  "-s")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})


PROJECT(${PROJECT_NAME})
INCLUDE_DIRECTORIES( ./ )

# -------------------
# Source files

FILE(
  GLOB_RECURSE
  PROJECT_SOURCES
  src/* include/*
  )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# -------------------
# External libs

SET(GAME_LIBS -lsfml-network -lsfml-system -lsfml-window -lsfml-graphics)

# -------------------
# Executable & Link

ADD_EXECUTABLE( "${EXECUTABLE_NAME}" ${PROJECT_SOURCES} )
TARGET_LINK_LIBRARIES( "${EXECUTABLE_NAME}" ${GAME_LIBS} )
