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

if(WIN32)
  # Windows (could be 64 bit).
  find_library(ASSIMP_LIB NAMES assimp
               PATHS ${CMAKE_SOURCE_DIR}/third_party/libs/assimp)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_USE_PLATFORM_WIN32_KHR")
else()
  # Linux?
  find_library(ASSIMP_LIB NAMES assimp libassimp.dll.a
               PATHS ${CMAKE_SOURCE_DIR}/third_party/libs/assimp)
  find_package(XCB REQUIRED)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_USE_PLATFORM_XCB_KHR")
endif()

# Set preprocessor defines.
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -DNOMINMAX -DVK_PROTOTYPES -D_USE_MATH_DEFINES")

# TODO(scotttodd): build assimp from CMake automatically.

# Hello World Test.
add_executable(HelloWorld src/hello_world.cc)
install(TARGETS HelloWorld DESTINATION bin)

# GLM Include Test.
add_executable(GLMInclude src/test_glm_include.cc)
install(TARGETS GLMInclude DESTINATION bin)

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

# Find Assimp.
# TODO(scotttodd): Figure out library here, maybe lib/ folder.
# find_library(ASSIMP_LIB NAMES assimp )

message(STATUS "VULKAN_LIB '${VULKAN_LIB}'")
message(STATUS "WINLIBS '${WINLIBS}'")
message(STATUS "ASSIMP_LIB '${ASSIMP_LIB}'")

# VulkanSDK Include Test.
add_executable(VulkanSDKInclude src/test_vulkan_sdk_include.cc)
# target_link_libraries(VulkanSDKInclude ${VULKAN_LIB})
install(TARGETS VulkanSDKInclude DESTINATION bin)

# Triangle from SaschaWillems.
add_executable(Triangle third_party/SaschaWillems_Vulkan/triangle/triangle.cc)
install(TARGETS Triangle DESTINATION bin)
