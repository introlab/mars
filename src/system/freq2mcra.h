#ifndef __MARS_SYST_FREQ2MCRA
#define __MARS_SYST_FREQ2MCRA

	#include "../signal/vector.h"
	#include "../utils/window.h"
	#include "../utils/indexing.h"

	#include <stdlib.h>

	/**
	* \file 	freq2mcra.h
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

	//! A structure that holds all the fields to estimate stationnary noise via MCRA
	typedef struct freq2mcra_obj {

		unsigned int frameSize; 			///< Size of the frame.
		unsigned int halfFrameSize; 		///< Size of the frame divided by 2 plus 1.
		unsigned int w; 					///< Parameter w.
		unsigned int L; 					///< Parameter L.
		float alphaS; 						///< Parameter \f$\alpha_S\f$.
		float alphaD; 						///< Parameter \f$\alpha_D\f$.
		float delta; 						///< Parameter \f$\delta\f$.

		vector_float * b; 					///< Vector b to perform frequency filtering.
		vector_float * X2; 					///< Power of the spectrum \f$|X|^2\f$.
		vector_float * Sf; 					///< Smoothed spectrum in frequency \f$S_{f}\f$.
		vector_float * S; 					///< Smoothed spectrum in time \f$S\f$.
		vector_float * Smin; 				///< Minimum spectrum \f$S_{min}\f$.
		vector_float * Stmp; 				///< Minimum temporary spectrum \f$S_{tmp}\f$.
		vector_float * lambdaD; 			///< Noise estimation \f$\lambda_D\f$.

		unsigned short l;					///< Frame index.

	} freq2mcra_obj;

	/** Constructor of the freq2mcra object.	
		\param 		frameSize 	Number of samples per frame.
		\param 		w 	 		Parameter w.
		\param 		L 	 		Parameter L.
		\param 		alphaS 		Parameter \f$\alpha_S\f$.
		\param 		alphaD 		Parameter \f$\alpha_D\f$.
		\param 		delta 		Parameter \f$\delta\f$.
		\return					Pointer to the instantiated object.
	*/
	freq2mcra_obj * freq2mcra_construct(const unsigned int frameSize, const unsigned int w, const unsigned int L, const float alphaS, const float alphaD, const float delta);

	/** Destructor of the freq2mcra object.
		\param		obj 		Pointer to the instantiated object.
	*/
	void freq2mcra_destroy(freq2mcra_obj * obj);

	/** Estimate stationnary noise
		\param 		obj 		Pointer to the instantiated object.
		\param 		freq 		Pointer to the input spectrum.
		\param 		mcra 	 	Pointer to the output noise.
		\return 				Return -1 if error, 0 otherwise.
	*/
	int freq2mcra_process(freq2mcra_obj * obj, const vector_float * freq, vector_float * mcra);


#endif
