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

    #include "../system/freq2mcra.h"
    #include "../system/freq2phase.h"
    #include "../system/mcra2mask.h"
    #include "../system/phase2phasex.h"
    #include "../system/phasex2xcorr.h"
    #include "../system/xcorr2aimg.h"

    #include "../general/map.h"
    #include "../general/tdoa.h"

    #include "../message/msg_spectra.h"
    #include "../message/msg_pots.h"

    #include "../utils/array.h"
    #include "../utils/minmax.h"
    #include "../utils/pair.h"

    //! A structure that holds all the fields for SSL with acoustic images
    typedef struct ssl_obj {

        unsigned int frameSize;         ///< Size of the frame.
        unsigned int halfFrameSize;     ///< Size of the frame divided by 2 plus 1.
        unsigned int nMics;             ///< Number of microphones/channels.
        unsigned int nPairs;            ///< Number of pairs of microphones.
        unsigned int nLevels;           ///< Number of levels.
        unsigned int fS;                ///< Sample rate (samples/sec).
        float c;                        ///< Speed of sound (m/sec).
        float epsilon;                  ///< Small value to avoid overflow.
        unsigned int w;
        unsigned int L;
        float alphaS;
        float alphaD;
        float delta;
        float alphaP;

        matrix_float * mics;            ///< Matrix that contains the microphone positions (Mx3).

        array_1d * points;
        array_1d * tdoas;
        array_1d * invmap;

        array_1d * freqs;               ///< Array of spectra.
        array_1d * freq2mcra;
        array_1d * mcras;
        array_1d * mcra2mask;
        array_1d * masks;
        array_1d * freq2phase;          ///< Array of objects to convert from spectra to phase
        array_1d * phases;              ///< Array of phases.
        array_1d * phase2phasex;        ///< Array of objects to convert from phases to paired phases.
        array_1d * phasexs;             ///< Array of paired phases.
        array_1d * phasex2xcorr;        ///< Array of objects to convert from paired phases to cross-correlations.
        array_1d * xcorrs;              ///< Array of cross-correlations.
        array_1d * xcorr2aimg;          ///< Array of objects to convert cross-correlations to acoustic images.
        array_1d * aimgs;               ///< Array of acoustic images.

    } ssl_obj;

    /** Constructor of the vector object.   
        \param      mics            Matrix that contains the microphnoe positions (Mx3).
        \param      frameSize       Number of samples in a frame.
        \param      fS              Sample rate (samples/sec).
        \param      c               Speed of sound (m/sec).
        \param      epsilon         Small value to avoid overflow.
        \return                     Pointer to the instantiated object.
    */  
    ssl_obj * ssl_construct(const matrix_float * mics, const unsigned int frameSize, const unsigned int fS, const float c, const vector_unsignedint * levels, const float sigma, const unsigned int nMatches, const float epsilon, const unsigned int w, const unsigned int L, const float alphaS, const float alphaD, const float delta, const float alphaP);

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