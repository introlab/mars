#ifndef __MARS_SIGNAL_AIMG
#define __MARS_SIGNAL_AIMG

    /**
    * \file     aimg.h
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

    //! Acoustic image
    typedef struct aimg_obj {

        unsigned int aimgSize;		///< Size of the aimg frame.
        float * array;				///< Array with the aimg elements.

    } aimg_obj;

    /** Constructor. Initialize all elements to 0.
    	\param		aimgSize       	Size of the aimg frame.
        \return                 	Pointer to the instantiated object.
    */  
    aimg_obj * aimg_construct_zero(const unsigned int aimgSize);

    /** Destructor. Free memory.
        \param      obj		        Object to be destroyed.
    */
    void aimg_destroy(aimg_obj * obj);

#endif