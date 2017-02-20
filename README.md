# MARS: Microphone Array Real-time System

## Authors

* Author: François Grondin
* Support: François Grondin, Dominic Létourneau

## Features

* Sound Source Localization
* Sound Source Tracking
* Optimized for real-time processing on low-cost hardware

## Articles

Please cite us if you like this framework and use it for your own research:

* Grondin, F. and Michaud, F., "Robust Speech/Non-Speech Discrimination Based on Pitch Estimation for Mobile Robots," Proceedings of the IEEE International Conference Robotics and Automation, 2016
* Grondin, F. and Michaud, F., "Noise Mask for TDOA Sound Source Localization of Speech on Mobile Robots in Noisy Environments," Proceedings of the IEEE International Conference Robotics and Automation, 2016
* Grondin, F. and Michaud, F., "Time Difference of Arrival Estimation based on Binary Frequency Mask for Sound Source Localization on Mobile Robots," Proceedings of the IEEE/RSJ International Conference on Intelligent Robots and Systems, 2015
* Grondin, F., Létourneau, D., Ferland, F. and Michaud, F., "An Open Hardware and Software Microphone Array System for Robotic Applications," Demonstration session of the IEEE International Conference on Human-Robot Interaction, 2013
* Grondin, F., Létourneau, D., Ferland, F., Rousseau, V. and Michaud, F., "The ManyEars Open Framework - Microphone Array Open Software and Open Hardware System for Robotic Applications," Autonomous Robots, pp. 1 - 16, 2013

## Installation

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
6. Compile code with make.

## Run

### From recorded RAW file

MARS can read RAW file format with little endian signed 16-bit or 32-bit PCM samples.
The number of channels must match those specified in the configuration file.
The sample rate of the input RAW file is defined by the processing sample rate *general.fS*, the processing hop size *general.hopSize* and the input hop size *raw.in.hopSize*, as follows: *sample rate = general.fS * raw.in.hopSize / general.hopSize*.

To process a recorded file ```file.raw``` with the configuration file ```config.cfg```, and store the results of localization and tracking in files ```potentialSources.pot.bin``` and ```trackedSources.track.bin```, respectively:

```bin/demo -i file.raw -c config.cfg -o potentialsources.pot.bin -o trackedSources.track.bin```

To process a recorded file ```file.raw``` with the configuration file ```config.cfg```, and print the results in the terminal:

```bin/demo -i file.raw -c config.cfg -v```

### From a sound card

MARS can process the microphone signals in real-time from the acquisition of a sound card (with little endian signed 16-bit or 32-bit PCM samples).
The number of channels must match those specified in the configuration file.
The sample rate of the sound card is defined by the processing sample rate *general.fS*, the processing hop size *general.hopSize* and the input hop size *raw.in.hopSize*, as follows: *sample rate = general.fS * raw.in.hopSize / general.hopSize*.

To process sound from the sound card 3 and subdevice #0, with the configuration file ```config.cfg```, and store the results of localization and tracking in files ```potentialSources.pot.bin``` and ```trackedSources.track.bin```, respectively:

```bin/demo -i hw:3,0 -c config.cfg -o potentialsources.pot.bin -o trackedSources.track.bin```

To process sound from the sound card 3 and subdevice #0, with the configuration file ```config.cfg```, and print the results in the terminal:

```bin/demo -i hw:3,0 -c config.cfg -v```

To record the sound stream from a sound card and store in the RAW file ```recorded.raw```:

```bin/demo -i hw:3,0 -c config.cfg -o recorded.raw```

The sample rate of the output RAW file is defined by the processing sample rate *general.fS*, the processing hop size *general.hopSize* and the output hop size *raw.out.hopSize*, as follows: *sample rate = general.fS * raw.out.hopSize / general.hopSize*.