#ifndef __MARS_SYST_XCORR2AIMG
#define __MARS_SYST_XCORR2AIMG

    /**
    * \file     xcorr2aimg.h
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

    //! A structure that holds all the fields to generate the acoustic image.
    typedef struct xcorr2aimg_obj {

        unsigned int frameSize;         ///< Size of the frame.
        unsigned int nMics;             ///< Number of microphones.
        unsigned int nPairs;            ///< Number of pairs.
        unsigned int nPoints;           ///< Number of points.

    } xcorr2aimg_obj;

    /** Constructor of the xcorr2aimg object.	
        \param      frameSize   Number of samples per frame.
        \param      nMics       Number of microphones.
        \param      nPoints     Number of points.
        \return                 Pointer to the instantiated object.
    */
    xcorr2aimg_obj * xcorr2aimg_construct(const unsigned int frameSize, const unsigned int nMics, const unsigned int nPoints);

    /** Destructor of the xcorr2aimg object.
        \param      obj         Pointer to the instantiated object.
    */
    void xcorr2aimg_destroy(xcorr2aimg_obj * obj);

    /** Generate the acoustic image. 
        \param      obj			Pointer to the instantiated object.
        \param      tdoas       Matrix with the TDOAs.
        \param      xcorrs      Cross-correlation matrix.
        \param      aimg        Vector with the acoustic image.
        \return                 Return -1 if error, 0 otherwise.        
	*/
    int xcorr2aimg_process(const xcorr2aimg_obj * obj, const matrix_unsignedint * tdoas, const matrix_float * xcorrs, vector_float * aimg);

#endif