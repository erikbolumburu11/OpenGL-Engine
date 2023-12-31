cmake_minimum_required(VERSION 3.0.0)

project(OpenGL-Engine VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

file(GLOB sources CONFIGURE_DEPENDS "src/*.cpp" "src/Components/*.cpp")

add_executable(OpenGL-Engine "${sources}") 
target_include_directories(OpenGL-Engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(OpenGL-Engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/ext")
target_include_directories(OpenGL-Engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-windows/include")

set(glfw3_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-windows/share/glfw3")
find_package(glfw3 REQUIRED)
target_link_libraries(OpenGL-Engine glfw)

set(glad_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-windows/share/glad")
find_package(glad REQUIRED)
target_link_libraries(OpenGL-Engine glad::glad)

set(glm_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-windows/share/glm")
find_package(glm REQUIRED)
target_link_libraries(OpenGL-Engine glm::glm)

set(entt_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-windows/share/entt")
find_package(entt REQUIRED)
target_link_libraries(OpenGL-Engine EnTT::EnTT)

set(imgui_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-windows/share/imgui")
find_package(imgui REQUIRED)
target_link_libraries(OpenGL-Engine imgui::imgui)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)