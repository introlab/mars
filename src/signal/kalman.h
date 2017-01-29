#ifndef __MARS_SIGNAL_KALMAN
#define __MARS_SIGNAL_KALMAN

    /**
    * \file     kalman.h
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

    #include "../utils/matrix.h"

    //! Kalman filter
    typedef struct kalman_obj {

        matrix_obj * x_lm1lm1;          ///< Mean vector (updated) \f$\mathbf{x}_{l-1|l-1}\f$
        matrix_obj * x_llm1;            ///< Mean vector (predited) \f$\mathbf{x}_{l|l-1}\f$
        matrix_obj * P_lm1lm1;          ///< Covariance matrix (updated) \f$\mathbf{P}_{l-1|l-1}\f$
        matrix_obj * P_llm1;            ///< Covariance matrix (predicted) \f$\mathbf{P}_{l|l-1}\f$

    } kalman_obj;

    //! Kalman filters
    typedef struct kalmans_obj {

        unsigned int nSignals;          ///< Number of Kalman filters.
        kalman_obj ** array;            ///< List of Kalman filters.

    } kalmans_obj;

    /** Constructor. Initialize all elements to 0.
        \return                     Pointer to the instantiated object.
    */
    kalman_obj * kalman_construct_zero(void);

    /** Set fields to the field values of the model object. No memory allocated.
        \param      src         Object to be copied.
        \param      obj         Object to be modified.
    */ 
    void kalman_copy_kalman(kalman_obj * obj, const kalman_obj * src);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void kalman_destroy(kalman_obj * obj);

    /** Print the content of the object.
        \param      obj             Object to be used.
    */
    void kalman_printf(const kalman_obj * obj);

#endif