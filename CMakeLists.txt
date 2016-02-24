cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
cmake_policy(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(NAME vulkan_experimentation)

project(${NAME})

include_directories(third_party)
include_directories(src)

add_executable(HelloWorld src/hello_world.cc)

install(TARGETS HelloWorld DESTINATION bin)
