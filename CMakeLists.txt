cmake_minimum_required(VERSION 3.0.0)

project(OpenGL-Engine VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(OpenGL-Engine src/main.cpp)
target_include_directories(OpenGL-Engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(OpenGL-Engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-windows/include")

set(glfw3_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-windows/share/glfw3")
find_package(glfw3 REQUIRED)
target_link_libraries(OpenGL-Engine glfw)

set(glad_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-windows/share/glad")
find_package(glad REQUIRED)
target_link_libraries(OpenGL-Engine glad::glad)

find_path(LINMATH_INCLUDE_DIRS "linmath.h/linmath.h")
target_link_directories(OpenGL-Engine PRIVATE ${LINMATH_INCLUDE_DIRS})

set(imgui_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-windows/share/imgui")
find_package(imgui REQUIRED)
target_link_libraries(OpenGL-Engine imgui::imgui)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
