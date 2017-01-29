#ifndef __MARS_SYSTEM_MIXTURE2MIXTURE
#define __MARS_SYSTEM_MIXTURE2MIXTURE

    /**
    * \file     mixture2mixture.h
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
    #include <math.h>

    #include "../utils/gaussian.h"
    #include "../signal/coherence.h"
    #include "../signal/mixture.h"
    #include "../signal/pot.h"
    #include "../signal/postprob.h"

    //! Mixture
    typedef struct mixture2mixture_obj {

        gaussians_1d_obj * active;          ///< Gaussian mixture model (GMM) for the energy distribution of an active source.
        gaussians_1d_obj * inactive;        ///< Gaussian mixture model (GMM) for the energy distribution of an inactive source.
        float diffuse;                      ///< Diffuse constant probability \f$p(\mathbf{z}_l^s|\mathcal{D})\f$.

        float Pfalse;                       ///< A priori probability there is a false detection (\f$P_{false}\f$).
        float Pnew;                         ///< A priori probability there is a new detection (\f$P_{new}\f$).
        float Ptrack;                       ///< A priori probability an tracked source is observed (\f$P_{track}\f$).

    } mixture2mixture_obj;

    /** Constructor. Initialize all fields.
        \param      active_gmm      GMM that models the energy distribution for an active source.
        \param      inactive_gmm    GMM that models the energy distribution for an inactive source.        
        \param      diffuse_cst     Diffuse constant probability \f$p(\mathbf{z}_l^s|\mathcal{D})\f$.
        \param      Pfalse          A priori probability there is a false detection (\f$P_{false}\f$).
        \param      Pnew            A priori probability there is a new detection (\f$P_{new}\f$).
        \param      Ptrack          A priori probability an tracked source is observed (\f$P_{track}\f$).
        \return                     Pointer to the instantiated object.
    */ 
    mixture2mixture_obj * mixture2mixture_construct(const gaussians_1d_obj * active_gmm, const gaussians_1d_obj * inactive_gmm, const float diffuse_cst, const float Pfalse, const float Pnew, const float Ptrack);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void mixture2mixture_destroy(mixture2mixture_obj * obj);

    /** Process the mixture. Update all probabilities.
        \param      mixture         Mixture object.
        \param      pots            Potential sources.
        \param      coherences      Coherences probabilities \f$p(\mathbf{z}^s_l|\mathcal{C},t)\f$ for all \f$s\f$ and \f$t\f$.
        \param      postprobs       Post probabilities \f$p(t|\mathbf{E}_l^s,\mathbf{z}_l^s)\f$ for all \f$s\f$ and \f$t\f$, and \f$p(new|\mathbf{E}_l^s,\mathbf{z}_l^s)\f$ for all \f$s\f$
        \param      obj             Object to be used.
    */
    void mixture2mixture_process(mixture2mixture_obj * obj, mixture_obj * mixture, const pots_obj * pots, const coherences_obj * coherences, postprobs_obj * postprobs);

#endif