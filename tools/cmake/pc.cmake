#
# This file is part of the KOTH distribution (https://github.com/arcadien/koth)
#
# Copyright (c) 2019 Aurélien Labrosse
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 3.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#

#
# This Cmake scripts perform project
# configuration for non-embedded PC
#

add_definitions("-Werror") 
add_definitions("-pedantic-errors")

file(GLOB SIMULATOR_SRC "${SOURCES_DIR}/src/hardware/simulator/*.cpp")

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_LIB_SRC} ${SIMULATOR_SRC})
add_library(unity STATIC "${SOURCES_DIR}/third_party/unity/src/unity.c")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(ConsolePlayer "${SOURCES_DIR}/src/player/ConsolePlayer.cpp")
target_link_libraries(ConsolePlayer ${PROJECT_NAME})
target_link_libraries(ConsolePlayer Threads::Threads)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  target_link_libraries(ConsolePlayer atomic)
endif()

foreach(test_ ${UNIT_TESTS})

  add_executable(${test_}_driver ${SOURCES_DIR}/tests/${test_})
  target_link_libraries(${test_}_driver Threads::Threads)
  target_link_libraries(${test_}_driver ${PROJECT_NAME})
  target_link_libraries(${test_}_driver unity)
  
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_link_libraries(${test_}_driver atomic)
  endif()
  add_test(${test_}_driver ${test_}_driver)

endforeach()

if(WITH_COVERAGE)
  include(tools/cmake/coverage.cmake)
endif()
