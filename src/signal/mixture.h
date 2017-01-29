#ifndef __MARS_SIGNAL_MIXTURE
#define __MARS_SIGNAL_MIXTURE

    /**
    * \file     mixture.h
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
    #include <stdio.h>

    #include "../signal/assignation.h"
    #include "../init/combining.h"

    //! Mixture.
    typedef struct mixture_obj {
       
        unsigned int S;                     ///< Number of potential sources.
        unsigned int T;                     ///< Number of tracked sources.
        unsigned int TND;                   ///< Number of tracked sources (including new and false detections).
        unsigned int C;                     ///< Number of combinations.

        assignations_obj * assignations;    ///< List of assignations.

        float * p_E_A;                      ///< Probabilities a source is active \f$p(E^s_l|\mathcal{A})\f$
        float * p_E_I;                      ///< Probabilities a source is inactive \f$p(E^s_l|\mathcal{I})\f$
        float ** p_z_C;                     ///< Probabilities the signal perceived is coherent \f$p(\mathbf{z}^s_l|\mathcal{C},t)\f$
        float * p_z_D;                      ///< Probabilities the signal perceived is diffuse \f$p(\mathbf{z}^s_l|\mathcal{D})\f$

        float ** p_Eszs_phics;              ///< Probabilities \f$p(E^s_l,\mathbf{z}^s_l|\phi_c(s))\f$
        float ** p_phics;                   ///< Probabilities \f$p(\phi_c(s))\f$

        float * p_Ez_phic;                  ///< Probabilities \f$p(\mathbf{E}_l,\mathbf{z}_l|\phi_c)\f$
        float * p_phic;                     ///< Probabilities \f$p(\phi_c)\f$
        float * p_phic_Ez;                  ///< Probabilities \f$p(\phi_c|\mathbf{E}_l,\mathbf{z}_l)\f$

    } mixture_obj;

    /** Constructor. Initialize all fields to zero.
        \param      S               Number of potential sources.
        \param      T               Number of tracked sources.
        \return                     Pointer to the instantiated object.
    */  
    mixture_obj * mixture_construct_zero(const unsigned int S, const unsigned int T);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void mixture_destroy(mixture_obj * obj);

    /** Print the content of this object in the console.
        \param      obj             Object, which content is to be printed.
    */
    void mixture_printf(const mixture_obj * obj);

#endif