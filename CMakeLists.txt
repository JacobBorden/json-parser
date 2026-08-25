cmake_minimum_required(VERSION 3.0.0)
project(json_parser VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(json_parser json.cpp)

add_executable(test_parser_bugs test_parser_bugs.cpp)
target_link_libraries(test_parser_bugs json_parser)
add_test(NAME test_parser_bugs COMMAND test_parser_bugs)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
