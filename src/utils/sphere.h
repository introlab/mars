#ifndef __MARS_UTILS_SPHERE
#define __MARS_UTILS_SPHERE

    #include "../signal/matrix.h"

    #include <stdlib.h>
    #include <math.h>

    /**
    * \file     sphere.h
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

    /** Generate points in a sphere.
    *   \param      nLevels         Number of levels (\f$N=10\times 4^l+2\f$, N is number of points, l is number of levels)
    *   \param      radius          Radius (in meter) of the sphere.
    *   \return                     Matrix of Nx3, where N is the number of points.
    */
    matrix_float * sphere_generate(const unsigned int nLevels, const float radius);

    /** Generate triangles at level 0.
    *   \return                     Matrix of 20x9 (20 triangles, with 3 points of 3 dimensions).
    */
    matrix_float * sphere_triangles_level0(void);

    /** Generate triangles at the next level.
    *   \param      triangles       Initial triangles in a matrix of Tx9.
    *   \return                     Refined triangles in a matrix of 4Tx9.
    */
    matrix_float * sphere_triangles_refine(const matrix_float * triangles);

    /** Convert triangles to points.
    *   \param      triangles       Triangles in a matrix of Tx9.
    *   \return                     Points in a matrix of Nx3, where \f$N = T/2+2\f$.
    */
    matrix_float * sphere_triangles2points(const matrix_float * triangles);

#endif