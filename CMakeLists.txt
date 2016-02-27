# CMake file based off of
# https://github.com/SaschaWillems/Vulkan/blob/master/CMakeLists.txt

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
cmake_policy(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(NAME vulkan_experimentation)

project(${NAME})

include_directories(third_party)
include_directories(third_party/assimp/include)
include_directories(third_party/gli)
include_directories(third_party/glm)
include_directories(third_party/SaschaWillems_Vulkan/base)

# Include cmake modules.
set(CMAKE_MODULE_PATH
  ${CMAKE_SOURCE_DIR}/cmake
)

# TODO(scotttodd): build assimp from CMake automatically.
if(WIN32)
  # Windows (could be 64 bit).
  find_package(VulkanSDK REQUIRED)
  find_library(ASSIMP_LIB NAMES assimp
               PATHS ${CMAKE_SOURCE_DIR}/third_party/libs/assimp)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_USE_PLATFORM_WIN32_KHR")
else()
  # Linux?
  find_package(VulkanSDK REQUIRED)
  find_library(ASSIMP_LIB NAMES assimp libassimp.dll.a
               PATHS ${CMAKE_SOURCE_DIR}/third_party/libs/assimp)
  find_package(XCB REQUIRED)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_USE_PLATFORM_XCB_KHR")
endif()

message(STATUS "VULKAN_LIB '${VULKAN_LIB}'")
message(STATUS "ASSIMP_LIB '${ASSIMP_LIB}'")

include_directories(${VULKANSDK_INCLUDE_DIR})

# Set preprocessor defines.
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -DNOMINMAX -DVK_PROTOTYPES -D_USE_MATH_DEFINES")

add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-std=c++11)
add_definitions(-std=c++0x)

# Compiler specific stuff.
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
endif()
if(NOT WIN32)
  link_libraries(${XCB_LIBRARIES} ${VULKAN_LIB})
endif()

message(STATUS "CMAKE_CXX_FLAGS: '${CMAKE_CXX_FLAGS}'")

# Hello World Test.
add_executable(HelloWorld src/hello_world.cc)
install(TARGETS HelloWorld DESTINATION bin)

# GLM Include Test.
add_executable(GLMInclude src/test_glm_include.cc)
install(TARGETS GLMInclude DESTINATION bin)

# VulkanSDK Include Test.
add_executable(VulkanSDKInclude src/test_vulkan_sdk_include.cc)
target_link_libraries(VulkanSDKInclude ${VULKAN_LIB})
install(TARGETS VulkanSDKInclude DESTINATION bin)

# WinMain Test.
add_executable(WinMainTest WIN32 src/test_win_main.cc)
target_link_libraries(WinMainTest ${WINLIBS})
install(TARGETS WinMainTest DESTINATION bin)

# Triangle from SaschaWillems.
# add_executable(Triangle WIN32 third_party/SaschaWillems_Vulkan/triangle/triangle.cc)
# target_link_libraries(Triangle ${VULKAN_LIB} ${ASSIMP_LIB} ${WINLIBS})
# install(TARGETS Triangle DESTINATION bin)
