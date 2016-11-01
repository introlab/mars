#ifndef __MARS_MODULE_STFT
#define __MARS_MODULE_STFT

    /**
    * \file     stft.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  1.0
    * \date     2016-11-01
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
    #include "../system/hop2frame.h"
    #include "../system/frame2freq.h"
    #include "../utils/window.h"

    typedef struct stft_obj {

        unsigned int hopSize;
        unsigned int frameSize;
        unsigned int nMics;

        vector_float ** frames;
        vector_float * window;

        hop2frame_obj ** hop2frame;
        frame2freq_obj ** frame2freq;

    } stft_obj;

    stft_obj * stft_construct(const unsigned int hopSize, const unsigned int frameSize, const unsigned int nMics);

    void stft_destroy(stft_obj * obj);

    int stft_process(stft_obj * obj, const vector_float ** hops, vector_float ** freqs);

#endif