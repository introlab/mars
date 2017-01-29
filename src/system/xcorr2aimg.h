#ifndef __MARS_SYSTEM_XCORR2AIMG
#define __MARS_SYSTEM_XCORR2AIMG

    /**
    * \file     xcorr2aimg.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2017-01-25
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

    #include "../signal/tdoa.h"
    #include "../signal/index.h"
    #include "../signal/xcorr.h"
    #include "../signal/aimg.h"

    //! Update the states of the particle filter
    typedef struct xcorr2aimg_obj {

        unsigned int aimgSize;      ///< Number of points scanned.

    } xcorr2aimg_obj;

    /** Constructor. Initialize all fields to zero.
        \param      aimgSize        Number of points to scan.
        \return                     Pointer to the instantiated object.
    */   
    xcorr2aimg_obj * xcorr2aimg_construct_zero(const unsigned int aimgSize);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void xcorr2aimg_destroy(xcorr2aimg_obj * obj);

    /** Perform scan and return an acoustic image.
        \param      tdoas           List of TDOAs associated to each point.
        \param      index           List of indexes that correpond to the point that needs to be scanned.
        \param      xcorrs          Cross-correlation vectors.
        \param      aimg            Acoustic image generated.
        \param      obj             Object to be used.
    */
    void xcorr2aimg_process(xcorr2aimg_obj * obj, const tdoas_obj * tdoas, const index_obj * index, const xcorrs_obj * xcorrs, aimg_obj * aimg);

#endif