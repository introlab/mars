#ifndef __MARS_SOURCE_RAW
#define __MARS_SOURCE_RAW

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

    #include "../message/msg_hops.h"
    #include "../utils/pcm.h"

    #include <stdio.h>
    #include <math.h>
    #include <limits.h>
    #include <string.h>

    //! A structure that holds all the fields to extract samples from a RAW file. 
    typedef struct src_raw_obj {

        unsigned int hopSize;       ///< Size of the hop.
        unsigned int nMics;         ///< Number of microphones/channels.
        unsigned int nBits;         ///< Number of bits per sample.
        char * fileName;            ///< Name of the RAW file.
        FILE * fp;                  ///< File pointer.

    } src_raw_obj;

    /** Constructor of the object.	
        \param      hopSize     Number of samples per hop.
        \param      nMics       Number of microphones/channels.
        \param      nBits       Number of bits.
        \param      fileName    Name of the RAW file.
        \return                 Pointer to the instantiated object.
    */
    src_raw_obj * src_raw_construct(const unsigned int hopSize, const unsigned int nMics, const unsigned int nBits, const char * fileName);

    /** Destructor of the object.
        \param      obj         Pointer to the instantiated object.
    */
    void src_raw_destroy(src_raw_obj * obj);

    /** Extract the next hop from the RAW file and push samples in the hops
        \param      obj         Pointer to the instantiated object.
        \param      hops        Pointer to a matrix of hops.
        \return                 Return -1 if end of file reached, 0 otherwise.
    */
    int src_raw_process(src_raw_obj * obj, msg_hops_obj * hops);

#endif