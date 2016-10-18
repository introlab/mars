#ifndef __MARS_SYST_PHASE2PHASES
#define __MARS_SYST_PHASE2PHASES

	#include "../signal/vector.h"

	#include <stdlib.h>

	//! \file phase2phases.h

	//! A structure that holds all the fields to convert spectra to phase. 
	typedef struct phase2phases_obj {

		unsigned int frameSize; 		///< Size of the frame.
		unsigned int halfFrameSize; 	///< Size of the frame divided by 2 plus 1.

	} phase2phases_obj;

	/** Constructor of the phase2phases object.	
		\param 		frameSize 	Number of samples per frame.
		\return					Pointer to the instantiated object.
	*/
	phase2phases_obj * phase2phases_construct(const unsigned int frameSize);

	/** Destructor of the phase2phases object.
		\param		obj 		Pointer to the instantiated object.
	*/
	void phase2phases_destroy(phase2phases_obj * obj);

	/** Convert frame to spectrum
		\param 		obj 		Pointer to the instantiated object.
		\param		phase1		Pointer to the first input phase.
		\param		phase2		Pointer to the second input phase.
		\param 		phase12		Pointer to the output phase.
		\return 				Return -1 if error, 0 otherwise.
	*/
	int phase2phases_process(phase2phases_obj * obj, const vector_float * phase1, const vector_float * phase2, vector_float * phase12);

#endif