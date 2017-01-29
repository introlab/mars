#ifndef __MARS_SYSTEM_HOP2FRAME
#define __MARS_SYSTEM_HOP2FRAME

    /**
    * \file     hop2frame.h
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

    #include "../signal/hop.h"
    #include "../signal/frame.h"

    //! Convertor from hop to time-domain frame.
    typedef struct hop2frame_obj {

        unsigned int hopSize;               ///< Number of samples per hop.
        unsigned int frameSize;             ///< Number of samples per frame.

    } hop2frame_obj;

    /** Constructor. Initialize all fields to zero.
        \param      hopSize         Number of samples per hop.
        \param      frameSize       Number of samples per frame.
        \return                     Pointer to the instantiated object.
    */ 
    hop2frame_obj * hop2frame_construct_zero(const unsigned int hopSize, const unsigned int frameSize);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void hop2frame_destroy(hop2frame_obj * obj);

    /** Process new hop to generate the new frame. The frame object must be the same as the one used in the previous hop2frame conversion.
        \param      hop             Hop with new samples.
        \param      frame           Frame to be updated.
        \param      obj             Object to be used.
    */
    void hop2frame_process_single(hop2frame_obj * obj, const hop_obj * hop, frame_obj * frame);

    /** Process new hops to generate the new frames. The frames object must be the same as the one used in the previous hop2frame conversion.
        \param      hops            Hops with new samples.
        \param      frames          Frames to be updated.
        \param      obj             Object to be used.
    */
    void hop2frame_process_many(hop2frame_obj * obj, const hops_obj * hops, frames_obj * frames);

#endif