file(GLOB_RECURSE SOURCE_FILES "src/**.cpp")

# 第三方库
find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# VulkanSdk
#find_package(Vulkan REQUIRED)
#if(Vulkan_FOUND)
#    message(STATUS "Successfully found Vulkan : ${Vulkan_INCLUDE_DIRS}")
#endif()

# 生成库
add_library(lb_engine
        ${SOURCE_FILES}
)

# 编译类型
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(lb_engine PUBLIC LAMBIX_DEBUG)
endif()

# 平台
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(lb_engine PUBLIC LAMBIX_OS_WINDOWS)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_definitions(lb_engine PUBLIC LAMBIX_OS_APPLE)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_definitions(lb_engine PUBLIC LAMBIX_OS_LINUX)
else()
    target_compile_definitions(lb_engine PUBLIC LAMBIX_OS_UNKNOWN)
endif ()

target_include_directories(lb_engine
        PUBLIC
        include
        PRIVATE
        #${Vulkan_INCLUDE_DIRS}
)
# 添加预编译头文件
target_precompile_headers(lb_engine PUBLIC lbpch.h)
# 链接第三方库
target_link_libraries(lb_engine
        PUBLIC
        spdlog::spdlog
        glm::glm
        PRIVATE
        glfw
        #${Vulkan_LIBRARY}
)