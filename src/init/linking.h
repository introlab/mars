#ifndef __MARS_INIT_LINKING
#define __MARS_INIT_LINKING

    /**
    * \file     linking.h
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

    #include "../signal/index.h"
    #include "../signal/map.h"
    #include "../signal/tdoa.h"

    /** Generate maps with TDOAs from coarse and fine levels.
        \param      tdoasCoarse         List of TDOA values on the coarse level.
        \param      tdoasFine           List of TDOA values on the fine level.
        \param      sigma               Parameter \f$\sigma_{\mathcal{V}}\f$.
        \param      nMatches            Number of matches between each point on the fine level and coarse points.
        \return                         Map sthat connects the coarse and fine levels.
    */
    maps_obj * linking_maps(const tdoas_obj * tdoasCoarse, const tdoas_obj * tdoasFine, const float sigma, const unsigned int nMatches);

    /** Compute the scores between all TDOAs on the coarse level, and one TDOA on the fine level
        \param      tdoasCoarse         List of TDOA values on the coarse level.
        \param      tdoaFine            TDOA value on the fine level.
        \param      sigma               Parameter \f$\sigma_{\mathcal{V}}\f$.
        \return                         Array of scores.
    */
    float * linking_scores(const tdoas_obj * tdoasCoarse, const tdoa_obj * tdoaFine, const float sigma);

    /** Compute the score between a TDOA on the coarse level and on the fine level.
        \param      tdoaCoarse          TDOA value on the coarse level.
        \param      tdoaFine            TDOA value on the fine level.
        \param      sigma               Parameter \f$\sigma_{\mathcal{V}}\f$.
        \return                         Score.
    */
    float linking_score(const tdoa_obj * tdoaCoarse, const tdoa_obj * tdoaFine, const float sigma);

    /** Convert maps to a list of indexes.
        \param      maps                Maps to convert
        \return                         Instantiated list of indexes.
    */
    indexes_obj * linking_indexes(const maps_obj * maps);

#endif