#ifndef __MARS_SYST_XCORR2XCORRMAX
#define __MARS_SYST_XCORR2XCORRMAX

    /**
    * \file     xcorr2xcorrmax.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  1.0
    * \date     2016-11-02
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

    #include "../signal/vector.h"
    #include "../signal/matrix.h"
    #include "../utils/indexing.h"

    #include <stdlib.h>
    #include <math.h>

    //! A structure that holds all the fields to generate the acoustic image.
    typedef struct xcorr2xcorrmax_obj {

        unsigned int frameSize;         ///< Size of the frame.
        unsigned int nMics;             ///< Number of microphones.
        unsigned int nPairs;            ///< Number of pairs.
        unsigned int winSize;           ///< Maximum window size (must be odd).
        unsigned int halfWinSize;       ///< (Maximum window size - 1) / 2.
        signed int lowValue;            ///< Low value.
        signed int highValue;           ///< High value.

    } xcorr2xcorrmax_obj;

    /** Constructor of the xcorr2xcorrmax object.	
        \param      frameSize   Number of samples per frame.
        \param      nMics       Number of microphones.
        \param      winSize     Maximum window size (must be odd).
        \param      lowValue    Low value.
        \param      highValue   High value.
        \return                 Pointer to the instantiated object.
    */
    xcorr2xcorrmax_obj * xcorr2xcorrmax_construct(const unsigned int frameSize, const unsigned int nMics, const unsigned int winSize, const signed int lowValue, const signed int highValue);

    /** Destructor of the xcorr2aimg object.
        \param      obj         Pointer to the instantiated object.
    */
    void xcorr2xcorrmax_destroy(xcorr2xcorrmax_obj * obj);

    /** Filter with a maximum window.
        \param      obj			Pointer to the instantiated object.
        \param      xcorrs      Cross-correlation matrix.
        \param      xcorrsMax   Filtered cross-correlation matrix.
        \return                 Return -1 if error, 0 otherwise.        
	*/
    int xcorr2xcorrmax_process(const xcorr2xcorrmax_obj * obj, const vector_float * xcorrs, vector_float * xcorrsMax);

#endif