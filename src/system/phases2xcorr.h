#ifndef __MARS_SYST_PHASES2XCORR
#define __MARS_SYST_PHASES2XCORR

	#include "../utils/fft.h"
	#include "../signal/vector.h"

	//! \file phases2xcorr.h

	//! A structure that holds all the fields to multiply phases. 
	typedef struct phases2xcorr_obj {

		unsigned short frameSize; 			///< Size of the frame.
		unsigned short halfFrameSize; 		///< Size of the frame divided by 2 plus 1.

		fft_obj * fft; 						///< Pointer to the FFT object.

	} phases2xcorr_obj;


	/** Constructor of the phases2xcorr object.	
		\param 		frameSize 	Number of samples per frame.
		\return					Pointer to the instantiated object.
	*/
	phases2xcorr_obj * phases2xcorr_construct(const unsigned int frameSize);

	/** Destructor of the phases2xcorr object.
		\param		obj 		Pointer to the instantiated object.
	*/
	void phases2xcorr_destroy(phases2xcorr_obj * obj);

	/** Convert frame to spectrum
		\param 		obj 		Pointer to the instantiated object.
		\param		phase12		Pointer to the input phase.
		\param 		xcorr 		Pointer to the output cross-correlation.
		\return 				Return -1 if error, 0 otherwise.
	*/
	int phases2xcorr_process(phases2xcorr_obj * obj, const vector_float * phase12, vector_float * xcorr);

#endif