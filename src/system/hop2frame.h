#ifndef __MARS_SYST_HOP2FRAME
#define __MARS_SYST_HOP2FRAME

    #include "../signal/matrix.h"

    #include <stdlib.h>

    /**
    * \file     hop2frame.h
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

    //! A structure that holds all the fields to convert hops to frames. 
    typedef struct hop2frame_obj {

        unsigned int hopSize;           ///< Size of the hop.
        unsigned int frameSize;         ///< Size of the frame.
        unsigned int nMics;             ///< Number of microphones.
        matrix_float * frames;          ///< Matrix that holds the samples.

    } hop2frame_obj;

    /** Constructor of the hop2frame object.	
        \param      hopSize     Number of samples per hop.
        \param      frameSize   Number of samples per frame.
        \param      nMics       Number of microphones.
        \return                 Pointer to the instantiated object.
    */
    hop2frame_obj * hop2frame_construct(const unsigned int hopSize, const unsigned int frameSize, const unsigned int nMics);

    /** Destructor of the raw2hop object.
        \param      obj             Pointer to the instantiated object.
    */
    void hop2frame_destroy(hop2frame_obj * obj);

    /** Consume the new hop and generate the next frame
        \param      obj         Pointer to the instantiated object.
        \param      hops        Pointer to the input hop.
        \param      frames      Pointer to the output frame.
        \return                 Return -1 if error, 0 otherwise.
    */
    int hop2frame_process(hop2frame_obj * obj, const matrix_float * hops, matrix_float * frames);

#endif