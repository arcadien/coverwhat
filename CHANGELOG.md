# Changelog

## Milestone 2 - API 1.1 - Not yet released

### Functional
- 

### Technical
- The compilation, test and firmware compilation is automated
- Unit test for embedded code is automated
- Acceptance test and game scenario can be prepared offgame and tested on a test environment

### Concepts
- __HackPoint__: A new kind of passive __Actor__. Players will have to interact with these to accumulate points to victory. The __HackPoint__, when owned by a __Team__, can be used as a spawn points.

## Milestone 1 - API 1.1 - Not yet released

### Functional
- 2 prototypes are available, so that two players can play together. At the end of a given time lapse, the player with the lower count of death wins the game.

### Technical
- Initial version of firmwares for AVR targets
- Tests for hardware devices

### Concepts
- __Team__: Group players in organizations


## Milestone 0 - API 1.0 - 2019/10/24 (commit 2660759)

### Functional
First version of the API allow to model two players with their weapons.

### Technical
Testing harness allow to test API using a simulated hardware on a Linux platform.

### Concepts
* __Actor__: Allow to implement players and weapons
* __Action__: Allow to model the capacities of weapons
* __Transport__: Allow a player weapon to hit another player
* __Entity__: In this version, 'health' entity is implemented

NOTE: For details about implemented use cases, see features/v1/ folder.
