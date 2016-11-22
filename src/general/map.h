#ifndef __MARS_UTILS_MAP
#define __MARS_UTILS_MAP

    /**
    * \file     map.h
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

    #include "../signal/vector.h"
    #include "../signal/matrix.h"

    #include "../utils/distribution.h"

    /** Generate a forward map that connects fine TDOAs to coarse TDOAs.
        \param      tdoasCoarse TDOA values in a matrix CxP, where \f$P=M(M-1)/2\f$, and M is the number of microphones.
        \param      tdoasFine   TDOA values in a matrix FxP, where \f$P=M(M-1)/2\f$, and M is the number of microphones.
        \param      sigma       Standard deviation of the normal distribution used to compute similarities.
        \param      nMatches    Number of coarse TDOAs associated to a fine TDOA, represented by the variable A.
        \return                 Map in a matrix FxA, where A is the number of matches, and each element holds an index in the range [1,F].
    */
    matrix_unsignedint * map_generate_forward(const matrix_float * tdoasCoarse, const matrix_float * tdoasFine, const float sigma, const unsigned int nMatches);

    /** Generate a reverse map that connects coarse TDOAs to fine TDOAs.
        \param      tdoasCoarse TDOA values in a matrix CxP, where \f$P=M(M-1)/2\f$, and M is the number of microphones.
        \param      tdoasFine   TDOA values in a matrix FxP, where \f$P=M(M-1)/2\f$, and M is the number of microphones.
        \param      sigma       Standard deviation of the normal distribution used to compute similarities.
        \param      nMatches    Number of coarse TDOAs associated to a fine TDOA, represented by the variable A.
        \return                 Map in a matrix CxB, where B is the maximum number of links, and each element holds an index in the range [0,C]. A value of 0 means there is no more index to link.
    */

    matrix_unsignedint * map_generate_reverse(const matrix_float * tdoasCoarse, const matrix_float * tdoasFine, const float sigma, const unsigned int nMatches);

    /** Generate an initial reverse map. Used to generate the first level for iterative search.
        \param      tdoasFine   TDOA values in a matrix FxP, where \f$P=M(M-1)/2\f$, and M is the number of microphones.
        \return                 Map in a matrix 1xF, with values equal to 1, 2, ..., F.
    */
    matrix_unsignedint * map_generate_reverse_init(const matrix_float * tdoasFine);

#endif