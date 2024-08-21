file(GLOB_RECURSE CORE_SOURCE_FILES src/**.cpp)

# 第三方库
find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# VulkanSdk
find_package(Vulkan REQUIRED)
if(Vulkan_FOUND)
    message(STATUS "Successfully found Vulkan : ${Vulkan_INCLUDE_DIRS}")
endif()

# 生成库
add_library(lb_core ${CORE_SOURCE_FILES})
target_include_directories(lb_core
        PUBLIC
        include
)
# 添加预编译头文件, 并自动继承
target_precompile_headers(lb_core PUBLIC include/lbpch.h)
# 链接第三方库
target_link_libraries(lb_core
        PUBLIC
        spdlog::spdlog
        glm::glm
        PRIVATE
        glfw
)
# 链接 Vulkan
target_include_directories(lb_core PRIVATE ${Vulkan_INCLUDE_DIRS})
target_link_libraries(lb_core PRIVATE ${Vulkan_LIBRARY})