set(UNIT_TESTS 
  ActionTest.cpp 
  SoftwareTransportTest.cpp 
  WeaponTest.cpp 
  VampireTest.cpp)

if(NOT AVR)
  list(APPEND UNIT_TESTS SimulatorTest.cpp)
endif()


