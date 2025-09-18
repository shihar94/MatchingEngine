cmake_minimum_required(VERSION 3.5.0)
project(Matching_Engine VERSION 0.1.0 LANGUAGES C CXX)

set(LINK_LIBRARIES
    rdmacm
    ibverbs
    xml2
    boost_date_time
    boost_filesystem
    boost_system
    boost_serialization
    boost_thread
    boost_chrono
    rdkafka
    rdkafka++
    clntsh
    nnz19
    lzf
    z
    ssl
    crypto
    nsl
    rt
    dl
    z
    crypt
    numa
    )


include_directories(
        ${PROJECT_SOURCE_DIR}/Include
        ${PROJECT_SOURCE_DIR}/Common
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/OrderClass
)

find_package(GTest CONFIG REQUIRED)


add_compile_options("-ggdb;-O3;-Wall")

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/Include/*.h"
        "${PROJECT_SOURCE_DIR}/Include/kafka/*.h"
        "${PROJECT_SOURCE_DIR}/Include/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/kafka/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.c"
        "${PROJECT_SOURCE_DIR}/test/*.cpp"
        "${PROJECT_SOURCE_DIR}/OrderClass/*.cpp"
        )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED off)
set(CMAKE_CXX_EXTENSIONS off)

find_package(Threads REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)


add_subdirectory(src/kafka)
list(APPEND EXTRA_LIB_DIRS "kafka")
list(APPEND EXTRA_INCLUDE_DIRS "kafka")
list(APPEND EXTRA_LINKS kafkaPublisher)

find_package(PkgConfig REQUIRED)
pkg_check_modules(rdkafka REQUIRED IMPORTED_TARGET rdkafka)


find_package(PkgConfig REQUIRED)
pkg_check_modules(rdkafka++ REQUIRED IMPORTED_TARGET rdkafka++)

find_package(nlohmann_json 3.7.0 REQUIRED)


find_package(Threads REQUIRED)

link_libraries(rdkafka++)
link_libraries(rdkafka)
link_libraries(pthread)

add_executable(${PROJECT_NAME} main.cpp ${all_SRCS})

target_link_libraries(${PROJECT_NAME} pthread librdkafka++.a librdkafka.a crypto ssl nlohmann_json::nlohmann_json)


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
  #GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)
