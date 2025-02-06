cmake_minimum_required(VERSION 3.5.0)
project(Trader VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED off)
set(CMAKE_CXX_EXTENSIONS off)

set(THREADS_PREFER_PTHREAD_FLAG ON)


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(Trader main.cpp)
