# CoverWhat

The goal is to provide a simple API for FPS game development.
Two implementations will take place:
- one for PC using simulated hardware
- one for current hardware target: a ATMega328p from Microchip (former Atmel)

The main concepts will be _Game_, _Team_, _Actor_, _Action_ and _Protocol_.
A _Game_ maintain global concept, its the space where instances will live. _Actor_ is a generic concept for players and mobs and every instance which have characteristics (named _Entities_) and/or can send and/or receive _Action_.
An _Action_ is the description of an event which can alter a _Actor_ _Entity_.
An _Action_ should be created by a _ActionSource_ and sent to one or more _ActionTarget_. The way _Action_ is transferred is let to a _Protocol_. A _Protocol_ implementation __MUST__ provide an _Emmiter_ and a _Receiver_.
