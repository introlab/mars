#ifndef __MARS_MESSAGE_POTS
#define __MARS_MESSAGE_POTS

    /**
    * \file     msg_pots.h
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

    //! A structure that holds all the fields for potential sources. 
    typedef struct msg_pots_obj {

        unsigned long long id;      ///< Time stamp
        float * samples;            ///< Samples.

    } msg_pots_obj;

    /** Constructor of the vector object.   
        \return                 Pointer to the instantiated object.
    */  
    msg_pots_obj * msg_pots_construct(void);

    /** Destructor of the vector object.
        \param      obj         Pointer to the instantiated object.
    */
    void msg_pots_destroy(msg_pots_obj * obj);

#endif