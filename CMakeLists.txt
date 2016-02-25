cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
cmake_policy(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(NAME vulkan_experimentation)

project(${NAME})

include_directories(third_party)
include_directories(third_party/glm)
include_directories(third_party/SaschaWillems_Vulkan/base)
include_directories(third_party/assimp/include)
include_directories(third_party/gli)
include_directories(src)

# Hello World Test.
add_executable(HelloWorld src/hello_world.cc)
install(TARGETS HelloWorld DESTINATION bin)

# GLM Include Test.
add_executable(GLMInclude src/test_glm_include.cc)
install(TARGETS GLMInclude DESTINATION bin)

# Set BASE_DIRECTORY.
if (NOT BASE_DIRECTORY)
  set(BASE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()

message(STATUS "BASE_DIRECTORY = ${BASE_DIRECTORY}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")

# Include cmake modules.
set(CMAKE_MODULE_PATH
  ${BASE_DIRECTORY}/third_party/nvidia/nvpro_shared_sources/cmake
)

# Find VulkanSDK.
find_package(VulkanSDK REQUIRED)
if(VULKANSDK_FOUND)
  message(STATUS "Found VulkanSDK!")
  add_definitions(-DUSEVULKANSDK)
  include_directories(${VULKANSDK_INCLUDE_DIR})
  list(APPEND LIBRARIES_OPTIMIZED ${VULKAN_LIB})
  list(APPEND LIBRARIES_DEBUG ${VULKAN_LIB})
  list(APPEND PACKAGE_SOURCE_FILES ${VULKANSDK_HEADERS})
  source_group(OPTIX FILES  ${VULKANSDK_HEADERS})
else()
  message(SEND_ERROR "Did not find VulkanSDK, please resolve.")
endif()

# VulkanSDK Include Test.
add_executable(VulkanSDKInclude src/test_vulkan_sdk_include.cc)
install(TARGETS VulkanSDKInclude DESTINATION bin)

# Triangle from SaschaWillems.
add_executable(Triangle third_party/SaschaWillems_Vulkan/triangle/triangle.cc)
install(TARGETS Triangle DESTINATION bin)
