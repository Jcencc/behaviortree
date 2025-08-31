#cmake_minimum_required(VERSION 3.15)
#project(usd_action)
#
#set(CMAKE_CXX_STANDARD 20)
#add_compile_options(/utf-8)
#if(MSVC)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /Zc:__cplusplus")
#endif()
#
#add_definitions(-DNOMINMAX)
#
#set(CMAKE_NINJA_FORCE_RESPONSE_FILE ON CACHE BOOL "Force Ninja to use response files" FORCE)
#
#if(MSVC)
#    set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_LIBRARIES ON)
#    set(CMAKE_C_USE_RESPONSE_FILE_FOR_LIBRARIES ON)
#endif()
#
#set(Python_LOCATION "C:/Program Files/Python310")
#include_directories("C:/Program Files/Python310/include")
#include_directories("C:/github/OpenUSD/include")
## Include vcpkg toolchain
##set(CMAKE_TOOLCHAIN_FILE "C:/Users/17203/Desktop/github/vcpkg/scripts/buildsystems/vcpkg.cmake")
#
##include(${CMAKE_TOOLCHAIN_FILE})
##include("C:\\Users\\17203\\Desktop\\github\\OpenUSD\\pxrConfig.cmake")
#
#set(LIB_DIR "C:\\github\\OpenUSD\\lib")
#
#
#file(GLOB ALL_LIB_FILES
#        "${LIB_DIR}/*.lib"
#)
#
#
#file(GLOB SOURCES "src/*.cpp")
#
#file(GLOB HEADERS "include/*.h")
#
## 打印源文件列表（用于调试：确认是否匹配到文件）
#message(STATUS "找到的源文件: ${SOURCES}")
#message(STATUS "找到的头文件: ${HEADERS}")
#
##find_package(pxr CONFIG REQUIRED)
##find_package(Boost 1.78 REQUIRED COMPONENTS atomic)
#list(APPEND CMAKE_PREFIX_PATH "C:/github/OpenUSD")
#find_package(pxr REQUIRED)
#
#add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
#
## 统一设置输出目录（静态库的输出目录由ARCHIVE_OUTPUT_DIRECTORY控制）
#set_target_properties(${PROJECT_NAME} PROPERTIES
#        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"  # 静态库(.lib)输出到lib目录
#        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"  # 动态库(.dll的导入库)输出到lib目录
#        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"  # 可执行文件输出到bin目录（这里用不到）
#)
#
## 设置公开头文件路径（其他目标链接此库时会自动包含此路径）
#target_include_directories(${PROJECT_NAME}
#        PUBLIC
#        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  # 构建时的头文件路径
#        $<INSTALL_INTERFACE:include>                    # 安装后的头文件路径（可选）
#)
#
#
#target_link_libraries(${PROJECT_NAME} PRIVATE
#        ${USD_LIBRARIES}
#        ${ALL_LIB_FILES}
#        "C:/Program Files/Python310/libs/python310.lib")
#
#target_include_directories(${PROJECT_NAME} PRIVATE ${USD_INCLUDE_DIRS})
#
## 可选：设置动态库输出目录
#set_target_properties(${PROJECT_NAME} PROPERTIES
#        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
#        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
#)
#
#
##if(WIN32)
##    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
##
##
##    add_custom_command(TARGET usd_action POST_BUILD
##            COMMAND ${CMAKE_COMMAND} -E copy_directory
##            "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/bin"
##            $<TARGET_FILE_DIR:usd_action>
##    )
##
##    target_compile_definitions(usd_action PRIVATE
##            PXR_PLUGIN_BUILD_SET=1
##    )
##endif()

cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME "usd_action")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
add_compile_options(/utf-8)
add_definitions(-DNOMINMAX)

find_package(behaviortree_cpp CONFIG REQUIRED)
include_directories("C:/Program Files/Python310/include")

include_directories("C:/github/OpenUSD/include")

set(LIB_DIR "C:\\github\\OpenUSD\\lib")

file(GLOB ALL_LIB_FILES
        "${LIB_DIR}/*.lib"
)

set(Python_LOCATION "C:/Program Files/Python310")
include_directories("C:/Program Files/Python310/include")
list(APPEND CMAKE_PREFIX_PATH "C:/github/OpenUSD")
find_package(pxr REQUIRED)

file(GLOB SOURCES "src/*.cpp")

file(GLOB HEADERS "include/*.h")

# 打印源文件列表（用于调试：确认是否匹配到文件）
message(STATUS "找到的源文件: ${SOURCES}")
message(STATUS "找到的头文件: ${HEADERS}")
add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

# 统一设置输出目录（静态库的输出目录由ARCHIVE_OUTPUT_DIRECTORY控制）
set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"  # 静态库(.lib)输出到lib目录
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"  # 动态库(.dll的导入库)输出到lib目录
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"  # 可执行文件输出到bin目录（这里用不到）
)

# 设置公开头文件路径（其他目标链接此库时会自动包含此路径）
target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  # 构建时的头文件路径
        $<INSTALL_INTERFACE:include>                    # 安装后的头文件路径（可选）
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        ${USD_LIBRARIES}
        ${ALL_LIB_FILES}
        "C:/Program Files/Python310/libs/python310.lib"
        BT::behaviortree_cpp
)