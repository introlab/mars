#ifndef __MARS_INIT_DELAY
#define __MARS_INIT_DELAY

    /**
    * \file     delay.h
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

    #include "../signal/point.h"
    #include "../signal/mic.h"
    #include "../signal/tdoa.h"

    /** Generate TDOAs.
        \param      points              Points to scan.
        \param      mics                List of microphones.
        \param      c                   Speed of sound (meters/sec).
        \param      fS                  Sample rate (samples/sec).
        \param      frameSize           Number of samples per frame.
        \return                         List of TDOAs.
    */    
    tdoas_obj * delay_tdoas(const points_obj * points, const mics_obj * mics, const float c, const unsigned int fS, const unsigned int frameSize);

    /** Compute the delay between microphones and a given point.
        \param      point               Point to use.
        \param      mic1                First microphone.
        \param      mic2                Second microphone.
        \return                         Delay value.
    */
    float delay_dist(const point_obj * point, const mic_obj * mic1, const mic_obj * mic2);

    /** Compute the minimum values of the TODAs.
        \param      tdoas               TDOAs values.
        \return                         Minimum TDOA values.
    */
    tdoa_obj * delay_mins(const tdoas_obj * tdoas);

    /** Compute the maximum values of the TODAs.
        \param      tdoas               TDOAs values.
        \return                         Maximum TDOA values.
    */
    tdoa_obj * delay_maxs(const tdoas_obj * tdoas);

#endif

    