#ifndef __MARS_UTILS_CIRCLE
#define __MARS_UTILS_CIRCLE

    #include "../signal/matrix.h"

    #include <stdlib.h>
    #include <math.h>

    /**
    * \file     circle.h
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

    /** Generate points in a circle in the x-y plane.
        \param      nPoints         Number of points on the circle.
        \param      radius          Radius (in meter) of the circle.
        \return                     Matrix of Nx3, where N is the number of points.
    */
    matrix_float * circle_generate(const unsigned int nPoints, const float radius);

#endif