#ifndef __MARS_SYSTEM_XCORR2TDOA
#define __MARS_SYSTEM_XCORR2TDOA

	#include "../signal/vector.h"

	#include <stdlib.h>
	#include <math.h>

	//! \file xcorr2tdoa.h

	//! A structure that holds all the fields to extract the maximum TDOA value
	typedef struct xcorr2tdoa_obj {

		unsigned int frameSize; 		///< Size of the frame.
		unsigned int nPairs; 			///< Number of pairs.
		float epsilon; 					///< Epsilon value (small value) to avoid overflow.

	} xcorr2tdoa_obj;

	/** Constructor of the xcorr2tdoa object.	
		\param 		frameSize 	Number of samples per frame.
		\param 		nPairs 		Number of pairs.
		\param 		epsilon 	Epsilon value (small value).
		\return					Pointer to the instantiated object.
	*/
	xcorr2tdoa_obj * xcorr2tdoa_construct(const unsigned int frameSize, const unsigned int nPairs, const float epsilon);

	/** Destructor of the phases2xcorr object.
		\param		obj 		Pointer to the instantiated object.
	*/
	void * xcorr2tdoa_destroy(xcorr2tdoa_obj * obj);

	/** Extract maximum TDOA from each pair
		\param 		obj 		Pointer to the instantiated object.
		\param 		xcorr 		Pointer to the input cross-correlations.
		\param 		minIndex	Pointer to a vector of minimum values.
		\param		maxIndex 	Pointer to a vector of maximum values.
		\param 		tdoaIndex 	Pointer to the output tdoa indexes.
		\param 		tdoaEnergy	Pointer to the output tdoa amplitudes.
		\return 				Return -1 if error, 0 otherwise.
	*/
	int xcorr2tdoa_process(const xcorr2tdoa_obj * obj, const vector_float ** xcorr, const vector_signedint * minIndex, const vector_signedint * maxIndex, vector_float * tdoaIndex, vector_float * tdoaEnergy);

#endif