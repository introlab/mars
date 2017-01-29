#ifndef __MARS_SYSTEM_FREQ2XCORR
#define __MARS_SYSTEM_FREQ2XCORR

    /**
    * \file     freq2xcorr.h
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

    #include "../signal/frame.h"
    #include "../signal/freq.h"
    #include "../signal/tdoa.h"
    #include "../signal/xcorr.h"
    #include "../utils/fft.h"

    //! Convertor from phasors in the frequency-domain to cross-correlation in the time-domain.
    typedef struct freq2xcorr_obj {

        unsigned int frameSize;             ///< Number of samples in a frame.
        unsigned int halfFrameSize;         ///< Number of bins in a frame.

        frame_obj * frame;                  ///< Temporary frame to store unnormalized results.

        fft_obj * fft;                      ///< FFT tool.

    } freq2xcorr_obj;

    /** Constructor. Initialize all fields to zero.
        \param      frameSize       Number of samples per frame.
        \param      halfFrameSize   Number of bins per frame.
        \return                     Pointer to the instantiated object.
    */ 
    freq2xcorr_obj * freq2xcorr_construct_zero(const unsigned int frameSize, const unsigned int halfFrameSize);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void freq2xcorr_destroy(freq2xcorr_obj * obj);

    /** Convert phasors to time-domain cross-correlation
        \param      freq            Frequency-domain frame (phasor).
        \param      minTdoa         Minimum TDOA value for this pair (to perform normalization on valid range only to go faster).
        \param      maxTdoa         Maximum TDOA value for this pair (to perform normalization on valid range only to go faster).
        \param      xcorr           Cross-correlation result.
        \param      obj             Object to be used.
    */
    void freq2xcorr_process_single(freq2xcorr_obj * obj, const freq_obj * freq, const unsigned int minTdoa, const unsigned maxTdoa, xcorr_obj * xcorr);

    /** Convert phasors to time-domain cross-correlations
        \param      freqs           Frequency-domain frames (phasor).
        \param      minTdoas        Minimum TDOA values for all pairs (to perform normalization on valid range only to go faster).
        \param      maxTdoas        Maximum TDOA values for all pairs (to perform normalization on valid range only to go faster).
        \param      xcorrs          Cross-correlation results.
        \param      obj             Object to be used.
    */
    void freq2xcorr_process_many(freq2xcorr_obj * obj, const freqs_obj * freqs, const tdoa_obj * minTdoas, const tdoa_obj * maxTdoas, xcorrs_obj * xcorrs);

#endif