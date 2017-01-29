#ifndef __MARS_UTILS_EXP
#define __MARS_UTILS_EXP

    /**
    * \file     exp.h
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
    #include <math.h>

    //! Exponential function estimator
    typedef struct exp_obj {

        float minX;             ///< Minimum value in the domain.
        float maxX;             ///< Maximum value in the domain.
        unsigned int N;         ///< Number of intervals to split the domain.
        float delta;            ///< Size of each interval.
        float * values;         ///< Array of values.

    } exp_obj;

    /** Constructor. Generate the exponential function from min to max values.
        \param      minX        Minimum X value.
        \param      maxX        Maximum X value;
        \param      N           Number of intervals.            
        \return                 Pointer to the instantiated object.
    */ 
    exp_obj * exp_construct(const float minX, const float maxX, const unsigned int N);

    /** Destructor. Free memory.
        \param      obj         Object to be destroyed.
    */
    void exp_destroy(exp_obj * obj);

    /** Estimate the value of \f$\exp(x)\f$
        \param      obj         Object to be used.
        \param      x           Value of x.
        \return                 Estimated value.
    */
    float exp_estimate(const exp_obj * obj, const float x);

#endif