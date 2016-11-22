#ifndef __MARS_UTILS_TDOA
#define __MARS_UTILS_TDOA

    /**
    * \file     tdoa.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  1.0
    * \date     2016-11-02
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

    #include "../signal/matrix.h"
    #include "../utils/indexing.h"

    #include <math.h>

    /** Generate the exact TDOA values.
        \param      points      Points in a matrix Nx3.
        \param      mics        Microphones positions in a matrix Mx3.
        \param      fS          Sample rate (samples/sec).
        \param      c           Speed of sound (m/sec).
        \return                 TDOA values in a matrix NxP, where \f$P=M(M-1)/2\f$.
    */
    matrix_float * tdoa_delay(const matrix_float * points, const matrix_float * mics, const unsigned int fS, const float c);

    /** Generate the rounded TDOA values to the closest frequency bin.
        \param      tdoas       TDOA values in a matrix NxP, where \f$P=M(M-1)/2\f$.
        \return                 Rounded TDOA values in a matrix NxP, where \f$P=M(M-1)/2\f$.
    */
    matrix_signedint * tdoa_round(const matrix_float * tdoas);    

    /** Generate the wrapped TDOA values that fit within the range [0,frameSize-1]
        \param      tdoas       Rounded TDOA values in a matrix NxP, where \f$P=M(M-1)/2\f$.
        \param      frameSize   Number of samples in a xcorr frame.
    */
    matrix_unsignedint * tdoa_wrap(const matrix_signedint * tdoas, const unsigned int frameSize);

#endif