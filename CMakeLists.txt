cmake_minimum_required (VERSION 3.22)


set(VCPKG_ROOT "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE PATH "")
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT})


MESSAGE( "this var key = ${CMAKE_TOOLCHAIN_FILE}.")

project(CpuRayTracingRenderer)


set(SOURCES
    src/TinyGlm.cpp
    src/Intersection.cpp
    src/Object.cpp
    src/Ray.cpp
    src/MessageQueue.cpp
    src/Renderer.cpp
    src/Scene.cpp
    src/Sphere.cpp
)
add_library(CpuRayTracingRenderer_library STATIC 
    ${SOURCES}
)
target_include_directories(CpuRayTracingRenderer_library
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include/mylib
)


find_package(SDL2 CONFIG REQUIRED)

add_executable(CpuRayTracingRenderer  src/main.cpp)

target_link_libraries(CpuRayTracingRenderer
    PRIVATE 
        CpuRayTracingRenderer_library
)

target_link_libraries(CpuRayTracingRenderer PRIVATE SDL2::SDL2 SDL2::SDL2main)