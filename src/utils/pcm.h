#ifndef __MARS_UTILS_PCM
#define __MARS_UTILS_PCM

    /**
    * \file     pcm.h
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
    #include <limits.h>

    /** Convert a 8-bit signed sample to float.
        \param      sample				8-bit signed sample.
        \return							Floating point sample.
    */
    float pcm_signed08bits2normalized(const signed char sample);

    /** Convert a 16-bit signed sample to float.
        \param      sample				16-bit signed sample.
        \return							Floating point sample.
    */
    float pcm_signed16bits2normalized(const signed short sample);

    /** Convert a 32-bit signed sample to float.
        \param      sample				32-bit signed sample.
        \return							Floating point sample.
    */
    float pcm_signed32bits2normalized(const signed int sample);

    /** Convert a float to a 8-bit signed sample.
        \param      sample				Floating point sample.
        \return							8-bit signed sample.
    */
    signed char pcm_normalized2signed08bits(const float sample);

    /** Convert a float to a 16-bit signed sample.
        \param      sample				Floating point sample.
        \return							16-bit signed sample.
    */
    signed short pcm_normalized2signed16bits(const float sample);

    /** Convert a float to a 32-bit signed sample.
        \param      sample				Floating point sample.
        \return							32-bit signed sample.
    */
    signed int pcm_normalized2signed32bits(const float sample);

#endif