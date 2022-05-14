cmake_minimum_required (VERSION 3.22)


set(VCPKG_ROOT "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE PATH "")
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT})


MESSAGE( "this var key = ${CMAKE_TOOLCHAIN_FILE}.")

project(CpuRayTracingRenderer)



set(STATIC_LIB_SOURCES
    src/Utils.cpp
    src/TinyGlm.cpp
    src/Intersection.cpp
    src/Object.cpp
    src/Ray.cpp
    src/MessageQueue.cpp
    src/Scene.cpp
    src/Sphere.cpp
    src/IPostProcess.cpp
    src/PostProcessHandle.cpp
    src/Camera.cpp
    src/Triangle.cpp
    src/BVH.cpp
    src/Bound.cpp
    src/PublicSingleton.cpp
    src/Rectangles.cpp
    src/ThreadPool.cpp
    src/IShader.cpp
    src/PBRMaterial.cpp
)

set(EXECUTABLE_SOURCES
    src/main.cpp
    src/Renderer.cpp
    src/SDLWindows.cpp
    src/InputHandle.cpp
)

add_library(CpuRayTracingRenderer_library STATIC 
    ${STATIC_LIB_SOURCES}
)
target_include_directories(CpuRayTracingRenderer_library
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include/mylib
)


find_package(SDL2 CONFIG REQUIRED)

add_executable(CpuRayTracingRenderer  ${EXECUTABLE_SOURCES})



target_link_libraries(CpuRayTracingRenderer
    PRIVATE 
        CpuRayTracingRenderer_library
)

target_link_libraries(CpuRayTracingRenderer PRIVATE SDL2::SDL2 SDL2::SDL2main)


MESSAGE( "this var key = ${CMAKE_CURRENT_BINARY_DIR}.")

