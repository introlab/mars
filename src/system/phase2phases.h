#ifndef __MARS_SYST_PHASE2PHASES
#define __MARS_SYST_PHASE2PHASES

	#include "../signal/vector.h"

	#include <stdlib.h>

	/**
	* \file 	phase2phases.h
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