cmake_minimum_required(VERSION 3.0.0)
project(json_parser VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(json_parser json.cpp)

add_executable(test_skip_comment test_skip_comment.cpp)
target_link_libraries(test_skip_comment json_parser)
add_test(NAME test_skip_comment COMMAND test_skip_comment)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
