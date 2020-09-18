cmake_minimum_required(VERSION 3.13.4)
enable_testing()

set(MAIN_NAME "pipedcp")

project(${MAIN_NAME})

set(EXEC ${MAIN_NAME})
set(CMAKE_CXX_STANDARD 14)

set(PIPEDCP_BUILD_TEST "Build pipedcp's unit tests" ON)

include_directories(include)
file(GLOB SOURCES src/**/*.cpp)

add_library(${EXEC} ${SOURCES})

# -------------------- gtest --------------------
if (PIPEDCP_BUILD_TEST)
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
endif(PIPEDCP_BUILD_TEST)
# -------------------- end gtest --------------------
