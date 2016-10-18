#ifndef __MARS_SYST_FRAME2FREQ
#define __MARS_SYST_FRAME2FREQ

	#include "../utils/fft.h"
	#include "../signal/vector.h"

	#include <stdlib.h>

	//! \file frame2freq.h

	//! A structure that holds all the fields to convert frames to spectra. 
	typedef struct frame2freq_obj {

		unsigned short frameSize; 			///< Size of the frame.
		unsigned short halfFrameSize; 		///< Size of the frame divided by 2 plus 1.
		vector_float * frameWindowed; 		///< Array that holds the samples of the window.

		fft_obj * fft;						///< Pointer to the FFT object.

	} frame2freq_obj;

	/** Constructor of the frame2freq object.	
		\param 		frameSize 	Number of samples per frame.
		\return					Pointer to the instantiated object.
	*/
	frame2freq_obj * frame2freq_construct(const unsigned int frameSize);

	/** Destructor of the raw2hop object.
		\param		obj 		Pointer to the instantiated object.
	*/
	void frame2freq_destroy(frame2freq_obj * obj);

	/** Convert frame to spectrum
		\param 		obj 		Pointer to the instantiated object.
		\param		frame		Pointer to the input frame.
		\param 		window 		Pointer to the input window.
		\param 		freq 		Pointer to the output spectrum.
		\return 				Return -1 if error, 0 otherwise.
	*/
	int frame2freq_process(frame2freq_obj * obj, const vector_float * frame, const vector_float * window, vector_float * freq);

#endif