    
    #include "sst.h"

    sst_obj * sst_construct(const unsigned int Tmax, const unsigned int S, const matrix_float * p_E_active_gmm, const matrix_float * p_E_inactive_gmm, const float p_z_coherent_sigma, const float p_z_diffuse_constant, const float P_false, const float P_true, const float Q_sigma2, const float R_sigma2) {

        sst_obj * obj;
        unsigned int t;

        obj = (sst_obj *) malloc(sizeof(sst_obj));

        obj->S = S;

        obj->Tmax = Tmax;
        obj->Cmax = assignments_count(obj->S,obj->Tmax);

        obj->filters = (obs2kalman_obj *) malloc(sizeof(obs2kalman_obj));

        for (t = 0; t < Tmax; t++) {

            obj->filters[t] = obs2kalman_construct(Q_sigma2, R_sigma2);

        }

        obj->T = 0;
        obj->C = assignments_count(obj->S,obj->T);
        
        obj->Q_sigma2 = Q_sigma2;
        obj->R_sigma2 = R_sigma2;

        obj->p_E_active = vector_float_malloc(obj->S);
        obj->p_E_active_gmm = matrix_float_clone(p_E_active_gmm);
        obj->p_E_inactive = vector_float_malloc(obj->S);
        obj->p_E_inactive_gmm = matrix_float_clone(p_E_inactive_gmm);

        obj->p_z_coherent = matrix_float_malloc(obj->Tmax,obj->S);
        obj->p_z_coherent_sigma = p_z_coherent_sigma;
        obj->p_z_diffuse = vector_float_malloc(obj->S);
        obj->p_z_diffuse_constant = p_z_diffuse_constant;

        obj->p_E_z_phi = matrix_float_malloc(obj->Tmax+2,obj->S);
        obj->p_phi = vector_float_malloc(obj->Tmax+2);

        obj->P_false = P_false;
        obj->P_true = P_true;

        obj->p_E_z_phi_c = vector_float_malloc(obj->Cmax);
        obj->p_phi_c = vector_float_malloc(obj->Cmax);
        obj->p_phi_c_E_z = vector_float_malloc(obj->Cmax);

        obj->p_t_E_z = vector_float_malloc(obj->Tmax);

        obj->phis = matrix_signedint_malloc(obj->Cmax,obj->S);

        obj->obs = vector_float_malloc(3);
        obj->x_predicted = vector_float_malloc(3);
        obj->x_updated = vector_float_malloc(3);

        return obj;

    }

    void sst_destroy(sst_obj * obj) {

    }

    int sst_process(sst_obj * obj, const msg_pots_obj * pots, msg_tracks_obj * tracks) {

        unsigned int t;
        unsigned int s;
        unsigned int g;
        unsigned int c;
        float total;

        float diffX;
        float diffY;
        float diffZ;
        float dist;

        // Predict & Normalize

        for (t = 0; t < obj->T; t++) {
            obs2kalman_predict(obj->filters[t]);
        }

        // Assignation

        obj->C = assignments_count(obj->S, obj->T);
        assignments_generate(obj->S, obj->T, obj->phis);

        // Likelihood

        vector_float_zero(obj->p_E_active);
        vector_float_zero(obj->p_E_inactive);

        for (s = 0; s < obj->S; s++) {

            for (g = 0; g < obj->p_E_active_gmm->nRows; g++) {

                obj->p_E_active->array[s] += obj->p_E_active_gmm->array[g][0] * distribution_normal(pots->samples[s][3], obj->p_E_active_gmm->array[g][1], obj->p_E_active_gmm->array[g][2]);
                obj->p_E_inactive->array[s] += obj->p_E_inactive_gmm->array[g][0] * distribution_normal(pots->samples[s][3], obj->p_E_inactive_gmm->array[g][1], obj->p_E_inactive_gmm->array[g][2]);

            }

        }

        for (t = 0; t < obj->T; t++) {

            obs2kalman_getPredicted(obj->filters[t], obj->x_predicted);

            for (s = 0; t < obj->S; s++) {

                diffX = pots->samples[s][0] - obj->x_predicted->array[0];
                diffY = pots->samples[s][1] - obj->x_predicted->array[1];
                diffZ = pots->samples[s][2] - obj->x_predicted->array[2];

                dist = sqrtf(diffX*diffX + diffY*diffY + diffZ*diffZ);

                obj->p_z_coherent->array[t][s] = distribution_normal(dist,0,obj->p_z_coherent_sigma);

            }

        }

        for (s = 0; s < obj->S; s++) {

            obj->p_z_diffuse->array[s] = obj->p_z_diffuse_constant;

        }

        for (t = 0; t < (obj->T+2); t++) {

            for (s = 0; s < obj->S; s++) {

                if (t == 0) {
                    
                    obj->p_E_z_phi->array[t][s] = obj->p_E_inactive->array[s] * obj->p_z_diffuse->array[s];

                }
                else if (t == 1) {

                    obj->p_E_z_phi->array[t][s] = obj->p_E_active->array[s] * obj->p_z_diffuse->array[s];

                }
                else {

                    obj->p_E_z_phi->array[t][s] = obj->p_E_active->array[s] * obj->p_z_coherent->array[t-2][s];

                }

            }

        }

        // Prior probabilities

        for (t = 0; t < (obj->T+2); t++) {

            if (t == 0) {
                
                obj->p_phi->array[t] = P_false;

            }
            else if (t == 1) {

                obj->p_phi->array[t] = P_true;

            }
            else {

                obj->p_phi->array[t] = (1.0f - P_false - P_true) / obj->T;

            }

        }

        // Posterior probabilities

        total = 0.0f;

        for (c = 0; c < obj->C; c++) {

            p_phi_c->array[c] = 1.0f;
            p_E_z_phi_c->array[c] = 1.0f;

            for (s = 0; s < obj->S; s++) {

                t = (unsigned int) (2 + obj->phis->array[c][s]);

                p_phi_c->array[c] *= obj->p_phi->array[t];
                p_E_z_phi_c->array[c] * = obj->p_E_z_phi->array[t];

            }            

            p_phi_c_E_z->array[c] = p_phi_c->array[c] * p_E_z_phi_c->array[c];

            total += p_phi_c_E_z->array[c];

        }

        for (c = 0; c < obj->C; c++) {

            p_phi_c_E_z->array[c] /= total;

        }

        obj->p_new_E_z = 0.0f;

        for (c = 0; c < obj->C; c++) {

            for (s = 0; s < obj->S; s++) {

                if (obj->phis->array[c][s] == -1) {
                    
                    obj->p_new_E_z += p_phi_c_E_z->array[c];
                    break;

                }

            }

        }

        vector_float_zero(obj->p_t_E_z);

        for (t = 0; t < obj->T; t++) {

            for (c = 0; c < obj->C; c++) {

                for (s = 0; s < obj->S; s++) {

                    if (obj->phis->array[c][s] == (signed int) t) {
                        
                        obj->p_t_E_z->array[t] += p_phi_c_E_z->array[c];
                        break;

                    }

                }

            }

        }

        // Remove

        // Add

        // Update
/*
        for (t = 0; t < obj->T; t++) {

            obj->obs->array[0] = pots->samples[0];
            obj->obs->array[1] = pots->samples[1];
            obj->obs->array[2] = pots->samples[2];

            obs2kalman_update(obj->filters[t], obj->obs, obj->p_t_E_z->array[t]);

        }
*/
    }