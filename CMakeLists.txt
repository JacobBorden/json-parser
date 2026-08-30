cmake_minimum_required(VERSION 3.0.0)
project(json_parser VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(json_parser json.cpp)

add_executable(test_fractional_part test_fractional_part.cpp)
target_link_libraries(test_fractional_part PRIVATE json_parser)
add_test(NAME test_fractional_part COMMAND test_fractional_part)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
