#ifndef __MARS_SOURCE_RAW2HOP
#define __MARS_SOURCE_RAW2HOP

    /**
    * \file     raw2hop.h
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

    #include "../signal/vector.h"
    #include "../utils/pcm.h"

    #include <stdio.h>
    #include <math.h>
    #include <limits.h>
    #include <string.h>

    //! A structure that holds all the fields to extract samples from a RAW file. 
    typedef struct raw2hop_obj {

        unsigned int hopSize;       ///< Size of the hop.
        unsigned int nMics;         ///< Number of microphones/channels.
        unsigned int nBits;         ///< Number of bits per sample.
        char * fileName;            ///< Name of the RAW file.
        FILE * fp;                  ///< File pointer.

    } raw2hop_obj;

    /** Constructor of the raw2hop object.	
        \param      hopSize     Number of samples per hop.
        \param      nMics       Number of microphones/channels.
        \param      nBits       Number of bits.
        \param      fileName    Name of the RAW file.
        \return                 Pointer to the instantiated object.
    */
    raw2hop_obj * raw2hop_construct(const unsigned int hopSize, const unsigned int nMics, const unsigned int nBits, const char * fileName);

    /** Destructor of the raw2hop object.
        \param      obj         Pointer to the instantiated object.
    */
    void raw2hop_destroy(raw2hop_obj * obj);

    /** Extract the next hop from the RAW file and push samples in the hops
        \param      obj         Pointer to the instantiated object.
        \param      hops        Pointer to an array of hops vectors.
        \return                 Return -1 if end of file reached, 0 otherwise.
    */
    int raw2hop_process(raw2hop_obj * obj, vector_float ** hops);

#endif