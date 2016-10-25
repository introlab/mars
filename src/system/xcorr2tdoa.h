#ifndef __MARS_SYSTEM_XCORR2TDOA
#define __MARS_SYSTEM_XCORR2TDOA

    #include "../signal/vector.h"

    #include <stdlib.h>
    #include <math.h>

    /**
    * \file     xcorr2tdoa.h
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

    //! A structure that holds all the fields to extract the maximum TDOA value
    typedef struct xcorr2tdoa_obj {

        unsigned int frameSize;         ///< Size of the frame.
        unsigned int nPairs;            ///< Number of pairs.
        float epsilon;                  ///< Epsilon value (small value) to avoid overflow.

    } xcorr2tdoa_obj;

    /** Constructor of the xcorr2tdoa object.	
        \param      frameSize   Number of samples per frame.
        \param      nPairs      Number of pairs.
        \param      epsilon     Epsilon value (small value).
        \return                 Pointer to the instantiated object.
    */
    xcorr2tdoa_obj * xcorr2tdoa_construct(const unsigned int frameSize, const unsigned int nPairs, const float epsilon);

    /** Destructor of the phases2xcorr object.
        \param      obj         Pointer to the instantiated object.
    */
    void * xcorr2tdoa_destroy(xcorr2tdoa_obj * obj);

    /** Extract maximum TDOA from each pair
        \param      obj         Pointer to the instantiated object.
        \param      xcorr       Pointer to the input cross-correlations.
        \param      minIndex    Pointer to a vector of minimum values.
        \param      maxIndex    Pointer to a vector of maximum values.
        \param      tdoaIndex   Pointer to the output tdoa indexes.
        \param      tdoaEnergy  Pointer to the output tdoa amplitudes.
        \return                 Return -1 if error, 0 otherwise.
    */
    int xcorr2tdoa_process(const xcorr2tdoa_obj * obj, const vector_float ** xcorr, const vector_signedint * minIndex, const vector_signedint * maxIndex, vector_float * tdoaIndex, vector_float * tdoaEnergy);

#endif