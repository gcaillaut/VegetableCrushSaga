#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 2.6)
project(VegetableCrushSaga CXX)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

include_directories("${PROJECT_BINARY_DIR}/include")

# Flags
if (CMAKE_CXX_COMPILER MATCHES ".*clang")
   set(CMAKE_COMPILER_IS_CLANGXX 1)
endif ()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX)
    set(CMAKE_CXX_FLAGS "-O2 -Wall -Wextra -std=c++11")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
# Define sources and executable
set(EXECUTABLE_NAME "vcs")
file( 
      GLOB_RECURSE 
      source_files
      src/* 
)
add_executable(${EXECUTABLE_NAME} ${source_files})


# Detect and add libs
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

# Detect and add SFML
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()


# Detect and add Yaml-cpp
find_package(YamlCpp)
if(YAMLCPP_FOUND)
	include_directories(${YAML_CPP_INCLUDE_DIR})
	target_link_libraries(${EXECUTABLE_NAME} ${YAMLCPP_LIBRARY})
endif()
