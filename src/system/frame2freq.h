#ifndef __MARS_SYST_FRAME2FREQ
#define __MARS_SYST_FRAME2FREQ

    #include "../utils/fft.h"
    #include "../signal/vector.h"

    #include <stdlib.h>

    /**
    * \file     frame2freq.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  1.0
    * \date     2016-10-25
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

    //! A structure that holds all the fields to convert frames to spectra. 
    typedef struct frame2freq_obj {

        unsigned int frameSize;             ///< Size of the frame.
        unsigned int halfFrameSize;         ///< Size of the frame divided by 2 plus 1.
        vector_float * frameWindowed;       ///< Array that holds the samples of the window.

        fft_obj * fft;                      ///< Pointer to the FFT object.

    } frame2freq_obj;

    /** Constructor of the frame2freq object.	
        \param      frameSize   Number of samples per frame.
        \return                 Pointer to the instantiated object.
    */
    frame2freq_obj * frame2freq_construct(const unsigned int frameSize);

    /** Destructor of the raw2hop object.
        \param      obj         Pointer to the instantiated object.
    */
    void frame2freq_destroy(frame2freq_obj * obj);

    /** Convert frame to spectrum
        \param      obj         Pointer to the instantiated object.
        \param      frame       Pointer to the input frame.
        \param      window      Pointer to the input window.
        \param      freq        Pointer to the output spectrum.
        \return                 Return -1 if error, 0 otherwise.
    */
    int frame2freq_process(frame2freq_obj * obj, const vector_float * frame, const vector_float * window, vector_float * freq);

#endif