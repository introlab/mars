#ifndef __MARS_SIGNAL_XCORR
#define __MARS_SIGNAL_XCORR

    /**
    * \file     xcorr.h
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
    #include <stdio.h>

    //! Cross-correlation
    typedef struct xcorr_obj {

        unsigned int frameSize;             ///< Number of samples per frame.
        float * array;                      ///< Array of samples in the frame.

    } xcorr_obj;

    //! Cross-correlations
    typedef struct xcorrs_obj {

        unsigned int nSignals;              ///< Number of frames.
        xcorr_obj ** array;                 ///< List of frames.

    } xcorrs_obj;

    /** Constructor. Initialize all samples to zero.
        \param      frameSize       Number of samples in the frame.
        \return                     Pointer to the instantiated object.
    */  
    xcorr_obj * xcorr_construct_zero(const unsigned int frameSize);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void xcorr_destroy(xcorr_obj * obj);

    /** Print the content of this object in the console.
        \param      obj             Object, which content is to be printed.
    */
    void xcorr_printf(const xcorr_obj * obj);

    /** Constructor. Fill the array of objects with null pointers.
        \param      nSignals    Number of frames.    
        \return                 Pointer to the instantiated object.
    */  
    xcorrs_obj * xcorrs_construct_null(const unsigned int nSignals);

    /** Constructor. Initialize the list of objects with instantiated frames.
        \param      nSignals        Number of frames.
        \param      frameSize       Number of samples per frame.
        \return                     Pointer to the instantiaed object.
    */
    xcorrs_obj * xcorrs_construct_zero(const unsigned int nSignals, const unsigned int frameSize);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void xcorrs_destroy(xcorrs_obj * obj);

    /** Print the content of this object in the console.
        \param      obj             Object, which content is to be printed.
    */
    void xcorrs_printf(const xcorrs_obj * obj);

#endif