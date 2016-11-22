#ifndef __MARS_UTILS_DISTRIBUTION
#define __MARS_UTILS_DISTRIBUTION

    /**
    * \file     distribution.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  1.0
    * \date     2016-11-16
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

    /** Generate the a normal distribution.
        \param      x               Value of x.
        \param      mu              Mean of the normal distribution.
        \param      sigma           Standard deviation of the normal distribution.
        \return                     Return the y value.
    */
    float distribution_normal(const float x, const float mu, const float sigma);

#endif