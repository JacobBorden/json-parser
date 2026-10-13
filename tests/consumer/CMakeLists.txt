cmake_minimum_required(VERSION 3.14)
project(json_parser_consumer LANGUAGES CXX)

if(NOT PARSER_SOURCE)
  message(FATAL_ERROR "PARSER_SOURCE is required")
endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(BUILD_TESTING OFF CACHE BOOL "Disable parser tests in the nested build" FORCE)
add_subdirectory("${PARSER_SOURCE}" parser)

add_executable(consumer_behavior main.cpp)
target_link_libraries(consumer_behavior PRIVATE json_parser)
enable_testing()
add_test(NAME consumer_behavior COMMAND consumer_behavior)
