cmake_minimum_required(VERSION 3.14)

project(ecs)

file(GLOB SRC include/*.hpp src/*.cpp)
include_directories(include)
link_directories(include)

add_executable(${PROJECT_NAME} ${SRC})
