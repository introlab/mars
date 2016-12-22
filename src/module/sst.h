#ifndef __MARS_SYST_SST
#define __MARS_SYST_SST

    /**
    * \file     obs2probs.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  1.0
    * \date     2016-12-14
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

    #include "../signal/vector.h"
    #include "../signal/matrix.h"

    #include <stdlib.h>

    typedef struct sst_obj{

        unsigned int Tmax;
        unsigned int Cmax;

        unsigned int S;
        unsigned int T;
        unsigned int C;

        obs2kalman_obj ** filters;
        float Q_sigma2;
        float R_sigma2;

        vector_float * p_E_active;
        matrix_float * p_E_active_gmm;

        vector_float * p_E_inactive;
        matrix_float * p_E_inactive_gmm;
        
        matrix_float * p_z_coherent;
        float p_z_coherent_sigma;

        vector_float * p_z_diffuse;
        float p_z_diffuse_constant;

        matrix_float * p_E_z_phi;

        float P_false;
        float P_true;
        vector_float * p_phi;

        vector_float * p_E_z_phi_c;
        vector_float * p_phi_c;
        vector_float * p_phi_c_E_z;

        float p_new_E_z;
        vector_float * p_t_E_z;

        matrix_signedint * phis;

        vector_float * obs;
        vector_float * x_predicted;
        vector_float * x_updated;

    } sst_obj;

    sst_obj * sst_construct(const unsigned int Tmax, const unsigned int S, const matrix_float * p_E_active_gmm, const matrix_float * p_E_inactive_gmm, const float p_z_coherent_sigma, const float p_z_diffuse_constant, const float P_false, const float P_true, const float Q_sigma2, const float R_sigma2);

    void sst_destroy(sst_obj * obj);

    int sst_process(sst_obj * obj, const msg_pots_obj * pots, msg_tracks_obj * tracks);

#endif