cmake_minimum_required(VERSION 3.13.4)
set(CMAKE_CXX_STANDARD 14)
enable_testing()

project(pipedcp)
option(PIPEDCP_BUILD_TESTS "Build pipedcp's unit tests" OFF)

file(GLOB SOURCES src/**/*.cpp)

include_directories(include)
add_library(${CMAKE_PROJECT_NAME} ${SOURCES})

# -------------------- gtest --------------------
if (PIPEDCP_BUILD_TESTS)
  configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
  execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
  if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
  endif()
  execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
  if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
  endif()

  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

  add_subdirectory(
    ${CMAKE_CURRENT_BINARY_DIR}/googletest-src
    ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
    EXCLUDE_FROM_ALL
  )

  add_executable(process_test test/process_test.cpp ${SOURCES})
  target_link_libraries(process_test gtest_main)
  add_test(NAME process_test COMMAND process_test)
endif()
# -------------------- end gtest --------------------
