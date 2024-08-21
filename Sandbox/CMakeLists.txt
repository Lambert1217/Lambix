file(GLOB_RECURSE SANDBOX_SOURCE_FILES src/**.cpp)

add_executable(sandbox ${SANDBOX_SOURCE_FILES})
target_link_libraries(sandbox PRIVATE lb_core)