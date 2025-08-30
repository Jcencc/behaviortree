cmake_minimum_required(VERSION 4.0)
project(behaviortree)

set(CMAKE_CXX_STANDARD 20)

include("C:\\Users\\17203\\Desktop\\github\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake")
find_package(behaviortree_cpp CONFIG REQUIRED)
find_package(OpenCV REQUIRED)


add_subdirectory(action)
add_executable(behaviortree main.cpp)
# 关键：添加action的头文件目录，让编译器能找到ScreenCheck.h
target_include_directories(behaviortree PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/action/include  # 指向action的include目录
)
target_include_directories(behaviortree PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(behaviortree PRIVATE BT::behaviortree_cpp action ${OpenCV_LIBS})

