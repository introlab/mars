cmake_minimum_required(VERSION 2.4.6)

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PC_FFTW3 REQUIRED fftw3f)
pkg_check_modules(PC_ALSA REQUIRED alsa)

include_directories(${PC_FFTW3_INCLUDE_DIRS} ${PC_ALSA_INCLUDE_DIRS} "${PROJECT_SOURCE_DIR}/include")
link_directories(${PC_FFTW3_LIBRARY_DIRS} ${PC_ALSA_LIBRARY_DIRS})

set(CMAKE_BUILD_TYPE "Release")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib")

set(SRC

    src/general/circle.c
    src/general/sphere.c
    src/general/tdoa.c
    src/general/window.c

    src/message/msg_hops.c
    src/message/msg_pots.c
    src/message/msg_spectra.c

    src/module/stft.c
    src/module/ssl_aimg.c

    src/probe/snapshot.c

	src/signal/matrix.c
	src/signal/vector.c

	src/sink/snk_raw.c
	
	src/source/src_eightsnd.c
	src/source/src_raw.c

    src/system/hop2frame.c
    src/system/frame2freq.c
    src/system/freq2phase.c
    src/system/phase2phasex.c
    src/system/phasex2xcorr.c
    src/system/xcorr2aimg.c
    src/system/xcorr2xcorrmax.c
    src/system/xcorr2xcorrreset.c

    src/utils/array.c
	src/utils/fft.c
	src/utils/fifo.c
	src/utils/indexing.c
	src/utils/minmax.c
	src/utils/pair.c
	src/utils/pcm.c

)

add_library(mars SHARED
	${SRC}
)

target_link_libraries(mars
	${PC_FFTW3_LIBRARIES}
	${PC_ALSA_LIBRARIES}
	m
)

add_executable(demo_fftinfo
	demo/demo_fftinfo.c
)
target_link_libraries(demo_fftinfo
	mars
)

add_executable(demo_rawinfo
	demo/demo_rawinfo.c
)
target_link_libraries(demo_rawinfo
	mars
)

add_executable(demo_record
	demo/demo_record.c
)
target_link_libraries(demo_record
	mars
)

add_executable(demo_sslt
    demo/demo_sslt.c
)
target_link_libraries(demo_sslt
    mars
)