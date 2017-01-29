#ifndef __MARS_INIT_SCANNING
#define __MARS_INIT_SCANNING

    /**
    * \file     scanning.h
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

    #include "../signal/scan.h"
    #include "../signal/mic.h"
    #include "../signal/map.h"
    #include "../init/space.h"
    #include "../init/delay.h"
    #include "../init/linking.h"

    /** Generate a list of scans for a sphere
        \param      mics                List of microphones.
        \param      nLevels             Number of levels.
        \param      levels              List of levels.
        \param      fS                  Sample rate (samples/sec).
        \param      c                   Speed of sound (meters/sec).
        \param      sigma               Parameter \f$\sigma_\mathcal{V}\f$.
        \param      nMatches            Number of matches.
        \param      frameSize           Number of samples per frame.
        \return                         List of scans.
    */
    scans_obj * scanning_init_sphere(const mics_obj * mics, const unsigned int nLevels, const unsigned int * levels, const unsigned int fS, const float c, const float sigma, const unsigned int nMatches, const unsigned int frameSize);

    /** Generate a list of scans for a halfsphere
        \param      mics                List of microphones.
        \param      nLevels             Number of levels.
        \param      levels              List of levels.
        \param      fS                  Sample rate (samples/sec).
        \param      c                   Speed of sound (meters/sec).
        \param      sigma               Parameter \f$\sigma_\mathcal{V}\f$.
        \param      nMatches            Number of matches.
        \param      frameSize           Number of samples per frame.
        \return                         List of scans.
    */
    scans_obj * scanning_init_halfsphere(const mics_obj * mics, const unsigned int nLevels, const unsigned int * levels, const unsigned int fS, const float c, const float sigma, const unsigned int nMatches, const unsigned int frameSize);

    /** Generate a list of indexes based on the multiple scans for all levels
        \param      scans               List of scans.
        \param      nMatches            Number of matches.
        \param      sigma               Parameter \f$\sigma_\mathcal{V}\f$.
    */
    void scanning_init_link(scans_obj * scans, const unsigned int nMatches, const float sigma);

#endif