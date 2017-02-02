# MARS: Microphone Array Real-time System

Authors
-------

* Author: François Grondin
* Support: François Grondin, Dominic Létourneau

Features
--------

* Real-Time
* Sound Source Localization
* Sound Source Tracking
* Optimized for real-time processing on low-cost hardware

Installation
------------

1. Install CMake if not already installed:
```sudo apt-get install cmake```
2. Install the FFTW library: 
```sudo apt-get install libfftw3-dev```
3. Install the ALSA library:
```sudo apt-get install libasound2-dev```
4. Install the Libconfig library:
```sudo apt-get install libconfig++-dev```
5. Run cmake: 
```cmake CMakeLists.txt```
6. Compile code:
```make```
