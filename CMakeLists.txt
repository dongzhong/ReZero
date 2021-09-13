cmake_minimum_required(VERSION 3.8.0)

project(rezero)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-aligned-allocation")

set(REZERO_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(rezero)

if(NOT ANDROID)
  add_subdirectory(example)
endif()