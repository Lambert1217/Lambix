# SandBox们

# 拷贝着色器文件夹
file(COPY ${CMAKE_SOURCE_DIR}/OtherFiles/Shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# demo1
file(GLOB_RECURSE DEMO1_SOURCE_FILES demo1/src/**.cpp)

add_executable(demo1 ${DEMO1_SOURCE_FILES})
target_link_libraries(demo1 PRIVATE Lambix::Engine)