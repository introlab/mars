#ifndef __MARS_UTILS_MINMAX
#define __MARS_UTILS_MINMAX

    /**
    * \file     minmax.h
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

    /** Returns the index of the minimum value in the array
        \param      elements    Pointer to the array.
        \param      nElements   Number of elements in the array.
        \return                 Index of the element with the minimum value.
    */
    unsigned int minmax_min_float(const float * elements, const unsigned int nElements);

    /** Returns the index of the maximum value in the array
        \param      elements    Pointer to the array.
        \param      nElements   Number of elements in the array.
        \return                 Index of the element with the maximum value.
    */
    unsigned int minmax_max_float(const float * elements, const unsigned int nElements);

#endif