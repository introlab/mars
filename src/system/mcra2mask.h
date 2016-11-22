#ifndef __MARS_SYST_MCRA2MASK
#define __MARS_SYST_MCRA2MASK

    #include "../general/window.h"
    #include "../signal/vector.h"
    #include "../utils/indexing.h"

    #include <stdlib.h>

    /**
    * \file     mcra2mask.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  1.0
    * \date     2016-11-22
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

    //! A structure that holds all the fields to estimate stationnary noise via MCRA
    typedef struct mcra2mask_obj {

        unsigned int frameSize;             ///< Size of the frame.
        unsigned int halfFrameSize;         ///< Size of the frame divided by 2 plus 1.
        float alphaP;                       ///< Parameter \f$\alpha_P\f$.
        float epsilon;                      ///< Parameter epsilon.

        vector_float * X2;                  ///< Power of the spectrum \f$|X|^2\f$.
        vector_float * zeta;                ///< Zeta vector.
        vector_float * xi;                  ///< Xi vector.

    } mcra2mask_obj;

    /** Constructor of the object.  
        \param      frameSize   Number of samples per frame.
        \param      alphaP      Parameter \f$\alpha_P\f$. 
        \param      epsilon     Parameter \f$\epsilon\f$. 
        \return                 Pointer to the instantiated object.
    */
    mcra2mask_obj * mcra2mask_construct(unsigned int frameSize, const float alphaP, const float epsilon);

    /** Destructor of the object.
        \param      obj             Pointer to the instantiated object.
    */
    void mcra2mask_destroy(mcra2mask_obj * obj);

    /** Generate a soft mask from the current spectrum and the estimated noise via MCRA.
        \param      obj         Pointer to the instantiated object.
        \param      freq        Pointer to spectrum.
        \param      mcra        Pointer to the MCRA noise.
        \param      mask        Pointer to the generated mask.
        \return                 Return -1 if error, 0 otherwise.
    */
    int mcra2mask_process(mcra2mask_obj * obj, const vector_float * freq, const vector_float * mcra, vector_float * mask);

#endif