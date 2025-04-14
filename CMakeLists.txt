cmake_minimum_required(VERSION 3.5.0)
project(Matching_Engine VERSION 0.1.0 LANGUAGES C CXX)

include_directories(
        ${PROJECT_SOURCE_DIR}/Include
        ${PROJECT_SOURCE_DIR}/Common
        ${PROJECT_SOURCE_DIR}/src
)

find_package(GTest CONFIG REQUIRED)


add_compile_options("-ggdb;-O3;-Wall")

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/Include/*.h"
        "${PROJECT_SOURCE_DIR}/Include/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.c"
        "${PROJECT_SOURCE_DIR}/test/*.cpp"
        )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED off)
set(CMAKE_CXX_EXTENSIONS off)

find_package(Threads REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(rdkafka REQUIRED IMPORTED_TARGET rdkafka)


find_package(PkgConfig REQUIRED)
pkg_check_modules(rdkafka++ REQUIRED IMPORTED_TARGET rdkafka++)

find_package(Threads REQUIRED)

add_executable(Matching_Engine main.cpp ${all_SRCS})

target_link_libraries(${PROJECT_NAME} PUBLIC PkgConfig::rdkafka)
target_link_libraries(${PROJECT_NAME}  PUBLIC PkgConfig::rdkafka++)


target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

add_executable(testingScript testingScript.cpp ${all_SRCS})

enable_testing()

add_executable(
  hello_test
  hello_test.cpp
  ${all_SRCS}
)
target_link_libraries(
  hello_test
  GTest::gtest_main
  GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)
