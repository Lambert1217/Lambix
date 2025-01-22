# 设置CMake最低版本要求
cmake_minimum_required(VERSION 3.27)

# 定义项目名称
project(demo1)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)

# 拷贝资源文件夹
file(COPY ${CMAKE_SOURCE_DIR}/Resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# demo1
file(GLOB_RECURSE SOURCE_FILES src/**.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE Lambix::Engine)