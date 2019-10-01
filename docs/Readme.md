# CoverWhat

The goal is to provide a simple API for FPS-like game development.

The main concepts will be _Game_, _Team_, _Actor_, _Action_ and _Transport_.
_Actor_, grouped in _Team_, are interacting in a _Game_. _Actor_ should be defined by _entities_, which can be altered by _Action_.
Theses _Action_ are triggered by _Actor_, and are transmitted using _Transport_.
