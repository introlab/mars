#ifndef __MARS_INIT_WINDOWING
#define __MARS_INIT_WINDOWING

    /**
    * \file     windowing.h
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

    #include <math.h>

    #include "../signal/window.h"
    
    /** Generate a Hann window
        \param      frameSize           Number of samples per frame.
        \return                         Instantiated window.
    */    
    window_obj * windowing_hann(const unsigned int frameSize);

#endif

    