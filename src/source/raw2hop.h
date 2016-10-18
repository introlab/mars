#ifndef __MARS_SOURCE_RAW2HOP
#define __MARS_SOURCE_RAW2HOP

	#include "../signal/vector.h"
	
	#include <stdio.h>
	#include <math.h>
	#include <limits.h>

	//! \file raw2hop.h

	//! A structure that holds all the fields to extract samples from a RAW file. 
	typedef struct raw2hop_obj {

		unsigned int hopSize;		///< Size of the hop.
		unsigned int nMics; 		///< Number of microphones/channels.
		unsigned char nBits; 		///< Number of bytes.
		size_t sizeSample;			///< Size of a sample.
		float maxAmplitude;			///< Maximum amplitude with the number of bytes.

	} raw2hop_obj;

	/** Constructor of the raw2hop object.	
		\param 		hopSize	 	Number of samples per hop.
		\param		nMics		Number of microphones/channels.
		\param  	nBits 		Number of bits.
		\return					Pointer to the instantiated object.
	*/
	raw2hop_obj * raw2hop_construct(const unsigned int hopSize, const unsigned int nMics, const unsigned char nBits);

	/** Destructor of the raw2hop object.
		\param		obj 		Pointer to the instantiated object.
	*/
	void raw2hop_destroy(raw2hop_obj * obj);

	/** Extract the next hop from the RAW file and push samples in the hops
		\param 		obj 		Pointer to the instantiated object.
		\param		fp			Pointer to the RAW file.
		\return 				Return -1 if end of file reached, 0 otherwise.
	*/
	int raw2hop_process(raw2hop_obj * obj, FILE * fp, vector_float ** hops);

#endif