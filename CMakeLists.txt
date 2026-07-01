cmake_minimum_required(VERSION 4.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Graphics)

add_library(my_lib SHARED timer.h timer.cpp)

add_executable(main main.cpp glad.c)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)

target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(main PRIVATE glfw OpenGL::GL glm::glm my_lib)
