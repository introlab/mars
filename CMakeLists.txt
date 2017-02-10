cmake_minimum_required(VERSION 2.4.6)

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PC_FFTW3 REQUIRED fftw3f)
pkg_check_modules(PC_ALSA REQUIRED alsa)
pkg_check_modules(PC_LIBCONFIG REQUIRED libconfig)

include_directories(${PC_FFTW3_INCLUDE_DIRS} ${PC_ALSA_INCLUDE_DIRS} "${PROJECT_SOURCE_DIR}/include")
link_directories(${PC_FFTW3_LIBRARY_DIRS} ${PC_ALSA_LIBRARY_DIRS})

set(CMAKE_BUILD_TYPE "Release")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib")

set(SRC

    src/general/arguments.c
    src/general/configs.c
    src/general/name.c
    src/general/objects.c
    src/general/parameters.c

    src/general/args2arguments.c
    src/general/configs2objects.c
    src/general/file2parameters.c
    src/general/objects2objects.c
    src/general/parameters2configs.c

    src/init/combining.c
    src/init/delay.c
    src/init/linking.c
    src/init/scanning.c
    src/init/space.c
    src/init/windowing.c

    src/message/msg_hops.c
    src/message/msg_pots.c
    src/message/msg_tracks.c
    src/message/msg_spectra.c

    src/module/mod_stft.c
    src/module/mod_ssl.c
    src/module/mod_sst.c

    src/signal/aimg.c
    src/signal/assignation.c
    src/signal/coherence.c
    src/signal/frame.c
    src/signal/freq.c
    src/signal/hop.c
    src/signal/index.c
    src/signal/kalman.c
    src/signal/map.c
    src/signal/mic.c
    src/signal/mixture.c
    src/signal/particle.c
    src/signal/point.c
    src/signal/postprob.c
    src/signal/pot.c
    src/signal/scan.c
    src/signal/tdoa.c
    src/signal/track.c
    src/signal/triangle.c
    src/signal/window.c
    src/signal/xcorr.c

    src/sink/snk_pots_file.c
    src/sink/snk_tracks_file.c

    #src/source/src_raw_8soundusb.c
    src/source/src_raw_file.c

    src/system/frame2freq.c
    src/system/freq2freq.c
    src/system/freq2xcorr.c
    src/system/hop2frame.c
    src/system/kalman2coherence.c
    src/system/kalman2kalman.c
    src/system/mixture2mixture.c
    src/system/particle2coherence.c
    src/system/particle2particle.c
    src/system/xcorr2aimg.c
    src/system/xcorr2xcorr.c

    src/utils/fft.c
    src/utils/gaussian.c   
    src/utils/matrix.c
    src/utils/pcm.c
    src/utils/random.c    

)

add_library(mars SHARED
	${SRC}
)

target_link_libraries(mars
	${PC_FFTW3_LIBRARIES}
	${PC_ALSA_LIBRARIES}
    ${PC_LIBCONFIG_LIBRARIES}
	m
)

add_executable(demo
    demo/demo.c
)
target_link_libraries(demo
    mars
)
