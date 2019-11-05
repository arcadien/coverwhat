@echo off
rem 
rem  This file is part of the KOTH distribution (https://github.com/arcadien/koth)
rem 
rem  Copyright (c) 2019 Aurélien Labrosse
rem 
rem  This program is free software: you can redistribute it and/or modify
rem  it under the terms of the GNU General Public License as published by
rem  the Free Software Foundation, version 3.
rem 
rem  This program is distributed in the hope that it will be useful, but
rem  WITHOUT ANY WARRANTY; without even the implied warranty of
rem  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
rem  General Public License for more details.
rem 
rem  You should have received a copy of the GNU General Public License
rem  along with this program. If not, see <http://www.gnu.org/licenses/>.
rem 
rem 
rem To use this script, Arduino IDE must installed in C:/Program Files (x86)/Arduino/.
rem If not, change the path of Arduino below. Also, the default target is a Arduino pro micro 
rem clocked at 16Mhz.
rem To change these settings, update MCU and BOARD below.
rem 
rem Sample call:
rem
rem ```
rem mkdir build
rem cd build
rem ..\tools\Script\init-avr-windows.bat ..
rem
rem ```

set MCU=atmega328p
set BOARD=standard
set CLOCK=16000000U

cmake  %1                                        ^
-G "Unix Makefiles"                              ^
-DMCU_SPEED=%CLOCK%                              ^
-DAVR_MCU=%MCU%                                  ^
-DBOARD_VARIANT=%BOARD%                          ^
-DCMAKE_BUILD_TYPE=Release                       ^
-DARDUINO_ROOT="C:/Program Files (x86)/Arduino/" ^
-DCMAKE_TOOLCHAIN_FILE=%1\software\third_party\cmake-avr\generic-gcc-avr.cmake


