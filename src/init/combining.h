#ifndef __MARS_INIT_COMBINING
#define __MARS_INIT_COMBINING

    /**
    * \file     combining.h
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
    #include "../signal/assignation.h"

    /** Generate all possible combinations for the given number of potential and tracked sources.
        \param      nPots               Number of potential sources.
        \param      nTracks             Number of tracked sources.
        \return                         Pointer to the instantiated object.
    */
    assignations_obj * combining_generate(const unsigned int nPots, const unsigned int nTracks);

    /** Increment the assignation and generate the next one.
        \param      src                 Previous assignation.
        \param      nTracks             Number of tracked sources.
        \return                         Pointer to the next instantiated assignation.
    */
    assignation_obj * combining_increment(const assignation_obj * src, const unsigned int nTracks);

#endif