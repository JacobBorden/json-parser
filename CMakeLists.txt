cmake_minimum_required(VERSION 3.14)
project(json_parser VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(json_parser json.cpp)

target_compile_features(json_parser PUBLIC cxx_std_11)
target_include_directories(json_parser PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
if(BUILD_TESTING)
  add_executable(parser_tests tests/parser_tests.cpp)
  target_link_libraries(parser_tests PRIVATE json_parser)
  foreach(group literals numbers strings arrays invalid)
    add_test(NAME parser_${group} COMMAND parser_tests ${group})
    set_tests_properties(parser_${group} PROPERTIES TIMEOUT 10)
  endforeach()

  add_executable(test_memory_leak tests/test_memory_leak.cpp)
  target_link_libraries(test_memory_leak PRIVATE json_parser)
  add_test(NAME test_memory_leak COMMAND test_memory_leak)

  add_executable(test_escape tests/test_escape.cpp)
  target_link_libraries(test_escape PRIVATE json_parser)
  add_test(NAME test_escape COMMAND test_escape)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
