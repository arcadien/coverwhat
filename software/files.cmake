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
)

if(AVR)
  list(APPEND UNIT_TESTS Atmega328pTest.cpp)
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

