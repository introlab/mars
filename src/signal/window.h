#ifndef __MARS_SIGNAL_WINDOW
#define __MARS_SIGNAL_WINDOW

    /**
    * \file     window.h
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

    //! Window
    typedef struct window_obj {

        unsigned int frameSize;         ///< Number of samples in the window.
        float * array;                  ///< Array of samples in the window.
        
    } window_obj;

    /** Constructor. Initialize all samples to zero.
        \param      frameSize       Number of samples in the window.
        \return                     Pointer to the instantiated object.
    */  
    window_obj * window_construct_zero(const unsigned int frameSize);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void window_destroy(window_obj * obj);

#endif