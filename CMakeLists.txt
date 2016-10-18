cmake_minimum_required(VERSION 2.4.6)

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PC_FFTW3 REQUIRED fftw3f)

include_directories(${PC_FFTW3_INCLUDE_DIRS} "${PROJECT_SOURCE_DIR}/include")
link_directories(${PC_FFTW3_LIBRARY_DIRS})

set(CMAKE_BUILD_TYPE "Release")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib")

set(SRC

	src/signal/matrix.c
	src/signal/vector.c
	
	src/source/raw2hop.c

	src/system/frame2freq.c
	src/system/freq2phase.c
	src/system/hop2frame.c
	
	src/utils/fft.c
	src/utils/window.c

)

add_library(mars SHARED
	${SRC}
)

target_link_libraries(mars
	${PC_FFTW3_LIBRARIES}
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
