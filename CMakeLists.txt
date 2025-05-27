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
  src/sprite_renderer.cpp
)

target_include_directories(breakout PRIVATE 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Copy resources directory to the build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(breakout
    glfw
)