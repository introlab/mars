#ifndef __MARS_SINK_HOP2RAW
#define __MARS_SINK_HOP2RAW

    /**
    * \file     hop2raw.h
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

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <math.h>
    #include <limits.h>

    #include "../signal/vector.h"
    #include "../utils/pcm.h"

    //! A structure that holds all the fields to extract samples from a RAW file. 
    typedef struct hop2raw_obj {

        unsigned int hopSize;       ///< Size of the hop.
        unsigned int nMics;         ///< Number of microphones/channels.
        unsigned char nBits;        ///< Number of bits per sample.
        size_t sizeSample;          ///< Size of a sample.
        float maxValue;             ///< Maximum value with the number of bytes.
        float minValue;             ///< Minimum value with the number of bytes.
        char * fileName;            ///< Name of the RAW file.
        FILE * fp;                  ///< File pointer.

    } hop2raw_obj;    

    /** Constructor of the hop2raw object.	
        \param      hopSize     Number of samples per hop.
        \param      nMics       Number of microphones/channels.
        \param      nBits       Number of bits.
        \param      fileName    Name of the RAW file.
        \return                 Pointer to the instantiated object.
    */
    hop2raw_obj * hop2raw_construct(const unsigned int hopSize, const unsigned int nMics, const unsigned char nBits, const char * fileName);

    /** Destructor of the hop2raw object.
        \param      obj         Pointer to the instantiated object.
    */
    void hop2raw_destroy(hop2raw_obj * obj);

    /** Extract the next hop from the RAW file and push samples in the hops
        \param      obj         Pointer to the instantiated object.
        \param      hops        Pointer to an array of hops vectors.
        \return                 Return -1 if end of file reached, 0 otherwise.
    */
    int hop2raw_process(hop2raw_obj * obj, vector_float ** hops);

#endif