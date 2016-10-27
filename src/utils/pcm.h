#ifndef __MARS_UTILS_PCM
#define __MARS_UTILS_PCM

    /**
    * \file     pcm.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  1.0
    * \date     2016-10-27
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

    /** Convert a sample encoded with signed 8 bits PCM to normalized float sample.
        \param      sample      Signed 8 bits PCM sample.
        \return                 Normalized float sample.
    */    
    float pcm_signed08bits2normalized(const signed char sample);

    /** Convert a sample encoded with signed 16 bits PCM to normalized float sample.
        \param      sample      Signed 16 bits PCM sample.
        \return                 Normalized float sample.
    */    
    float pcm_signed16bits2normalized(const signed short sample);

    /** Convert a sample encoded with signed 32 bits PCM to normalized float sample.
        \param      sample      Signed 32 bits PCM sample.
        \return                 Normalized float sample.
    */    
    float pcm_signed32bits2normalized(const signed int sample);

    /** Convert a normalized float sample to a sample encoded with signed 8 bits PCM.
        \param      sample      Normalized float sample.
        \return                 Signed 8 bits PCM sample.
    */  
    signed char pcm_normalized2signed08bits(const float sample);

    /** Convert a normalized float sample to a sample encoded with signed 16 bits PCM.
        \param      sample      Normalized float sample.
        \return                 Signed 16 bits PCM sample.
    */  
    signed short pcm_normalized2signed16bits(const float sample);

    /** Convert a normalized float sample to a sample encoded with signed 32 bits PCM.
        \param      sample      Normalized float sample.
        \return                 Signed 32 bits PCM sample.
    */  
    signed int pcm_normalized2signed32bits(const float sample);

#endif