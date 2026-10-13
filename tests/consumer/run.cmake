if(NOT CONSUMER_SOURCE OR NOT PARSER_SOURCE OR NOT CONSUMER_BUILD OR
   NOT CONSUMER_STANDARD OR NOT CONSUMER_BUILD_TYPE OR NOT CONSUMER_GENERATOR)
  message(FATAL_ERROR "Consumer runner arguments are incomplete")
endif()

execute_process(
  COMMAND "${CMAKE_COMMAND}" -S "${CONSUMER_SOURCE}" -B "${CONSUMER_BUILD}"
    -G "${CONSUMER_GENERATOR}"
    "-DPARSER_SOURCE=${PARSER_SOURCE}"
    "-DCMAKE_BUILD_TYPE=${CONSUMER_BUILD_TYPE}"
    "-DCMAKE_CXX_STANDARD=${CONSUMER_STANDARD}"
  RESULT_VARIABLE configure_result)
if(NOT configure_result EQUAL 0)
  message(FATAL_ERROR "Consumer configure failed: ${configure_result}")
endif()

execute_process(
  COMMAND "${CMAKE_COMMAND}" --build "${CONSUMER_BUILD}" --config "${CONSUMER_BUILD_TYPE}"
  RESULT_VARIABLE build_result)
if(NOT build_result EQUAL 0)
  message(FATAL_ERROR "Consumer build failed: ${build_result}")
endif()

execute_process(
  COMMAND "${CMAKE_CTEST_COMMAND}" --test-dir "${CONSUMER_BUILD}"
    -C "${CONSUMER_BUILD_TYPE}" --output-on-failure --no-tests=error
  RESULT_VARIABLE test_result)
if(NOT test_result EQUAL 0)
  message(FATAL_ERROR "Consumer test failed: ${test_result}")
endif()
