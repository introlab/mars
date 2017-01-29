#ifndef __MARS_SYSTEM_KALMAN2PRIOR
#define __MARS_SYSTEM_KALMAN2PRIOR

    /**
    * \file     kalman2coherence.h
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
    #include <math.h>

    #include "../signal/coherence.h"
    #include "../signal/kalman.h"
    #include "../signal/pot.h"
    #include "../utils/matrix.h"

    //! Generator of coherence probability from the Kalman filter and observations
    typedef struct kalman2coherence_obj {

        float epsilon;                                      ///< Small value to avoir overflow.

        matrix_obj * H;                                     ///< \f$\mathbf{H}\f$.
        matrix_obj * Ht;                                    ///< \f$\mathbf{H}^T\f$.

        matrix_obj * mu_t;                                  ///< \f$\bm{\mu}^t_l\f$.
        matrix_obj * mu_t_t;                                ///< \f$(\bm{\mu}^t_l)^T\f$.
        matrix_obj * mu_s;                                  ///< \f$\bm{\mu}^s_l\f$.
        matrix_obj * mu_s_t;                                ///< \f$(\bm{\mu}^s_l)^T\f$.
        matrix_obj * mu_st;                                 ///< \f$\bm{\mu}^{s,t}_l\f$.
        matrix_obj * mu_st_t;                               ///< \f$(\bm{\mu}^{s,t}_l)^T\f$.

        matrix_obj * HP;                                    ///< \f$\mathbf{H}\mathbf{P}\f$.
        matrix_obj * sigma_epsilon;                         ///< \f$\epsilon\f$

        matrix_obj * sigma_t;                               ///< \f$\bm{\Sigma}^t_l\f$
        matrix_obj * sigma_s;                               ///< \f$\bm{\Sigma}^s_l\f$
        matrix_obj * sigma_st;                              ///< \f$\bm{\Sigma}^{s,t}_l\f$
        
        matrix_obj * sigma_t_epsilon;                       ///< \f$\bm{\Sigma}^t_l + \epsilon\f$
        matrix_obj * sigma_t_inv;                           ///< \f$(\bm{\Sigma}^t_l)^{-1}\f$
        matrix_obj * sigma_s_inv;                           ///< \f$(\bm{\Sigma}^s_l)^{-1}\f$
        matrix_obj * sigma_st_inv;                          ///< \f$(\bm{\Sigma}^{s,t}_l)^{-1}\f$

        matrix_obj * sigma_t_inv_mu_t;                      ///< \f$(\bm{\Sigma}^t_l)^{-1}\bm{\mu}^t_l\f$
        matrix_obj * sigma_s_inv_mu_s;                      ///< \f$(\bm{\Sigma}^s_l)^{-1}\bm{\mu}^s_l\f$
        matrix_obj * sigma_st_inv_mu_st;                    ///< \f$(\bm{\Sigma}^{s,t}_l)^{-1}\bm{\mu}^{s,t}_l\f$

        matrix_obj * mu_t_t_sigma_t_inv_mu_t;               ///< \f$((\bm{\mu}^t_l)^T\bm{\Sigma}^t_l)^{-1}\bm{\mu}^t_l\f$
        matrix_obj * mu_s_t_sigma_s_inv_mu_s;               ///< \f$((\bm{\mu}^s_l)^T\bm{\Sigma}^s_l)^{-1}\bm{\mu}^s_l\f$
        matrix_obj * mu_st_t_sigma_st_inv_mu_st;            ///< \f$((\bm{\mu}^{s,t}_l)^T\bm{\Sigma}^{s,t}_l)^{-1}\bm{\mu}^{s,t}_l\f$

        matrix_obj * sigma_t_inv_mu_t_sigma_s_inv_mu_s;     ///< \f$(\bm{\Sigma}^t_l)^{-1}\bm{\mu}^t_l+(\bm{\Sigma}^s_l)^{-1}\bm{\mu}^s_l\f$

    } kalman2coherence_obj;

    /** Constructor. Initialize all fields to zero.
        \param      epsilon         Small value to avoid overflow.
        \param      sigmaR          Standard deviation in the matrix \f$\mathbf{R}\f$.
        \return                     Pointer to the instantiated object.
    */ 
    kalman2coherence_obj * kalman2coherence_construct(const float epsilon, const float sigmaR);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void kalman2coherence_destroy(kalman2coherence_obj * obj);

    /** Fill the coherence object with probabilities \f$p(\mathbf{z}^s_l|\mathcal{C},t)\f$ for all \f$s\f$ and a given \f$t\f$.
        \param      kalman          Kalman filter.
        \param      pots            Potential sources.
        \param      coherence       Coherence.
        \param      obj             Object to be used.
    */
    void kalman2coherence_process(kalman2coherence_obj * obj, const kalman_obj * kalman, const pots_obj * pots, coherence_obj * coherence);


#endif