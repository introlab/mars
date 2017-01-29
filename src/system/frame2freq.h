#ifndef __MARS_SYSTEM_FRAME2FREQ
#define __MARS_SYSTEM_FRAME2FREQ

    /**
    * \file     frame2freq.h
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

    #include "../init/windowing.h"
    #include "../signal/frame.h"
    #include "../signal/freq.h"
    #include "../signal/window.h"
    #include "../utils/fft.h"

    //! Convertor from time-domain frame to frequency-domain frame
    typedef struct frame2freq_obj {

        unsigned int frameSize;                 ///< Number of samples per frame (time-domain).
        unsigned int halfFrameSize;             ///< Number of bins per frame (frequency-domain).

        window_obj * win;                       ///< Analysis window.
        frame_obj * frame;                      ///< Windowed frame.

        fft_obj * fft;                          ///< FFT tool.

    } frame2freq_obj;

    /** Constructor. Initialize all fields to zero.
        \param      frameSize       Number of samples per frame.
        \param      halfFrameSize   Number of bins per frame.
        \return                     Pointer to the instantiated object.
    */  
    frame2freq_obj * frame2freq_construct_zero(const unsigned int frameSize, const unsigned int halfFrameSize);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void frame2freq_destroy(frame2freq_obj * obj);

    /** Convert frame in the time-domain to frequency-domain.
        \param      frame           Frame in time-domain.
        \param      freq            Frame in the frequency-domain.
        \param      obj             Object to be used.
    */
    void frame2freq_process_single(frame2freq_obj * obj, const frame_obj * frame, freq_obj * freq);

    /** Convert frames in the time-domain to frequency-domain.
        \param      frames          Frames in time-domain.
        \param      freqs           Frames in the frequency-domain.
        \param      obj             Object to be used.
    */
    void frame2freq_process_many(frame2freq_obj * obj, const frames_obj * frames, freqs_obj * freqs);

#endif