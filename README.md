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

Run
---

For now the library runs prerecorded RAW files. Live processing from a sound card with the ALSA driver will be added soon.
The recommended RAW file format is Little endian signed 16-bit PCM, and no heading.
The number of channels and the sampling rate must match those specified in the configuration file.
To process a recorded file ```file.raw``` with the configuration file ```config.cfg```, and store the results of localization and tracking in files ```potentialSources.dat``` and ```trackedSources.dat```, respectively:

```bin/demo_offline -r file.raw -c config.cfg -p potentialsources.dat -t trackedSources.dat```

We will soon add an option to export the localization and tracking results in XML format.