
cmake_minimum_required(VERSION 3.12)
project(Coverwhat VERSION 0.1.0)


add_definitions("-DF_CPU=${MCU_SPEED}")

if(WIN32)
  message("-- Compiling for Windows")
  set(LIB_LOWPOWER_SOURCES )
elseif(UNIX)
  message("-- Compiling for Linux")
  set(LIB_LOWPOWER_SOURCES )
else()
  message("-- Compiling for AVR")
  set(LIB_LOWPOWER_SOURCES "${CMAKE_SOURCE_DIR}/third_party/Low-Power/LowPower.cpp")
endif()

#set(PLAYER_SOURCES ${LIB_LOWPOWER_SOURCES} "${CMAKE_SOURCE_DIR}/src/marker/marker.cpp")
#set(MARKER_SOURCES ${LIB_LOWPOWER_SOURCES} "${CMAKE_SOURCE_DIR}/src/player/player.cpp")
set(COMMON_SOURCES )
set(PLAYER_SOURCES )
set(MARKER_SOURCES )
set(SOURCES ${MARKER_SOURCES} ${PLAYER_SOURCES})

##########################################################################
# set compiler options for build types
##########################################################################
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

include_directories("${CMAKE_SOURCE_DIR}/")
include_directories("${CMAKE_SOURCE_DIR}/include/")
include_directories("${CMAKE_SOURCE_DIR}/third_party/unity/src/")

if(AVR)
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
  add_avr_library(unity third_party/unity/src/unity.c)
  set_target_properties(Player PROPERTIES LINK_FLAGS "--wrap main" )
  set_target_properties(Marker PROPERTIES LINK_FLAGS "--wrap main" )
else()
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
 SimulatedHardwareTest.cpp
)


foreach(test_ ${TESTS})

  if(AVR)
    add_avr_executable(${test_}_driver tests/${test_} ${SOURCES})
    avr_target_link_libraries(${test_}_driver unity)
  else()
    add_executable(${test_}_driver tests/${test_})
    target_link_libraries(${test_}_driver unity)
    target_link_libraries(${test_}_driver atomic)
    target_link_libraries(${test_}_driver log)
  endif()
  add_test(${test_}_driver ${test_}_driver)
endforeach()
