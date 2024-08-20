file(GLOB_RECURSE CORE_SOURCE_FILES src/**.cpp)

find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_library(lb_core ${CORE_SOURCE_FILES})
target_include_directories(lb_core
        PUBLIC
        include
)
target_link_libraries(lb_core
        PUBLIC
        spdlog::spdlog
        glfw
)