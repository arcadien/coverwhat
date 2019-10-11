
set(UNIT_TESTS 
  ActionTest.cpp 
  SoftwareTransportTest.cpp 
  WeaponTest.cpp 
  VampireTest.cpp)

if(NOT AVR)
  list(APPEND UNIT_TESTS SimulatorTest.cpp)
endif()

set(LIB_H
  ./include/api/IHardware.h
  ./include/api/Meta.h
  ./include/api/Action.h
  ./include/api/Actor.h
  ./include/api/Entity.h
  ./include/api/ITransport.h
  ./include/actors/Player.h
  ./include/actors/Weapon.h
  ./include/transports/Software.h
  ./include/transports/Dummy.h
  ./include/weapons/Vampire.h
)

set(LIB_CPP
  ./src/api/IHardware.cpp
  ./src/api/Actor.cpp
  ./src/api/ITransport.cpp
  ./src/weapons/Vampire.cpp
  ./src/transports/Software.cpp
)

if(NOT AVR)
  list(APPEND LIB_CPP
    ./src/hardware/simulator/Simulator.cpp
  )

  list(APPEND LIB_H
    ./include/hardware/simulator/Simulator.h
  )
endif()

