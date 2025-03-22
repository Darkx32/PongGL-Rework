cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
set(CMAKE_CXX_STANDARD 17)

project(rework-ponggl VERSION 1.0 LANGUAGES CXX)

find_package(AudioEngine CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(rework-ponggl src/main.cpp src/game.cpp src/rect.cpp src/rigidbody.cpp src/shader.cpp src/circle.cpp)
include_directories(rework-ponggl PRIVATE include)

target_link_libraries(rework-ponggl PRIVATE AudioEngine::AudioEngine)
target_link_libraries(rework-ponggl PRIVATE glad::glad)
target_link_libraries(rework-ponggl PRIVATE imgui::imgui)
target_link_libraries(rework-ponggl PRIVATE SDL3::SDL3)
target_link_libraries(rework-ponggl PRIVATE glm::glm)

add_custom_command(TARGET rework-ponggl POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:rework-ponggl>/assets"
)