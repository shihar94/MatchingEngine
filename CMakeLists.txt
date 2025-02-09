cmake_minimum_required(VERSION 3.5.0)
project(Matching_Engine VERSION 0.1.0 LANGUAGES C CXX)

include_directories(
        ${PROJECT_SOURCE_DIR}/Include
        ${PROJECT_SOURCE_DIR}/Common
        ${PROJECT_SOURCE_DIR}/src
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

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


add_executable(Matching_Engine main.cpp ${all_SRCS})
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)


enable_testing()

add_executable(
  hello_test
  hello_test.cpp
)
target_link_libraries(
  hello_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)