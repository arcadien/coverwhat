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

# ############################################################################
# status messages
# ############################################################################
message(STATUS "Current uploadtool is: ${AVR_UPLOADTOOL}")
message(STATUS "Current programmer is: ${AVR_PROGRAMMER}")
message(STATUS "Current upload port is: ${AVR_UPLOADTOOL_PORT}")
message(STATUS "Current uploadtool options are: ${AVR_UPLOADTOOL_OPTIONS}")
message(STATUS "Current MCU is set to: ${AVR_MCU}")
message(STATUS "Current MCU speed (Hz) is set to: ${MCU_SPEED}")
message(STATUS "Current H_FUSE is set to: ${AVR_H_FUSE}")
message(STATUS "Current L_FUSE is set to: ${AVR_L_FUSE}")

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
include_directories("/usr/share/arduino/hardware/arduino/cores/arduino/")
include_directories("/usr/share/arduino/hardware/arduino/variants/standard")

add_avr_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_LIB_SRC})

add_avr_library(unity STATIC "${SOURCES_DIR}/third_party/unity/src/unity.c")

file(GLOB ARDUINO_SRC_CPP
     "/usr/share/arduino/hardware/arduino/cores/arduino/*.cpp")
file(GLOB ARDUINO_SRC_C
     "/usr/share/arduino/hardware/arduino/cores/arduino/*.c")
file(GLOB ARDUINO_INCLUDE
     "/usr/share/arduino/hardware/arduino/cores/arduino/*.h")
add_avr_library(arduino
                STATIC
                ${ARDUINO_SRC_CPP}
                ${ARDUINO_SRC_C}
                ${ARDUINO_INCLUDE})

add_avr_library(lowpower STATIC
                "${SOURCES_DIR}/third_party/Low-Power/LowPower.cpp")
avr_target_link_libraries(lowpower arduino)

file(GLOB IREMOTE_SRC "${SOURCES_DIR}/third_party/iremote/*.cpp")
add_avr_library(iremote STATIC ${IREMOTE_SRC})
avr_target_link_libraries(iremote arduino)
add_avr_executable(Player ${PLAYER_SOURCES})
add_avr_executable(Marker ${MARKER_SOURCES})

avr_target_link_libraries(Player arduino)
avr_target_link_libraries(Player lowpower)
avr_target_link_libraries(Player iremote)
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
