#ifndef __MARS_MODULE_SSLAIMG
#define __MARS_MODULE_SSLAIMG

    /**
    * \file     ssl_aimg.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  1.0
    * \date     2016-11-04
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

    #include "../signal/vector.h"
    #include "../signal/matrix.h"

    #include "../system/freq2phase.h"
    #include "../system/phase2phasex.h"
    #include "../system/phasex2xcorr.h"
    #include "../system/xcorr2aimg.h"
    #include "../system/xcorr2xcorrmax.h"
    #include "../system/xcorr2xcorrreset.h"

    #include "../general/tdoa.h"

    #include "../message/msg_spectra.h"
    #include "../message/msg_pots.h"

    #include "../utils/array.h"
    #include "../utils/minmax.h"
    #include "../utils/pair.h"

    //! A structure that holds all the fields for SSL with acoustic images
    typedef struct ssl_aimg_obj {

        unsigned int frameSize;         ///< Size of the frame.
        unsigned int halfFrameSize;     ///< Size of the frame divided by 2 plus 1.
        unsigned int nMics;             ///< Number of microphones/channels.
        unsigned int nPairs;            ///< Number of pairs of microphones.
        unsigned int nPoints;           ///< Number of points to scan.
        unsigned int fS;                ///< Sample rate (samples/sec).
        float c;                        ///< Speed of sound (m/sec).
        float epsilon;                  ///< Small value to avoid overflow.
        unsigned int winSizeMax;        ///< Size of the sliding maximum window (must be an odd number).
        unsigned int winSizeReset;      ///< Size of the reset window (must be an odd number).
        unsigned int nScans;            ///< Number of scans.
        unsigned int nBands;            ///< Number of bands.

        matrix_float * ref_mics;        ///< Matrix that contains the microphone positions (Mx3).
        matrix_float * ref_points;      ///< Matrix that contains the points to scan (Sx3).
        matrix_float * ref_bands;       ///< Matrix that contains the frequency bands (Bx(N/2+1)).
        matrix_float * ref_tdoas;       ///< Matrix that contains the TDOAs values (SxP).

        matrix_unsignedint * tdoas;     ///< Matrix that contains the TDOAs values rounded to closest integer.
        vector_signedint * lowValues;   ///< Vector that contains the minimum TDOA value for each pair.
        vector_signedint * highValues;  ///< Vector that contains the maximum TDOA value for each pair.

        array_1d * bands;               ///< Array of frequency bands.
        array_1d * freqs;               ///< Array of spectra.

        array_2d * freq2phase;          ///< Array of objects to convert from spectra to phase
        array_2d * phases;              ///< Array of phases.
        array_2d * phase2phasex;        ///< Array of objects to convert from phases to paired phases.
        array_2d * phasexs;             ///< Array of paired phases.
        array_2d * phasex2xcorr;        ///< Array of objects to convert from paired phases to cross-correlations.

        array_3d * xcorrs;              ///< Array of cross-correlations.
        array_3d * xcorr2xcorrmax;      ///< Array of objects to filter cross-correlations.
        array_3d * xcorrsMax;           ///< Array of filtered cross-correlations.
        array_3d * xcorr2xcorrreset;    ///< Array of objects to reset cross-correlations.

        array_2d * xcorr2aimg;          ///< Array of objects to convert cross-correlations to acoustic images.
        array_2d * aimgs;               ///< Array of acoustic images.

    } ssl_aimg_obj;

    /** Constructor of the vector object.   
        \param      mics            Matrix that contains the microphnoe positions (Mx3).
        \param      points          Matrix that contains the points to scan (Sx3).
        \param      bands           Matrix that contains the frequency bands (Bx(N/2+1)).
        \param      frameSize       Number of samples in a frame.
        \param      fS              Sample rate (samples/sec).
        \param      c               Speed of sound (m/sec).
        \param      nScans          Number of scans.
        \param      epsilon         Small value to avoid overflow.
        \param      winSizeMax      Size of the sliding maximum window (must be an odd number).
        \param      winSizeReset    Size of the reset window (must be an odd number).
        \return                     Pointer to the instantiated object.
    */  
    ssl_aimg_obj * ssl_aimg_construct(const matrix_float * mics, const mtrix_float * points, const matrix_float * bands, const unsigned int frameSize, const unsigned int fS, const float c, const unsigned int nScans, const float epsilon, const unsigned int winSizeMax, const unsigned int winSizeReset);

    /** Destructor of the vector object.
        \param      obj             Pointer to the instantiated object.
    */
    void ssl_aimg_destroy(ssl_aimg_obj * obj);

    /** Generate potential sound sources from the spectra
        \param      obj             Pointer to the instantiated object.
        \param      spectra         Pointer to the spectra message.
        \param      pots            Pointer to the potential sources message.
    */
    int ssl_aimg_process(ssl_aimg_obj * obj, const msg_spectra_obj * spectra, msg_pots_obj * pots);

#endif