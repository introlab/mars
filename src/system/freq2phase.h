#ifndef __MARS_SYST_FREQ2PHASE
#define __MARS_SYST_FREQ2PHASE

	#include "../signal/vector.h"

	#include <math.h>

	//! \file freq2phase.h

	//! A structure that holds all the fields to convert spectra to phase. 
	typedef struct freq2phase_obj {

		unsigned short frameSize; 		///< Size of the frame.
		unsigned short halfFrameSize; 	///< Size of the frame divided by 2 plus 1.
		float epsilon; 					///< Epsilon value (small value) to avoid overflow.

	} freq2phase_obj;

	/** Constructor of the freq2phase object.	
		\param 		frameSize 	Number of samples per frame.
		\param      epsilon 	Epsilon value (small value) to avoid overflow.
		\return					Pointer to the instantiated object.
	*/
	freq2phase_obj * freq2phase_construct(const unsigned int frameSize, const float epsilon);

	/** Destructor of the freq2phase object.
		\param		obj 		Pointer to the instantiated object.
	*/
	void freq2phase_destroy(freq2phase_obj * obj);

	/** Convert frame to spectrum
		\param 		obj 		Pointer to the instantiated object.
		\param		freq		Pointer to the input spectrum.
		\param 		mask 		Pointer to the input mask.
		\param 		phase 		Pointer to the output phase.
		\return 				Return -1 if error, 0 otherwise.
	*/
	int freq2phase_process(freq2phase_obj * obj, const vector_float * freq, const vector_float * mask, vector_float * phase);

#endif