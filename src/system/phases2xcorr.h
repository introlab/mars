#ifndef __MARS_SYST_PHASES2XCORR
#define __MARS_SYST_PHASES2XCORR

	#include "../utils/fft.h"
	#include "../signal/vector.h"

	/**
	* \file 	phases2xcorr.h
	* \author 	François Grondin <francois.grondin2@usherbrooke.ca>
	* \version  1.0
	* \date 	2016-10-25
	* \copyright
	*
	* This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
	*
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    * GNU General Public License for more details.
	* 
    * You should have received a copy of the GNU General Public License
    * along with this program.  If not, see <http://www.gnu.org/licenses/>.
	*
	*/

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