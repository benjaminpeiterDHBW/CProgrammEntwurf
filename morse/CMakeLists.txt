cmake_minimum_required(VERSION 3.10)
project(morse C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES "src/*.c")

add_executable(morse main.c ${SOURCES})
