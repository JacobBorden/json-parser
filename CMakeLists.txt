cmake_minimum_required(VERSION 3.0.0)
project(json_parser VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(json_parser json.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
