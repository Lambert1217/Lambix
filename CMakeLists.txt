cmake_minimum_required(VERSION 3.27)

# 本项目使用vcpkg进行包管理，此处设置三元组（须在project()之前）
set(VCPKG_TARGET_TRIPLET "x64-mingw-dynamic")

project(Lambix)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Engine)
add_subdirectory(Sandbox)
