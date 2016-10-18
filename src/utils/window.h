#ifndef __MARS_UTILS_WINDOWS
#define __MARS_UTILS_WINDOWS

	#include "../signal/vector.h"

	//! \file frame2freq.h

	/** Instantiate a vector that contains a Hann window.
		\param 		frameSize 	Number of samples per frame.
		\return					Pointer to the instantiated vector.
	*/
	vector_float * window_hann(const unsigned short frameSize);

#endif