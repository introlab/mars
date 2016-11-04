#ifndef __MARS_MODULE_STFT
#define __MARS_MODULE_STFT

    /**
    * \file     stft.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  1.0
    * \date     2016-11-01
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

    #include "../general/window.h"
    #include "../signal/vector.h"
    #include "../system/hop2frame.h"
    #include "../system/frame2freq.h"
    #include "../utils/array.h"

    #include "../message/msg_hops.h"
    #include "../message/msg_spectra.h"

    //! A structure that holds all the fields for STFT
    typedef struct stft_obj {

        unsigned int hopSize;           ///< Size of the hop.
        unsigned int frameSize;         ///< Size of the frame.
        unsigned int halfFrameSize;     ///< Size of the frame divided by 2 plus 1.
        unsigned int nMics;             ///< Number of microphones/channels.

        array_1d * hops;                ///< Array of hops.
        array_1d * hop2frame;           ///< Array of objects to convert hops to frames.
        array_1d * frames;              ///< Array of frames.
        array_1d * frame2freq;          ///< Array of objects to convert frames to freqs.
        array_1d * freqs;               ///< Array of spectra.

        vector_float * window;          ///< Analysis window.


    } stft_obj;

    /** Constructor of the vector object.   
        \param      hopSize     Size of a hop.
        \param      frameSize   Size of a frame.
        \param      nMics       Number of microphones/channels.
        \return                 Pointer to the instantiated object.
    */      
    stft_obj * stft_construct(const unsigned int hopSize, const unsigned int frameSize, const unsigned int nMics);

    /** Destructor of the vector object.
        \param      obj         Pointer to the instantiated object.
    */
    void stft_destroy(stft_obj * obj);

    /** Generate spectra from hops.
        \param      obj         Pointer to the instantiated object.
        \param      hops        Hops message.
        \param      spectra     Spectra message.
    */
    int stft_process(stft_obj * obj, const msg_hops_obj * hops, const msg_spectra_obj * spectra);

#endif