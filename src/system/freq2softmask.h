#ifndef __MARS_SYST_FREQ2SOFTMASK
#define __MARS_SYST_FREQ2SOFTMASK

    #include "../signal/vector.h"
    #include <stdlib.h>

    /**
    * \file     freq2softmask.h
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

    //! A structure that holds all the fields to estimate a soft mask
    typedef struct freq2softmask_obj {

        unsigned short frameSize;           ///< Size of the frame.
        unsigned short halfFrameSize;       ///< Size of the frame divided by 2 plus 1.
        float alphaP;                       ///< Parameter \f$\alpha_P\f$
        float epsilon;                      ///< Epsilon value (small value) to avoid overflow.

        vector_float * X2;                  ///< Power of the spectrum \f$|X|^2\f$.
        vector_float * zeta;                ///< Mask \f$\zeta\f$.
        vector_float * xi;                  ///< SNR estimation.

    } freq2softmask_obj;

    /** Constructor of the freq2softmask object.	
        \param      frameSize   Number of samples per frame.
        \param      alphaP      Parameter \f$\alpha_P\f$.
        \param      epsilon     Epsilon value (small value) to avoid overflow. 
        \return                 Pointer to the instantiated object.
    */
    freq2softmask_obj * freq2softmask_construct(const unsigned int frameSize, const float alphaP, const float epsilon);

    /** Destructor of the freq2softmask object.
        \param      obj         Pointer to the instantiated object.
    */
    void freq2softmask_destroy(freq2softmask_obj * obj);

    /** Compute soft mask
        \param      obj         Pointer to the instantiated object.
        \param      freq        Pointer to the input spectrum.
        \param      mcra        Pointer to the input noise.
        \param      mask        Pointer to the output mask.
        \return                 Return -1 if error, 0 otherwise.
    */
    int freq2softmask_process(freq2softmask_obj * obj, const vector_float * freq, const vector_float * mcra, vector_float * mask);


#endif
