cmake_minimum_required(VERSION 3.15)

# 定义动态库项目名
project(action LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 定义源文件和头文件
set(ACTION_SOURCES
        src/ScreenCheck.cpp
        src/MoveMouse.cpp
)

set(ACTION_HEADERS
        include/ScreenCheck.h
        include/MoveMouse.h
)

# 创建动态库
add_library(${PROJECT_NAME} STATIC
        ${ACTION_SOURCES}
        ${ACTION_HEADERS}
)
## 2. 为动态库目标添加 BT_PLUGIN_EXPORTS 宏（PRIVATE 修饰）
#target_compile_definitions(action
#        PRIVATE
#        BT_PLUGIN_EXPORTS  # 编译这个 DLL 时，宏生效，BT_PLUGIN_API 解析为 dllexport
#)
set_target_properties(${PROJECT_NAME} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib  # 导入库(.lib)输出到lib目录
)
# 设置公开头文件路径（其他目标链接此库时会自动包含此路径）
target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  # 构建时的头文件路径
        $<INSTALL_INTERFACE:include>                    # 安装后的头文件路径（可选）
)

# 链接BehaviorTree库
find_package(behaviortree_cpp CONFIG REQUIRED)
find_package(OpenCV REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})

# 可选：设置动态库输出目录
set_target_properties(${PROJECT_NAME} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        BT::behaviortree_cpp
        ${OpenCV_LIBS}
)