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

cmake_minimum_required(VERSION 3.10)

project(Koth VERSION 0.1.0)

set(PROJECT_NAME "koth")

set(CMAKE_CXX_STANDARD 11)

include(software/files.cmake)

set(SOURCES_DIR "${CMAKE_SOURCE_DIR}/software")

set( CMAKE_EXPORT_COMPILE_COMMANDS ON ) 
if( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
  EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json)
endif()

set(${PROJECT_NAME}_LIB_SRC )
foreach(_header ${LIB_H})
  list(APPEND ${PROJECT_NAME}_LIB_SRC "${SOURCES_DIR}/${_header}")
endforeach()
foreach(_source ${LIB_CPP})
  list(APPEND ${PROJECT_NAME}_LIB_SRC "${SOURCES_DIR}/${_source}")
endforeach()

include_directories("${SOURCES_DIR}/include/")

include_directories("${SOURCES_DIR}/third_party/unity/src/")

include(CTest)
enable_testing()

if(AVR)
  include(tools/cmake/avr.cmake)
else()
  include(tools/cmake/pc.cmake)
endif()
