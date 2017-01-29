#ifndef __MARS_SIGNAL_FREQ
#define __MARS_SIGNAL_FREQ

    /**
    * \file     freq.h
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

    //! Frame in the frequency-domain
    typedef struct freq_obj {

        unsigned int halfFrameSize;     ///< Number of bins in the frame in the frequency domain.
        float * array;                  ///< Array of complex elements in the frame.

    } freq_obj;

    //! Frames in the frequency-domain
    typedef struct freqs_obj {

        unsigned int nSignals;          ///< Number of frames.
        freq_obj ** array;              ///< List of frames.

    } freqs_obj;

    /** Constructor. Initialize all elements to 0.
        \param      halfFrameSize   Number of bins.
        \return                     Pointer to the instantiated object.
    */  
    freq_obj * freq_construct_zero(const unsigned int halfFrameSize);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void freq_destroy(freq_obj * obj);   

    /** Print the content of the object.
        \param      obj             Object to be used.
    */
    void freq_printf(freq_obj * obj);

    /** Constructor. Fill the array of objects with null pointers.
        \param      nSignals        Number of frames.    
        \return                     Pointer to the instantiated object.
    */ 
    freqs_obj * freqs_construct_null(const unsigned int nSignals);

    /** Constructor. Fill the array of objects instantiated to zero.
        \param      nSignals        Number of frames.
        \param      halfFrameSize   Number of bins per frame.
        \return                     Pointer to the instantiated object.
    */  
    freqs_obj * freqs_construct_zero(const unsigned int nSignals, const unsigned int halfFrameSize);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void freqs_destroy(freqs_obj * obj);

    /** Print the content of the object.
        \param      obj             Object to be used.
    */
    void freqs_printf(freqs_obj * obj);

#endif