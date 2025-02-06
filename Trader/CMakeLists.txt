cmake_minimum_required(VERSION 3.5.0)
project(Trader VERSION 0.1.0 LANGUAGES C CXX)


include_directories(
        ${PROJECT_SOURCE_DIR}/Include
        ${PROJECT_SOURCE_DIR}/src
)

add_compile_options("-ggdb;-O3;-Wall")

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/Include/*.h"
        "${PROJECT_SOURCE_DIR}/Include/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.c"
        )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED off)
set(CMAKE_CXX_EXTENSIONS off)

set(THREADS_PREFER_PTHREAD_FLAG ON)


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(Trader main.cpp ${all_SRCS})
