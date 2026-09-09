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
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_executable(test_memory test_memory.cpp)
target_link_libraries(test_memory json_parser)
add_test(NAME test_memory COMMAND test_memory)
