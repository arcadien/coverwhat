#
# This file is part of the Hack distribution (https://github.com/arcadien/Hack)
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
# configuration for AVR chip target
#
# uploadtool is: AVR_UPLOADTOOL
# programmer is: AVR_PROGRAMMER
# upload port is: AVR_UPLOADTOOL_PORT
# uploadtool options are: AVR_UPLOADTOOL_OPTIONS
# MCU is set to: AVR_MCU
# MCU speed (Hz) is set to: MCU_SPEED
# H_FUSE is set to: AVR_H_FUSE
# L_FUSE is set to: AVR_L_FUSE

# ############################################################################
# compiler options for all build types
# ############################################################################
add_definitions("-DF_CPU=${MCU_SPEED}")
add_definitions("-std=gnu++11")
add_definitions("-fpack-struct")
add_definitions("-fshort-enums")
add_definitions("-Wall")
add_definitions("-funsigned-char")
add_definitions("-funsigned-bitfields")
add_definitions("-ffunction-sections")
add_definitions("-DARDUINO=101")

# Do not use on library
#add_definitions("-flto")

set(AVR_BINARIES "${ARDUINO_ROOT}/hardware/tools/avr/bin")
message("-- Using AVR toolchain binaries in ${AVR_BINARIES}")

find_program(AVR_CC avr-gcc HINTS ${AVR_BINARIES})
find_program(AVR_CXX avr-g++ HINTS ${AVR_BINARIES})
find_program(AVR_OBJCOPY avr-objcopy HINTS ${AVR_BINARIES})
find_program(AVR_SIZE_TOOL avr-size HINTS ${AVR_BINARIES})
find_program(AVR_OBJDUMP avr-objdump HINTS ${AVR_BINARIES})

# ############################################################################
# status messages
# ############################################################################
message(STATUS "Current C compiler is: ${AVR_CC}")
message(STATUS "Current C++ compiler is: ${AVR_CXX}")
message(STATUS "Current OBJCOPY is: ${AVR_OBJCOPY}")
message(STATUS "Current AVR_SIZE_TOOL is: ${AVR_SIZE_TOOL}")
message(STATUS "Current AVR_OBJDUMP is: ${AVR_OBJDUMP}")

message(STATUS "Current uploadtool is: ${AVR_UPLOADTOOL}")
message(STATUS "Current programmer is: ${AVR_PROGRAMMER}")
message(STATUS "Current upload port is: ${AVR_UPLOADTOOL_PORT}")
message(STATUS "Current uploadtool options are: ${AVR_UPLOADTOOL_OPTIONS}")
message(STATUS "Current MCU is set to: ${AVR_MCU}")
message(STATUS "Current MCU speed (Hz) is set to: ${MCU_SPEED}")
message(STATUS "Current H_FUSE is set to: ${AVR_H_FUSE}")
message(STATUS "Current L_FUSE is set to: ${AVR_L_FUSE}")

if(NOT BOARD_VARIANT)
  set(BOARD_VARIANT "standard")
endif()

message(STATUS "Current board variant is set to : ${BOARD_VARIANT}")

if(CMAKE_BUILD_TYPE MATCHES Release)
  set(CMAKE_C_FLAGS_RELEASE "-Os")
  set(CMAKE_CXX_FLAGS_RELEASE "-Os")
endif(CMAKE_BUILD_TYPE MATCHES Release)

if(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
  set(CMAKE_C_FLAGS_RELWITHDEBINFO
      "-Os -save-temps -g -gdwarf-3 -gstrict-dwarf")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO
      "-Os -save-temps -g -gdwarf-3 -gstrict-dwarf")
endif(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)

if(CMAKE_BUILD_TYPE MATCHES Debug)
  set(CMAKE_C_FLAGS_DEBUG "-O0 -save-temps -g -gdwarf-3 -gstrict-dwarf")
  set(CMAKE_CXX_FLAGS_DEBUG "-O0 -save-temps -g -gdwarf-3 -gstrict-dwarf")
endif(CMAKE_BUILD_TYPE MATCHES Debug)

include_directories("${SOURCES_DIR}/third_party/Low-Power/")
include_directories("${SOURCES_DIR}/third_party/iremote/")


add_avr_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_LIB_SRC})

add_avr_library(unity STATIC "${SOURCES_DIR}/third_party/unity/src/unity.c")

if(NOT ARDUINO_ROOT)
  set(ARDUINO_ROOT "/usr/share/arduino/")
endif()

if(CROSS_FROM_WINDOWS)
  set(ARDUINO_SRC "${ARDUINO_ROOT}/hardware/arduino/avr/cores/arduino/")
  include_directories("${ARDUINO_ROOT}/hardware/arduino/avr/variants/${BOARD_VARIANT}")
  include_directories("${ARDUINO_ROOT}/hardware/tools/avr/avr/include")
else()
  set(ARDUINO_SRC "${ARDUINO_ROOT}/hardware/arduino/cores/arduino/")
  include_directories("${ARDUINO_ROOT}/hardware/arduino/variants/${BOARD_VARIANT}")
endif()

file(GLOB ARDUINO_SRC_CPP "${ARDUINO_SRC}/*.cpp")
file(GLOB ARDUINO_SRC_C   "${ARDUINO_SRC}/*.c")
file(GLOB ARDUINO_INCLUDE "${ARDUINO_SRC}/*.h")

include_directories("${ARDUINO_SRC}")

add_avr_library(arduino
  STATIC
  ${ARDUINO_SRC_CPP}
  ${ARDUINO_SRC_C}
  ${ARDUINO_INCLUDE})

add_avr_library(lowpower STATIC
                "${SOURCES_DIR}/third_party/Low-Power/LowPower.cpp")
avr_target_link_libraries(lowpower arduino)

file(GLOB SSD1306_SRC_C       "${SOURCES_DIR}/third_party/ssd1306/src/*.c")
file(GLOB SSD1306_SRC         "${SOURCES_DIR}/third_party/ssd1306/src/*.cpp")
file(GLOB SSD1306_DEVICES_SRC "${SOURCES_DIR}/third_party/ssd1306/src/lcd/*.c")

add_avr_library(ssd1306 STATIC ${SSD1306_SRC} ${SSD1306_SRC_C} ${SSD1306_DEVICES_SRC})
avr_target_link_libraries(ssd1306 arduino)
avr_target_include_directories(ssd1306 PRIVATE "${SOURCES_DIR}/third_party/ssd1306/src/")
include_directories("${SOURCES_DIR}/third_party/ssd1306/src/")

file(GLOB IREMOTE_SRC "${SOURCES_DIR}/third_party/iremote/*.cpp")
add_avr_library(iremote STATIC ${IREMOTE_SRC})
avr_target_link_libraries(iremote arduino)

set(PLAYER_SOURCES "${SOURCES_DIR}/src/marker/Marker.cpp")
set(MARKER_SOURCES "${SOURCES_DIR}/src/player/PlayerAvr.cpp")

add_avr_executable(Player ${PLAYER_SOURCES})
add_avr_executable(Marker ${MARKER_SOURCES})

avr_target_link_libraries(Player arduino)
avr_target_link_libraries(Player lowpower)
avr_target_link_libraries(Player iremote)
avr_target_link_libraries(Player ssd1306)
avr_target_link_libraries(Player ${PROJECT_NAME})

avr_target_link_libraries(Marker arduino)
avr_target_link_libraries(Marker lowpower)
avr_target_link_libraries(Marker iremote)
avr_target_link_libraries(Marker ${PROJECT_NAME})

set_target_properties(Player PROPERTIES LINK_FLAGS "--wrap main")
set_target_properties(Marker PROPERTIES LINK_FLAGS "--wrap main")

foreach(test_ ${UNIT_TESTS})
  add_avr_executable(${test_}_driver ${SOURCES_DIR}/tests/${test_})
  avr_target_link_libraries(${test_}_driver ${PROJECT_NAME})
  avr_target_link_libraries(${test_}_driver unity)
  avr_target_link_libraries(${test_}_driver m)
  avr_target_link_libraries(${test_}_driver arduino)
  add_test(${test_}_driver ${test_})
endforeach() 
