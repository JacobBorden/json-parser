cmake_minimum_required(VERSION 3.0.0)
project(json_parser VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(json_parser json.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
add_executable(my_test test.cpp)
target_link_libraries(my_test PRIVATE json_parser)
add_test(NAME my_test COMMAND ./my_test)
add_executable(my_test2 test2.cpp)
target_link_libraries(my_test2 PRIVATE json_parser)
add_test(NAME my_test2 COMMAND ./my_test2)
