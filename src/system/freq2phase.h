#ifndef __MARS_SYST_FREQ2PHASE
#define __MARS_SYST_FREQ2PHASE

    #include "../signal/vector.h"

    #include <math.h>
    #include <stdlib.h>

    /**
    * \file     freq2phase.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  1.0
    * \date     2016-10-25
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
    typedef struct freq2phase_obj {

        unsigned int frameSize;         ///< Size of the frame.
        unsigned int halfFrameSize;     ///< Size of the frame divided by 2 plus 1.
        float epsilon;                  ///< Epsilon value (small value) to avoid overflow.

    } freq2phase_obj;

    /** Constructor of the freq2phase object.	
        \param      frameSize   Number of samples per frame.
        \param      epsilon     Epsilon value (small value) to avoid overflow.
        \return                 Pointer to the instantiated object.
	*/
    freq2phase_obj * freq2phase_construct(const unsigned int frameSize, const float epsilon);

    /** Destructor of the freq2phase object.
        \param      obj         Pointer to the instantiated object.
    */
    void freq2phase_destroy(freq2phase_obj * obj);

    /** Convert frame to spectrum
        \param      obj         Pointer to the instantiated object.
        \param      freq        Pointer to the input spectrum.
        \param      mask        Pointer to the input mask.
        \param      phases      Pointer to the output phase.
        \return                 Return -1 if error, 0 otherwise.
    */
    int freq2phase_process(freq2phase_obj * obj, const vector_float * freq, const vector_float * mask, vector_float * phases);

#endif