#ifndef __MARS_SYSTEM_KALMAN2KALMAN
#define __MARS_SYSTEM_KALMAN2KALMAN

    /**
    * \file     kalman2kalman.h
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

    #include "../signal/postprob.h"
    #include "../signal/kalman.h"
    #include "../signal/pot.h"
    #include "../utils/matrix.h"

    //! Update the states of the Kalman filter
    typedef struct kalman2kalman_obj {

        float epsilon;                  ///< \f$\epsilon\f$

        float deltaT;                   ///< \f$\Delta T\f$
        float sigmaQ;                   ///< \f$\sigma_Q\f$
        float sigmaR;                   ///< \f$\sigma_R\f$

        matrix_obj * F;                 ///< \f$\mathbf{F}\f$
        matrix_obj * Ft;                ///< \f$\mathbf{F}^T\f$
        matrix_obj * Q;                 ///< \f$\mathbf{Q}\f$
        matrix_obj * H;                 ///< \f$\mathbf{H}\f$
        matrix_obj * Ht;                ///< \f$\mathbf{H}^T\f$
        matrix_obj * R;                 ///< Frame update rate

        matrix_obj * FP;                ///< \f$\mathbf{F}\mathbf{P}\f$
        matrix_obj * FPFt;              ///< \f$\mathbf{F}\mathbf{P}\mathbf{F}^T\f$
        
        matrix_obj * K;                 ///< \f$\mathbf{K}^t\f$
        matrix_obj * PHt;               ///< \f$\mathbf{P}^t_{l|l-1}\mathbf{H}^T\f$
        matrix_obj * HP;                ///< \f$\mathbf{H}\mathbf{P}^t_{l|l-1}\f$
        matrix_obj * HPHt;              ///< \f$\mathbf{H}\mathbf{P}^t_{l|l-1}\mathbf{H}^T\f$
        matrix_obj * HPHt_R;            ///< \f$\mathbf{H}\mathbf{P}^t_{l|l-1}\mathbf{H}^T + \mathbf{R}\f$
        matrix_obj * HPHt_Rinv;         ///< \f$(\mathbf{H}\mathbf{P}^t_{l|l-1}\mathbf{H}^T + \mathbf{R})^{-1}\f$
        matrix_obj * Hx;                ///< \f$\mathbf{H}\mathbf{x}^t_{l|l-1}\f$
        matrix_obj * z;                 ///< \f$\mathbf{z}^s_l\f$
        matrix_obj * z_Hx;              ///< \f$\mathbf{z}^s_l-\mathbf{H}\mathbf{x}^t_{l|l-1}\f$
        matrix_obj * Kz_Hx;             ///< \f$\mathbf{K}^t(\mathbf{z}^s_l-\mathbf{H}\mathbf{x}^t_{l|l-1})\f$
        matrix_obj * pKz_Hx;            ///< \f$p(t|\mathbf{E}_l,\mathbf{z}_l)\mathbf{K}^t\mathbf{H}\mathbf{P}^t_{l|l-1}\f$
        matrix_obj * KHP;               ///< \f$\mathbf{K}^t\mathbf{H}\mathbf{P}^t_{l|l-1}\f$
        matrix_obj * pKHP;              ///< \f$p(t|\mathbf{E}_l,\mathbf{z}_l)\mathbf{K}^t\mathbf{H}\mathbf{P}^t_{l|l-1}\f$

    } kalman2kalman_obj;

    /** Constructor. Initialize all fields.
        \param      deltaT          Time interval (in sec) between frames.
        \param      sigmaQ          Parameter \f$\sigma_Q\f$ in matrix \f$\mathbf{Q}\f$.
        \param      sigmaR          Parameter \f$\sigma_R\f$ in matrix \f$\mathbf{R}\f$.
        \param      epsilon         Small value to avoid overflow.
        \return                     Pointer to the instantiated object.
    */ 
    kalman2kalman_obj * kalman2kalman_construct(const float deltaT, const float sigmaQ, const float sigmaR, const float epsilon);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void kalman2kalman_destroy(kalman2kalman_obj * obj);

    /** Initialize the kalman filter to the position of the potential source.
        \param      pot             Potential source.
        \param      kalman          New tracked source.
        \param      obj             Object to be used.
    */
    void kalman2kalman_init(kalman2kalman_obj * obj, const pot_obj * pot, kalman_obj * kalman);

    /** Predict the next state of the Kalman filter.
        \param      kalman          Kalman filter which states are predicted.
        \param      obj             Object to be used.
    */
    void kalman2kalman_predict(kalman2kalman_obj * obj, kalman_obj * kalman);

    /** Update the state of the Kalman filter according to new observations.
        \param      postprob        Probabilities \f$p(t|\mathbf{E}_l^s,\mathbf{z}_l^s)\f$ for all \f$s\f$.
        \param      pots            Potential sources.
        \param      kalman          Kalman filter which states are updated.
        \param      obj             Object to be used.
    */
    void kalman2kalman_update(kalman2kalman_obj * obj, const postprob_obj * postprob, const pots_obj * pots, kalman_obj * kalman);

    /** Estimate the position of the tracked source.
        \param      kalman          Kalman filter.
        \param      coord           3D estimated position.
        \param      obj             Object to be used.
    */
    void kalman2kalman_estimate(kalman2kalman_obj * obj, const kalman_obj * kalman, coord_obj * coord);

#endif