#
# This Cmake scripts perform project
# configuration for non-embedded PC
#

add_definitions("-Werror") 
add_definitions("-pedantic-errors")

file(GLOB SIMULATOR_SRC "${SOURCES_DIR}/src/hardware/simulator/*.cpp")

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_LIB_SRC} ${SIMULATOR_SRC})
add_library(unity STATIC "${SOURCES_DIR}/third_party/unity/src/unity.c")

if(WITH_COVERAGE)
  set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
  set(CMAKE_C_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
endif()

foreach(test_ ${UNIT_TESTS})
  set(THREADS_PREFER_PTHREAD_FLAG ON)
  find_package(Threads REQUIRED)

  add_executable(${test_}_driver ${SOURCES_DIR}/tests/${test_})
  target_link_libraries(${test_}_driver Threads::Threads)
  target_link_libraries(${test_}_driver ${PROJECT_NAME})
  target_link_libraries(${test_}_driver unity)
  
  if(NOT WIN32)
    target_link_libraries(${test_}_driver atomic)
  endif()

  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_link_libraries(${test_}_driver log)
  endif()
  add_test(${test_}_driver ${test_}_driver)
endforeach()
