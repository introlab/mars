#ifndef __MARS_MESSAGE_HOPS
#define __MARS_MESSAGE_HOPS

    /**
    * \file     msg_hops.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  1.0
    * \date     2016-11-04
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

    //! A structure that holds all the fields in a hops. 
    typedef struct msg_hops_obj {

        unsigned int hopSize;       ///< Size of the hop.
        unsigned int nMics;         ///< Number of microphones/channels.
        float ** samples;           ///< Samples.

    } msg_hops_obj;

    /** Constructor of the vector object.   
        \param      hopSize     Size of the hop.
        \param      nMics       Number of microphones/channels.
        \return                 Pointer to the instantiated object.
    */  
    msg_hops_obj * msg_hops_construct(const unsigned int hopSize, const unsigned int nMics);

    /** Destructor of the vector object.
        \param      obj         Pointer to the instantiated object.
    */
    void msg_hops_destroy(msg_hops_obj * obj);

#endif