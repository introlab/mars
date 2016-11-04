#ifndef __MARS_UTILS_PAIR
#define __MARS_UTILS_PAIR

    /**
    * \file     pair.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  1.0
    * \date     2016-11-03
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

    /** Returns the number of pairs 
        \param      nMics       Number of microphones.
        \return                 Number of pairs.
    */
    unsigned int pair_nPairs(const unsigned int nMics);

    /** Return the pair index for the given microphone indexes.
        \param      nMics       Number of microphones.
        \param      iMic1       Index of microphone 1.
        \param      iMic2       Index of microphone 2.
    */
    unsigned int pair_iPair(const unsigned int nMics, const unsigned int iMic1, const unsigned int iMic2);

#endif