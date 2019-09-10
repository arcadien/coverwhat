export MCU=atmega328p
cmake  ../ \
-G "Unix Makefiles" \
-DMCU_SPEED=16000000U \
-DAVR_MCU=$MCU \
-DCMAKE_BUILD_TYPE=Release \
-DCMAKE_TOOLCHAIN_FILE=../third_party/cmake-avr/generic-gcc-avr.cmake


