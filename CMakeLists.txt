cmake_minimum_required(VERSION 3.15)
project(behaviortree)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(/utf-8)  # 确保中文编译正常

# 针对MSVC编译器设置运行时库（静态链接）
if(MSVC)
    # 清除可能存在的动态运行时库标志
    foreach(flag_var
            CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
        string(REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        string(REPLACE "/MDd" "/MTd" ${flag_var} "${${flag_var}}")
    endforeach()

    # 显式添加静态运行时库标志
    add_compile_options(
            $<$<CONFIG:Debug>:/MTd>
            $<$<CONFIG:Release>:/MT>
            $<$<CONFIG:RelWithDebInfo>:/MT>
            $<$<CONFIG:MinSizeRel>:/MT>
    )
endif()

# 禁用Windows的min/max宏
add_definitions(-DNOMINMAX)

include("C:\\github\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake")
find_package(behaviortree_cpp CONFIG REQUIRED)
find_package(OpenCV REQUIRED)


add_subdirectory(action)
add_subdirectory(usd_action)
add_executable(behaviortree main.cpp)
# 关键：添加action的头文件目录，让编译器能找到ScreenCheck.h
target_include_directories(behaviortree PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/action/include  # 指向action的include目录
        ${CMAKE_CURRENT_SOURCE_DIR}/usd_action/include
)
target_include_directories(behaviortree PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(behaviortree PRIVATE BT::behaviortree_cpp action usd_action ${OpenCV_LIBS} )

