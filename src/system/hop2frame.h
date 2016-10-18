#ifndef __MARS_SYST_HOP2FRAME
#define __MARS_SYST_HOP2FRAME

	#include "../signal/vector.h"

	#include <stdlib.h>

	//! \file hop2frame.h

	//! A structure that holds all the fields to convert hops to frames. 
	typedef struct hop2frame_obj {

		unsigned short hopSize;			///< Size of the hop.
		unsigned short frameSize;		///< Size of the frame.
		vector_float * frame;			///< Vector that holds the samples.

	} hop2frame_obj;

	/** Constructor of the hop2frame object.	
		\param 		hopSize	 	Number of samples per hop.
		\param 		frameSize 	Number of samples per frame.
		\return					Pointer to the instantiated object.
	*/
	hop2frame_obj * hop2frame_construct(const unsigned short hopSize, const unsigned short frameSize);

	/** Destructor of the raw2hop object.
		\param		obj 		Pointer to the instantiated object.
	*/
	void hop2frame_destroy(hop2frame_obj * obj);

	/** Consume the new hop and generate the next frame
		\param 		obj 		Pointer to the instantiated object.
		\param		hop			Pointer to the input hop.
		\param		frame		Pointer to the output frame.
		\return 				Return -1 if error, 0 otherwise.
	*/
	int hop2frame_process(hop2frame_obj * obj, const vector_float * hop, vector_float * frame);

#endif