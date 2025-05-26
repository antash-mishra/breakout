cmake_minimum_required(VERSION 3.10)
project(breakout VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(breakout src/main.cpp
  src/game.cpp
  src/resource_manager.cpp
  src/glad.c
  src/shader.cpp
  src/texture.cpp
  src/stb_image.cpp
)

target_include_directories(breakout PRIVATE 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(breakout
    glfw
)