#ifndef __MARS_MODULE_SSL
#define __MARS_MODULE_SSL

    /**
    * \file     ssl.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  1.0
    * \date     2016-11-21
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

    #include "../general/sphere.h"

    #include "../signal/vector.h"
    #include "../signal/matrix.h"

    #include "../system/phasor.h"
    #include "../system/crossphasor.h"
    #include "../system/bufferphasor.h"
    #include "../system/xcorr.h"
    #include "../system/aimg.h"
    #include "../system/maxxcorr.h"

    #include "../general/map.h"
    #include "../general/tdoa.h"

    #include "../message/msg_spectra.h"
    #include "../message/msg_pots.h"

    #include "../utils/array.h"
    #include "../utils/minmax.h"
    #include "../utils/pair.h"
    #include "../utils/sort.h"

    //! A structure that holds all the fields for SSL with acoustic images
    typedef struct ssl_obj {

        unsigned int frameSize;                 ///< Size of the frame.
        unsigned int halfFrameSize;             ///< Size of the frame divided by 2 plus 1.
        unsigned int nMics;                     ///< Number of microphones/channels.
        unsigned int nPairs;                    ///< Number of pairs of microphones.
        unsigned int nLevels;                   ///< Number of levels.
        unsigned int bufferSize;                ///< Buffer size for cross-correlation.
        unsigned int bufferDelta;               ///< Refresh rate for cross-correlation.
        unsigned int fS;                        ///< Sample rate (samples/sec).
        float c;                                ///< Speed of sound (m/sec).
        float epsilon;                          ///< Small value to avoid overflow.

        unsigned int bValue;                    ///< Frame count for the refresh rate.
        float vPointPrev;                       ///< Energy level since last refresh.
        unsigned int iPointPrev;                ///< Point index since last refresh.

        matrix_float * mics;                    ///< Matrix that contains the microphone positions (Mx3).

        array_1d * points;                      ///< Array of matrices (Nx3) that contains the points to scan for each level.
        array_1d * tdoas;                       ///< Array of matrices (NxP) that contains the TDOAs for each level.
        array_1d * invmap;                      ///< Array of matrices (NxB) that contains the maps for each level.

        vector_unsignedint * deltaSortValue;    ///< List of delta values for xcorr filtering, sorted in ascending order.
        vector_unsignedint * deltaSortIndex;    ///< List of indexes that correspond to sorted delta values.
        vector_unsignedint * deltaDiff;         ///< Difference in delta values between each delta value.

        array_1d * freqs;                       ///< Array of spectra.
        array_1d * phasors;                     ///< Array of objects to convert from spectra to phase
        array_1d * phases;                      ///< Array of phases.
        array_1d * crossphasors;                ///< Array of objects to convert from phases to paired phases.
        array_1d * phasexs;                     ///< Array of paired phases.
        array_1d * bufferphasors;               ///< Array of objects to buffer paired phases.
        array_1d * phasexsmooths;               
        array_1d * xcorrs;                      ///< Array of objects to convert from paired phases to cross-correlations.
        array_1d * xcorrsoriginal;              ///< Array of cross-correlations.
        array_2d * maxxcorrs;                   ///< Array of objects to compute max values in cross-correlations.
        array_2d * xcorrsfiltered;              ///< Array of cross-correlations with max values.
        array_1d * aimgs;                       ///< Array of objects to convert cross-correlations to acoustic images.
        array_1d * aimages;                     ///< Array of acoustic images.

    } ssl_obj;

    /** Constructor of the vector object.   
        \param      mics            Matrix that contains the microphnoe positions (Mx3).
        \param      frameSize       Number of samples in a frame.
        \param      fS              Sample rate (samples/sec).
        \param      c               Speed of sound (m/sec).
        \param      bufferSize      Buffer size for cross-correlation.
        \param      bufferDelta     Refresh rate for cross-correlation.
        \param      levels          List of resolution levels.
        \param      deltas          List of deltas to filter xcorr vectors.
        \param      sigma           Standard deviation.
        \param      nMatches        Number of matches to generate the map.
        \param      epsilon         Small value to avoid overflow.
        \return                     Pointer to the instantiated object.
    */  
    ssl_obj * ssl_construct(const matrix_float * mics, const unsigned int frameSize, const unsigned int fS, const float c, const unsigned int bufferSize, const unsigned int bufferDelta, const vector_unsignedint * levels, const vector_unsignedint * deltas, const float sigma, const unsigned int nMatches, const float epsilon );

    /** Destructor of the vector object.
        \param      obj             Pointer to the instantiated object.
    */
    void ssl_destroy(ssl_obj * obj);

    /** Generate potential sound sources from the spectra
        \param      obj             Pointer to the instantiated object.
        \param      spectra         Pointer to the spectra message.
        \param      pots            Pointer to the potential sources message.
    */
    int ssl_process(ssl_obj * obj, const msg_spectra_obj * spectra, msg_pots_obj * pots);

#endif