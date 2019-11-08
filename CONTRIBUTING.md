# Contributing to the project

:+1::tada: First off, thanks for taking the time to contribute! :tada::+1:

This document is quite unexisting for now. Please create Github issues for bugs, and open pull requests on changes you want to propose to the project.

# Repository structure

```
features: Gerkin[3]-based description of user-level features which are implemented, by version
|
hardware: Contains Kicad[2] design for hardware part of the project
|
tools:
  |
  |-- scripts: Windows and Linux bootstrap and/or utility scripts 
  |-- cmake: sub-configuration files for CMake[2] build system
|
software
  |
  |-- include: headers file, generic API
  |-- src: cpp files, for either PC and AVR targets
  |-- tests: unit tests
    |
    |-- acceptance: Tests to be run on flashed devices
  | 
  |-- third party: Other libraries embedded in this project

```

- [1] http://www.kicad-pcb.org
- [2] https://cmake.org
- [3] https://cucumber.io/docs/gherkin/reference/

# Development

# Testing

Hack is testing using two distinct technologies. The generic C++ code, as well as code for PC (eg. simulator related code), are unit tested using  [Unity](https://www.throwtheswitch.org/unity) library.
Acceptance tests for embedded code uses [RobotFramework](https://robotframework.org/) and communicates with the devices using a serial port using [SerialLibrary for Robot Framework](https://github.com/whosaysni/robotframework-seriallibrary).