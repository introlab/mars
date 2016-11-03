#ifndef __MARS_MODULE_SSLAIMG
#define __MARS_MODULE_SSLAIMG

    /**
    * \file     ssl_aimg.h
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
    #include "../signal/matrix.h"

    #include "../system/freq2phase.h"
    #include "../system/phase2phases.h"
    #include "../system/phases2xcorr.h"
    #include "../system/xcorr2aimg.h"

    #include "../general/tdoa.h"

    typedef struct ssl_aimg_obj {

        unsigned int frameSize;
        unsigned int halfFrameSize;
        unsigned int nMics;
        unsigned int nPoints;
        unsigned int nPairs;
        unsigned int fS;
        float c;
        float epsilon;
        unsigned int nScans;
        unsigned int nBands;

        matrix_float * mics;
        matrix_float * points;
        matrix_float * bands;

        matrix_unsignedint * tdoas;
        matrix_float ** bandsMics;

        matrix_float * phases;
        matrix_float * phasesx;
        matrix_float *** xcorrs;
        vector_float *** aimg;

        matrix_unsignedint * maxIndexes;
        matrix_float * maxValues;

        freq2phase_obj * freq2phase;
        phase2phases_obj * phase2phases;
        phases2xcorr_obj * phases2xcorr;
        xcorr2aimg_obj * xcorr2aimg;

    } ssl_aimg_obj;

    ssl_aimg_obj * ssl_aimg_construct(const unsigned int frameSize, const matrix_float * mics, const matrix_float * points, const unsigned int fS, const float c, const unsigned int nScans, const matrix_float * bands, const float epsilon);

    void ssl_aimg_destroy(ssl_aimg_obj * obj);

    int ssl_aimg_process(ssl_aimg_obj * obj, const matrix_float * freqs, matrix_float ** positions);

#endif