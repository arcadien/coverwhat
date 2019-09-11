cmake_minimum_required(VERSION 3.12)
project(Coverwhat VERSION 0.1.0)
set (CMAKE_CXX_STANDARD 11)

add_definitions("-DF_CPU=${MCU_SPEED}")

if(WIN32)
  message("-- Compiling for Windows")
elseif(UNIX)
  message("-- Compiling for Linux")
else()
  message("-- Compiling for AVR")
endif()

# Setup generic API
file(GLOB COVERWHAT_LIB_SRC "${CMAKE_SOURCE_DIR}/src/api/*.cpp")
include_directories("${CMAKE_SOURCE_DIR}/include/")

set(PLAYER_SOURCES "${CMAKE_SOURCE_DIR}/src/marker/Marker.cpp")
set(MARKER_SOURCES "${CMAKE_SOURCE_DIR}/src/player/Player.cpp")

##########################################################################
# set compiler options for build types
##########################################################################

include_directories("${CMAKE_SOURCE_DIR}/")
include_directories("${CMAKE_SOURCE_DIR}/third_party/unity/src/")

if(AVR)
  
  if(CMAKE_BUILD_TYPE MATCHES Release)
     set(CMAKE_C_FLAGS_RELEASE "-Os")
     set(CMAKE_CXX_FLAGS_RELEASE "-Os")
  endif(CMAKE_BUILD_TYPE MATCHES Release)

  if(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
     set(CMAKE_C_FLAGS_RELWITHDEBINFO "-Os -save-temps -g -gdwarf-3 -gstrict-dwarf")
     set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Os -save-temps -g -gdwarf-3 -gstrict-dwarf")
  endif(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)

  if(CMAKE_BUILD_TYPE MATCHES Debug)
     set(CMAKE_C_FLAGS_DEBUG "-O0 -save-temps -g -gdwarf-3 -gstrict-dwarf")
     set(CMAKE_CXX_FLAGS_DEBUG "-O0 -save-temps -g -gdwarf-3 -gstrict-dwarf")
  endif(CMAKE_BUILD_TYPE MATCHES Debug)

  add_definitions("-DARDUINO=101")
  include_directories("${CMAKE_SOURCE_DIR}/third_party/avr/Low-Power/")
  include_directories("${CMAKE_SOURCE_DIR}/third_party/avr/iremote/")
  include_directories("/usr/share/arduino/hardware/arduino/cores/arduino/")
  include_directories("/usr/share/arduino/hardware/arduino/variants/standard")

  add_avr_library(coverwhat STATIC ${COVERWHAT_LIB_SRC})

  add_avr_library(unity third_party/unity/src/unity.c)

  file(GLOB ARDUINO_SRC_CPP "/usr/share/arduino/hardware/arduino/cores/arduino/*.cpp")
  file(GLOB ARDUINO_SRC_C   "/usr/share/arduino/hardware/arduino/cores/arduino/*.c")
  file(GLOB ARDUINO_INCLUDE "/usr/share/arduino/hardware/arduino/cores/arduino/*.h")
  add_avr_library(arduino STATIC ${ARDUINO_SRC_CPP} ${ARDUINO_SRC_C} ${ARDUINO_INCLUDE})

  add_avr_library(lowpower STATIC "${CMAKE_SOURCE_DIR}/third_party/avr/Low-Power/LowPower.cpp")
  avr_target_link_libraries(lowpower arduino)

  file(GLOB IREMOTE_SRC "${CMAKE_SOURCE_DIR}/third_party/iremote/*.cpp")
  add_avr_library(iremote STATIC ${IREMOTE_SRC})
  avr_target_link_libraries(iremote arduino)

  ##########################################################################
  # compiler options for all build types
  ##########################################################################
  add_definitions("-DF_CPU=${MCU_SPEED}")
  add_definitions("-fpack-struct")
  add_definitions("-fshort-enums")
  add_definitions("-Wall")
  #add_definitions("-Werror")
  #add_definitions("-pedantic")
  #add_definitions("-pedantic-errors")
  add_definitions("-funsigned-char")
  add_definitions("-funsigned-bitfields")
  add_definitions("-ffunction-sections")

  ##########################################################################
  # status messages
  ##########################################################################
  message(STATUS "Current uploadtool is: ${AVR_UPLOADTOOL}")
  message(STATUS "Current programmer is: ${AVR_PROGRAMMER}")
  message(STATUS "Current upload port is: ${AVR_UPLOADTOOL_PORT}")
  message(STATUS "Current uploadtool options are: ${AVR_UPLOADTOOL_OPTIONS}")
  message(STATUS "Current MCU is set to: ${AVR_MCU}")
  message(STATUS "Current MCU speed (Hz) is set to: ${MCU_SPEED}")
  message(STATUS "Current H_FUSE is set to: ${AVR_H_FUSE}")
  message(STATUS "Current L_FUSE is set to: ${AVR_L_FUSE}")

  add_avr_executable(Player ${PLAYER_SOURCES})
  add_avr_executable(Marker ${MARKER_SOURCES})

  avr_target_link_libraries(Player arduino)
  avr_target_link_libraries(Player lowpower)
  avr_target_link_libraries(Player iremote)
  avr_target_link_libraries(Player coverwhat)

  avr_target_link_libraries(Marker arduino)
  avr_target_link_libraries(Marker lowpower)
  avr_target_link_libraries(Marker iremote)
  avr_target_link_libraries(Marker coverwhat)

  set_target_properties(Player PROPERTIES LINK_FLAGS "--wrap main" )
  set_target_properties(Marker PROPERTIES LINK_FLAGS "--wrap main" )
else()
  
  file(GLOB SIMULATOR_SRC "${CMAKE_SOURCE_DIR}/src/hardware/simulator/*.cpp")
  
  add_library(coverwhat STATIC ${COVERWHAT_LIB_SRC} ${SIMULATOR_SRC})

  if(WITH_COVERAGE)
    set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
    set(CMAKE_C_FLAGS   "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
  endif()
  add_subdirectory("third_party/unity")
  # add_library(PlayerLib OBJECT ${PLAYER_SOURCES})
  # add_library(MarkerLib OBJECT ${MARKER_SOURCES})
endif()

include(CTest)
enable_testing()

# Scenario Runner
SET(TESTS
 firstTest.cpp
)

if(NOT AVR)
  list(APPEND TESTS
    SimulatorTest.cpp
  )
endif()

foreach(test_ ${TESTS})

  if(AVR)
    add_avr_executable(${test_}_driver tests/${test_})
    avr_target_link_libraries(${test_}_driver unity)
    avr_target_link_libraries(${test_}_driver coverwhat)
  else()
    add_executable(${test_}_driver tests/${test_})
    target_link_libraries(${test_}_driver coverwhat)
    target_link_libraries(${test_}_driver unity)
    target_link_libraries(${test_}_driver atomic)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
      target_link_libraries(${test_}_driver log)
    endif()
  endif()
  add_test(${test_}_driver ${test_}_driver)
endforeach()
