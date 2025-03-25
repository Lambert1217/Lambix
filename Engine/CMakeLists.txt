# 设置CMake最低版本要求
cmake_minimum_required(VERSION 3.27)

# 定义项目名称
project(LambixEngine VERSION 0.1)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 使用GLOB_RECURSE命令递归地查找所有的.cpp文件
file(GLOB_RECURSE SOURCE_FILES 
    "src/Core/**.cpp"
    "src/ECS/**.cpp"
    "src/Events/**.cpp"
    "src/Imgui/**.cpp"
    "src/Log/**.cpp"
    "src/Math/**.cpp"
    "src/Renderer/**.cpp"
    "src/Resource/**.cpp"
    "src/Utils/**.cpp"
    "src/Assets/**.cpp"
)
# 头文件
file(GLOB_RECURSE HEADER_FILES 
    "src/Core/**.h"
    "src/ECS/**.h"
    "src/Events/**.h"
    "src/Imgui/**.h"
    "src/Log/**.h"
    "src/Math/**.h"
    "src/Renderer/**.h"
    "src/Resource/**.h"
    "src/Utils/**.h"
    "src/Assets/**.h"
)

# 查找并配置第三方库
find_package(spdlog CONFIG REQUIRED) # 配置并查找spdlog库
find_package(glfw3 CONFIG REQUIRED) # 配置并查找GLFW3库
find_package(glm CONFIG REQUIRED)   # 配置并查找GLM库
find_package(imgui CONFIG REQUIRED) # 配置并查找Imgui
find_package(Stb REQUIRED) # 配置并查找Stb
find_package(EnTT CONFIG REQUIRED) # 配置并查找EnTT
find_package(assimp CONFIG REQUIRED) # 配置并查找assimp
find_package(yaml-cpp CONFIG REQUIRED) #配置并查找yaml-cpp

# 创建一个名为lbx的库
add_library(lbx "")

# 创建别名
add_library(Lambix::Engine ALIAS lbx)

# 设置编译类型
target_compile_definitions(lbx PUBLIC 
    $<$<CONFIG:Debug>:LAMBIX_DEBUG>
)

# 根据操作系统定义平台相关的宏，并收集平台相关的源文件
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(lbx PUBLIC LAMBIX_OS_WINDOWS)
    file(GLOB_RECURSE PLATFORM_SOURCE_FILES "src/Platform/Window/**.cpp")
    file(GLOB_RECURSE PLATFORM_HEADER_FILES "src/Platform/Window/**.h")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_definitions(lbx PUBLIC LAMBIX_OS_APPLE)
    file(GLOB_RECURSE PLATFORM_SOURCE_FILES "src/Platform/Window/**.cpp")
    file(GLOB_RECURSE PLATFORM_HEADER_FILES "src/Platform/Window/**.h")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_definitions(lbx PUBLIC LAMBIX_OS_LINUX)
    file(GLOB_RECURSE PLATFORM_SOURCE_FILES "src/Platform/Window/**.cpp")
    file(GLOB_RECURSE PLATFORM_HEADER_FILES "src/Platform/Window/**.h") 
else()
    target_compile_definitions(lbx PUBLIC LAMBIX_OS_UNKNOWN)
endif()

# 定义渲染后端选项
option(USE_OPENGL "Use OpenGL for rendering" ON)
option(USE_VULKAN "Use Vulkan for rendering" OFF)

# 根据选定的渲染后端来配置源文件和宏
if(USE_OPENGL)
    find_package(glad CONFIG REQUIRED) # 配置并查找GLAD库
    target_compile_definitions(lbx PUBLIC LAMBIX_USE_OPENGL GLFW_INCLUDE_NONE)
    file(GLOB_RECURSE RENDERER_BACKEND_SOURCE_FILES "src/Backend/OpenGL/**.cpp")
    file(GLOB_RECURSE RENDERER_BACKEND_HEADER_FILES "src/Backend/OpenGL/**.h")
elseif(USE_VULKAN)
    # 这里应该添加Vulkan的相关配置
    # find_package(Vulkan REQUIRED)
    # target_compile_definitions(lbx PUBLIC LAMBIX_USE_VULKAN)
    # file(GLOB_RECURSE RENDERER_BACKEND_SOURCE_FILES "src/Backend/Vulkan/**.cpp")
    # target_link_libraries(lbx PUBLIC Vulkan::Vulkan)
endif()

# 将所有源文件添加到库中
target_sources(lbx PUBLIC
        ${SOURCE_FILES}
        ${HEADER_FILES}
        ${PLATFORM_SOURCE_FILES}
        ${PLATFORM_HEADER_FILES}
        ${RENDERER_BACKEND_SOURCE_FILES}
        ${RENDERER_BACKEND_HEADER_FILES}
)

# 设置包含目录
target_include_directories(lbx
        PUBLIC
        "src"
        PRIVATE
        ${Stb_INCLUDE_DIR}
)

# 添加预编译头文件
target_precompile_headers(lbx PUBLIC "src/lbpch.h")

# 链接第三方库
target_link_libraries(lbx
        PUBLIC
        spdlog::spdlog
        glm::glm
        imgui::imgui
        PRIVATE
        glfw
        glad::glad
        EnTT::EnTT
        assimp::assimp
        yaml-cpp::yaml-cpp
)
