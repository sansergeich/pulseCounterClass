# About

This is just training for memory and power effective pulse counter module implementation.

## Contain

Repository will contain following items:
* pulseCounter implementation
* library test utility and example
* readme, how to use library

## Concept

Pulse counter module idea is to provide simple to use class with following features:
* power efficiency, can be used with sleep modes and so on;
* provide detailed log, snapped to real time, stored on internal device flash storage with any type of storage.
    * every pulse logged  method (priority)
    * time-sliced logging method

## Interface

T.B.D.

## Build
### Test build
Test builds are performed under WSL using g++ and make tool chain.
If needed, tool chain can be installed with with following commands:
```
sudo apt-get update
sudo apt-get install gcc g++ make git
```

To run first simple test application should be executed:
```
make
./build/test
```

T.B.D.
