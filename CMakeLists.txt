cmake_minimum_required(VERSION 3.0.0)
project(json_parser VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

add_library(json_parser json.cpp)

add_executable(json_test test_main.cpp)
target_link_libraries(json_test PRIVATE json_parser)
add_test(NAME json_test COMMAND json_test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
