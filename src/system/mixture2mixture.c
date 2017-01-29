
    #include "mixture2mixture.h"

    mixture2mixture_obj * mixture2mixture_construct(const gaussians_1d_obj * active_gmm, const gaussians_1d_obj * inactive_gmm, const float diffuse_cst, const float Pfalse, const float Pnew, const float Ptrack) {

        mixture2mixture_obj * obj;

        obj = (mixture2mixture_obj *) malloc(sizeof(mixture2mixture_obj));

        obj->active = gaussians_1d_construct_gaussians(active_gmm);
        obj->inactive = gaussians_1d_construct_gaussians(inactive_gmm);
        obj->diffuse = diffuse_cst;

        obj->Pfalse = Pfalse;
        obj->Pnew = Pnew;
        obj->Ptrack = Ptrack;

        return obj;

    }

    void mixture2mixture_destroy(mixture2mixture_obj * obj) {

    }

    void mixture2mixture_process(mixture2mixture_obj * obj, mixture_obj * mixture, const pots_obj * pots, const coherences_obj * coherences, postprobs_obj * postprobs) {

        unsigned int iS;
        unsigned int iP;
        unsigned int iC;
        unsigned int iT;
        signed int t;
        float total;
        unsigned char match;

        // Compute likelihood

        // p(E^s_l|A), p(E^s_l|I) & p(z^s_l|D)

        for (iS = 0; iS < mixture->S; iS++) {

             mixture->p_E_A[iS] = gaussians_1d_eval(obj->active, pots->array[iS]->E);
             mixture->p_E_I[iS] = gaussians_1d_eval(obj->inactive, pots->array[iS]->E);
             mixture->p_z_D[iS] = obj->diffuse;

        }

        // p(z^s_l|C,t)

        for (iT = 0; iT < mixture->T; iT++) {

            for (iS = 0; iS < mixture->S; iS++) {

                mixture->p_z_C[iT][iS] = coherences->array[iT]->probs[iS];

            }

        }

        // p(E^s_l,z^s_l|phis_c) & p(phis_c)

        for (iS = 0; iS < mixture->S; iS++) {

            for (iT = 0; iT < mixture->TND; iT++) {

                t = (((signed int) iT) - 2);

                if (t == -2) {

                    mixture->p_Eszs_phics[iS][iT] = mixture->p_E_I[iS] * mixture->p_z_D[iS];

                }
                else if (t == -1) {

                    mixture->p_Eszs_phics[iS][iT] = mixture->p_E_A[iS] * mixture->p_z_D[iS];

                }
                else {

                	mixture->p_Eszs_phics[iS][iT] = mixture->p_E_A[iS] * mixture->p_z_C[t][iS];

                }

            }

        }

        // Prior probabilities

        for (iS = 0; iS < mixture->S; iS++) {

            for (iT = 0; iT < mixture->TND; iT++) {

                t = (((signed int) iT) - 2);

                if (t == -2) {

                    mixture->p_phics[iS][iT] = obj->Pfalse;

                }
                else if (t == -1) {

                    mixture->p_phics[iS][iT] = obj->Pnew;                        

                }
                else {

                	mixture->p_phics[iS][iT] = obj->Ptrack;

                }                    

            }

        }

        // Posterior probabilities

        total = 0.0f;

        for (iC = 0; iC < mixture->C; iC++) {

            mixture->p_Ez_phic[iC] = 1.0f;
            mixture->p_phic[iC] = 1.0f;

            for (iS = 0; iS < mixture->S; iS++) {

                t = mixture->assignations->array[iC]->array[iS];
                iT = (unsigned int) (t + 2);

                mixture->p_Ez_phic[iC] *= mixture->p_Eszs_phics[iS][iT];
                mixture->p_phic[iC] *= mixture->p_phics[iS][iT];

            }

            mixture->p_phic_Ez[iC] = mixture->p_Ez_phic[iC] * mixture->p_phic[iC];

            total += mixture->p_phic_Ez[iC];

        }

        for (iC = 0; iC < mixture->C; iC++) {

            mixture->p_phic_Ez[iC] /= total;

        }

        // Tracking - Potential probabilities

        for (iT = 0; iT < mixture->T; iT++) {

            t = ((signed int) iT);

            for (iS = 0; iS < mixture->S; iS++) {

                postprobs->p_track[iT]->probs[iS] = 0.0f;

                for (iC = 0; iC < mixture->C; iC++) {

                    if (mixture->assignations->array[iC]->array[iS] == t) {

                        postprobs->p_track[iT]->probs[iS] += mixture->p_phic_Ez[iC];

                    }

                }

            }    

        }

        // New probabilities

        for (iS = 0; iS < mixture->S; iS++) {

            postprobs->p_new->probs[iS] = 0.0f;

            for (iC = 0; iC < mixture->C; iC++) {

                if (mixture->assignations->array[iC]->array[iS] == -1) {

                    postprobs->p_new->probs[iS] += mixture->p_phic_Ez[iC];

                }

            }

        }                 

        // Tracking probabilities

        for (iT = 0; iT < mixture->T; iT++) {

            t = ((signed int) iT);
            postprobs->p_track[iT]->probTotal = 0.0f;

            for (iC = 0; iC < mixture->C; iC++) {

                match = 0;

                for (iS = 0; iS < mixture->S; iS++) {

                    if (mixture->assignations->array[iC]->array[iS] == t) {

                        match = 1;
                        break;

                    }

                }

                if (match == 1) {

                    postprobs->p_track[iT]->probTotal += mixture->p_phic_Ez[iC];

                }

            }              

        }

    }