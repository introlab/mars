#ifndef __MARS_SYST_XCORR2XCORR
#define __MARS_SYST_XCORR2XCORR

    /**
    * \file     xcorr2xcorr.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  1.0
    * \date     2016-12-10
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

    #include <stdlib.h>
    #include "../signal/vector.h"
    #include "../utils/indexing.h"

    //! A structure that holds all the fields to multiply phases. 
    typedef struct xcorr2xcorr_obj {

        unsigned int frameSize;             ///< Size of the frame.
        unsigned int halfFrameSize;         ///< Size of the frame divided by 2 plus 1.
        unsigned int delta;
        signed int tdoaMin;
        signed int tdoaMax;

    } xcorr2xcorr_obj;

    xcorr2xcorr_obj * xcorr2xcorr_construct(const unsigned int frameSize, const unsigned int delta, const signed int tdoaMin, const signed int tdoaMax);

    void xcorr2xcorr_destroy(xcorr2xcorr_obj * obj);

    int xcorr2xcorr_process(const xcorr2xcorr_obj * obj, const vector_float * xcorrSrc, vector_float * xcorrDest);

#endif