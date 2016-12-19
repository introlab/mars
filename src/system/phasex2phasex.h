#ifndef __MARS_SYST_PHASEX2PHASEX
#define __MARS_SYST_PHASEX2PHASEX

    #include "../signal/vector.h"
    #include "../utils/fifo.h"

    #include <stdlib.h>

    /**
    * \file     phasex2phasex.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  1.0
    * \date     2016-12-19
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
    typedef struct phasex2phasex_obj {

        unsigned int frameSize;         ///< Size of the frame.
        unsigned int halfFrameSize;     ///< Size of the frame divided by 2 plus 1.
        unsigned int bufferSize;        ///< Size of the buffer.

        fifo_obj * fifo;                ///< FIFO buffer.
        vector_float * runningSum;      ///< Running sum.

    } phasex2phasex_obj;

    /** Constructor of the object.	
        \param      frameSize       Number of samples per frame.
        \return                     Pointer to the instantiated object.
    */
    phasex2phasex_obj * phasex2phasex_construct(const unsigned int frameSize, const unsigned int bufferSize);

    /** Destructor of the object.
        \param      obj             Pointer to the instantiated object.
    */
    void phasex2phasex_destroy(phasex2phasex_obj * obj);

    /** Convert frame to spectrum
        \param      obj             Pointer to the instantiated object.
        \param      phase12         Pointer to the input phase.
        \param      phase12smooth   Pointer to the output phase.
        \return                     Return -1 if error, 0 otherwise.
    */
    int phasex2phasex_process(phasex2phasex_obj * obj, const vector_float * phase12, vector_float * phase12smooth);


#endif
