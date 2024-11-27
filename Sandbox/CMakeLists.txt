# SandBox们

# 拷贝资源文件夹
file(COPY ${CMAKE_SOURCE_DIR}/Resources DESTINATION ${EXECUTABLE_OUTPUT_PATH})

# demo1
file(GLOB_RECURSE DEMO1_SOURCE_FILES demo1/src/**.cpp)

add_executable(demo1 ${DEMO1_SOURCE_FILES})
target_link_libraries(demo1 PRIVATE Lambix::Engine)