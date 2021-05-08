cmake_minimum_required(VERSION 3.14)

project(oopGL)

file(GLOB SRC Sources/main.cpp Sources/*/*.hpp Sources/*/*.cpp)
include_directories(Sources)
link_directories(Sources)

add_executable(${PROJECT_NAME} ${SRC})
