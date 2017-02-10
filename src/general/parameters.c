
    #include "parameters.h"

    parameters * parameters_construct_null(void) {

        parameters * params;

        params = (parameters *) malloc(sizeof(parameters));

        params->general = (parameters_general_obj *) NULL;
        params->raw = (parameters_raw_obj *) NULL;
        params->ssl = (parameters_ssl_obj *) NULL;
        params->sst = (parameters_sst_obj *) NULL;    

        return params;

    }

    void parameters_destroy(parameters * params) {

        if (params->general != NULL) {

            mics_destroy(params->general->mics);
            
            free((void *) params->general);

        }

        if (params->raw != NULL) {

            free((void *) params->raw);

        }

        if (params->ssl != NULL) {

            free((void *) params->ssl->levels);
            free((void *) params->ssl->deltasMax);
            free((void *) params->ssl->shape);
            
            free((void *) params->ssl);

        }

        if (params->sst != NULL) {

            free((void *) params->sst->mode);
            free((void *) params->sst->active_weight);
            free((void *) params->sst->active_mu);
            free((void *) params->sst->active_sigma);
            free((void *) params->sst->inactive_weight);
            free((void *) params->sst->inactive_mu);
            free((void *) params->sst->inactive_sigma);
            free((void *) params->sst->N_inactive);

            free((void *) params->sst);

        }

        free((void *) params);

    }

    void parameters_printf(const parameters * params) {

        unsigned int iMic;
        unsigned int iLevel;
        unsigned int iGaussian;
        unsigned int iTrack;

        // General

        printf("general:\n");

        printf(" - mics:\n");

        for (iMic = 0; iMic < params->general->mics->nMics; iMic++) {
            
            printf("    - (%02u): (%+1.3f, %+1.3f, %+1.3f)\n",
                   iMic,
                   params->general->mics->array[iMic * 3 + 0],
                   params->general->mics->array[iMic * 3 + 1],
                   params->general->mics->array[iMic * 3 + 2]);    

        }

        printf(" - hopSize: %u\n",params->general->hopSize);
        printf(" - frameSize: %u\n",params->general->frameSize);
        printf(" - fS: %u\n",params->general->fS);
        printf(" - c: %1.1f\n",params->general->c);

        // Raw

        printf("raw:\n");

        printf(" - nBitsIn: %u\n",params->raw->nBitsIn);
        printf(" - nBitsOut: %u\n",params->raw->nBitsOut);

        // SSL

        printf("ssl:\n");

        printf(" - nPots: %u\n",params->ssl->nPots);
        printf(" - nLevels: %u\n",params->ssl->nLevels);
        printf(" - levels:\n");

        for (iLevel = 0; iLevel < params->ssl->nLevels; iLevel++) {

            printf("    - (%01u): level = %u, deltaMax = %u\n",
                   iLevel,
                   params->ssl->levels[iLevel],
                   params->ssl->deltasMax[iLevel]);

        }

        printf(" - deltaReset: %u\n",params->ssl->deltaReset);
        printf(" - sigma: %1.3f\n",params->ssl->sigma);
        printf(" - nMatches: %u\n",params->ssl->nMatches);
        printf(" - epsilon: %1.3e\n",params->ssl->epsilon);
        printf(" - alpha: %1.3f\n",params->ssl->alpha);
        printf(" - R: %u\n",params->ssl->R);
        printf(" - shape: %s\n",params->ssl->shape);

        // SST

        printf("sst:\n");

        printf(" - mode: %s\n",params->sst->mode);
        printf(" - nTracks: %u\n",params->sst->nTracks);
        printf(" - sigmaQ: %1.3f\n",params->sst->sigmaQ);
        printf(" - sigmaR_prob: %1.3f\n",params->sst->sigmaR_prob);
        printf(" - sigmaR_active: %1.3f\n",params->sst->sigmaR_active);
        printf(" - epsilon: %1.3e\n",params->sst->epsilon);
        
        printf(" - active:\n");
        for (iGaussian = 0; iGaussian < params->sst->active_G; iGaussian++) {

            printf("    - (%02u): weight = %1.3f, mu = %1.3f, sigma = %1.3f\n",
                   iGaussian,
                   params->sst->active_weight[iGaussian],
                   params->sst->active_mu[iGaussian],
                   params->sst->active_sigma[iGaussian]);

        }
        printf(" - inactive:\n");
        for (iGaussian = 0; iGaussian < params->sst->inactive_G; iGaussian++) {

            printf("    - (%02u): weight = %1.3f, mu = %1.3f, sigma = %1.3f\n",
                   iGaussian,
                   params->sst->inactive_weight[iGaussian],
                   params->sst->inactive_mu[iGaussian],
                   params->sst->inactive_sigma[iGaussian]);

        }        
        
        printf(" - Pfalse: %1.3f\n",params->sst->Pfalse);
        printf(" - Pnew: %1.3f\n",params->sst->Pnew);
        printf(" - Ptrack: %1.3f\n",params->sst->Ptrack);
        printf(" - theta_new: %1.3f\n",params->sst->theta_new);
        printf(" - N_prob: %u\n",params->sst->N_prob);
        printf(" - theta_prob: %1.3f\n",params->sst->theta_prob);

        printf(" - N_active:\n");
        for (iTrack = 0; iTrack < params->sst->nTracks; iTrack++) {
            printf("    - (%02u): %u\n",iTrack,params->sst->N_inactive[iTrack]);
        }

        printf(" - theta_inactive: %1.3f\n",params->sst->theta_inactive);
        printf(" - nParticles: %u\n",params->sst->nParticles);
        printf(" - st_alpha: %1.3f\n",params->sst->st_alpha);
        printf(" - st_beta: %1.3f\n",params->sst->st_beta);
        printf(" - st_ratio: %1.3f\n",params->sst->st_ratio);
        printf(" - ve_alpha: %1.3f\n",params->sst->ve_alpha);
        printf(" - ve_beta: %1.3f\n",params->sst->ve_beta);
        printf(" - ve_ratio: %1.3f\n",params->sst->ve_ratio);
        printf(" - ac_alpha: %1.3f\n",params->sst->ac_alpha);
        printf(" - ac_beta: %1.3f\n",params->sst->ac_beta);
        printf(" - ac_ratio: %1.3f\n",params->sst->ac_ratio);
        printf(" - Nmin: %+1.3f\n",params->sst->Nmin);

    }