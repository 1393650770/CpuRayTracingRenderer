cmake_minimum_required (VERSION 3.22)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE PATH "")
set(SDL2_DIR "${CMAKE_SOURCE_DIR}/vcpkg/installed/x86-windows/share/sdl2")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/vcpkg/installed/x86-windows/share/sdl2")
project(CpuRayTracingRenderer)

message("cmake_module_path: " ${CMAKE_MODULE_PATH})

add_executable(CpuRayTracingRenderer main.cpp)
