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

set(LIB_CPP
  ./src/api/IHardware.cpp
  ./src/api/Actor.cpp
  ./src/api/ITransport.cpp
  ./src/transports/Software.cpp
  ./src/weapons/Vampire.cpp
)

set(LIB_H
  ./include/api/IHardware.h
  ./include/api/Meta.h
  ./include/api/Action.h
  ./include/api/Actor.h
  ./include/api/Entity.h
  ./include/api/Team.h
  ./include/api/ITransport.h
  ./include/transports/Software.h
  ./include/actors/Player.h
  ./include/actors/Weapon.h
  ./include/transports/Dummy.h
  ./include/weapons/Vampire.h
)

set(UNIT_TESTS 
  EntityTest.cpp
  ActionTest.cpp 
  SoftwareTransportTest.cpp 
  WeaponTest.cpp 
  DummyTransportTest.cpp
  VampireTest.cpp
  RGBColorTest.cpp
  StringActionFactoryTest.cpp
  PlayerTest.cpp
)

if(AVR)
  
list(APPEND UNIT_TESTS Atmega328pTest.cpp)
  
list(APPEND LIB_H
  ./include/ui/Ssd1306Ui.h
)
list(APPEND LIB_CPP 
  ./src/ui/Ssd1306Ui.cpp
)

else()
  
  list(APPEND UNIT_TESTS 
    ConsoleUiTest.cpp
    SimulatorTest.cpp
  )

  list(APPEND LIB_CPP 
    ./src/hardware/simulator/Simulator.cpp
    ./src/ui/ConsoleUi.cpp
  )
  
  list(APPEND LIB_H 
    ./include/hardware/simulator/Simulator.h
    ./include/ui/ConsoleUi.h
  )
endif()

