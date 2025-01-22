# 设置CMake最低版本要求
cmake_minimum_required(VERSION 3.27)

# 定义项目名称
project(LambixEditor)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)

# 拷贝资源文件夹
file(COPY ${CMAKE_SOURCE_DIR}/Resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# lbEditor
file(GLOB_RECURSE SOURCE_FILES src/**.cpp)

# 创建可执行程序
set(EXE_NAME lbEditor)
add_executable(${EXE_NAME} ${SOURCE_FILES})
#头文件
target_include_directories(${EXE_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
# 链接引擎库
target_link_libraries(${EXE_NAME} PRIVATE Lambix::Engine)