    
    #include "parameters2config.h"

    src_raw_cfg * parameters2src_raw(const parameters_obj * obj) {

        src_raw_cfg * cfg;

        cfg = src_raw_cfg_construct();

        cfg->hopSize = obj->general->hopSize;
        cfg->nMics = obj->general->mics->nSignals;
        cfg->nBits = obj->raw->nBits;
        cfg->fileName = (char *) malloc(sizeof(char) * 1024);
        strcpy(cfg->fileName, "");

        return cfg;

    }

    msg_hops_cfg * parameters2msg_hops(const parameters_obj * obj) {

        msg_hops_cfg * cfg;

        cfg = msg_hops_cfg_construct();

        cfg->hopSize = obj->general->hopSize;
        cfg->nMics = obj->general->mics->nSignals;

        return cfg;        

    }

    mod_stft_cfg * parameters2mod_stft(const parameters_obj * obj) {

        mod_stft_cfg * cfg;

        cfg = mod_stft_cfg_construct();

        cfg->hopSize = obj->general->hopSize;
        cfg->frameSize = obj->general->frameSize;
        cfg->nMics = obj->general->mics->nSignals;

        return cfg;

    }

    msg_spectra_cfg * parameters2msg_spectra(const parameters_obj * obj) {

        msg_spectra_cfg * cfg;

        cfg = msg_spectra_cfg_construct();

        cfg->frameSize = obj->general->frameSize;
        cfg->nMics = obj->general->mics->nSignals;

        return cfg;

    }

    mod_ssl_cfg * parameters2mod_ssl(const parameters_obj * obj) {

        mod_ssl_cfg * cfg;

        cfg = mod_ssl_cfg_construct();

        cfg->mics = mics_construct_mics(obj->general->mics);
        cfg->nPots = obj->ssl->nPots;
        cfg->fS = obj->general->fS;
        cfg->c = obj->general->c;
        cfg->frameSize = obj->general->frameSize;
        cfg->nMatches = obj->ssl->nMatches;
        cfg->sigma = obj->ssl->sigma;
        cfg->epsilon = obj->ssl->epsilon;
        cfg->alpha = obj->ssl->alpha;
        cfg->shape = (char *) malloc(sizeof(char) * (strlen(obj->ssl->shape)+1));
        strcpy(cfg->shape,obj->ssl->shape);
        cfg->nLevels = obj->ssl->nLevels;
        cfg->levels = (unsigned int *) malloc(sizeof(unsigned int) * obj->ssl->nLevels);
        memcpy(cfg->levels, obj->ssl->levels, sizeof(unsigned int) * obj->ssl->nLevels);
        cfg->deltasMax = (unsigned int *) malloc(sizeof(unsigned int) * obj->ssl->nLevels);
        memcpy(cfg->deltasMax, obj->ssl->deltasMax, sizeof(unsigned int) * obj->ssl->nLevels);
        cfg->deltaReset = obj->ssl->deltaReset;
        cfg->R = obj->ssl->R;

        return cfg;

    }

    msg_pots_cfg * parameters2msg_pots(const parameters_obj * obj) {

        msg_pots_cfg * cfg;

        cfg = msg_pots_cfg_construct();

        cfg->nPots = obj->ssl->nPots;

        return cfg;

    }

    snk_pots_cfg * parameters2snk_pots(const parameters_obj * obj) {

        snk_pots_cfg * cfg;

        cfg = snk_pots_cfg_construct();

        cfg->fileName = (char *) malloc(sizeof(char) * 1024);
        strcpy(cfg->fileName, "");
        cfg->format = (char *) malloc(sizeof(char) * 64);
        strcpy(cfg->fileName, "");

        return cfg;

    }

    mod_sst_cfg * parameters2mod_sst(const parameters_obj * obj) {

        mod_sst_cfg * cfg;
        unsigned int iGaussian;

        cfg = mod_sst_cfg_construct();

        cfg->nPots = obj->ssl->nPots;
        cfg->nTracks = obj->sst->nTracks;
        cfg->mode = (char *) malloc(sizeof(char) * (strlen(obj->sst->mode)+1));
        strcpy(cfg->mode, obj->sst->mode);
        cfg->R = obj->ssl->R;
        cfg->hopSize = obj->general->hopSize;
        cfg->fS = obj->general->fS;
        cfg->sigmaQ = obj->sst->sigmaQ;
        cfg->nParticles = obj->sst->nParticles;
        cfg->st_alpha = obj->sst->st_alpha;
        cfg->st_beta = obj->sst->st_beta;
        cfg->st_ratio = obj->sst->st_ratio;
        cfg->ve_alpha = obj->sst->ve_alpha;
        cfg->ve_beta = obj->sst->ve_beta;
        cfg->ve_ratio = obj->sst->ve_ratio;
        cfg->ac_alpha = obj->sst->ac_alpha;
        cfg->ac_beta = obj->sst->ac_beta;
        cfg->ac_ratio = obj->sst->ac_ratio;
        cfg->Nmin = obj->sst->Nmin;

        cfg->epsilon = obj->sst->epsilon;
        cfg->sigmaR = obj->sst->sigmaR;

        cfg->active_gmm = gaussians_1d_construct_null(obj->sst->active_G);

        for (iGaussian = 0; iGaussian < obj->sst->active_G; iGaussian++) {

            cfg->active_gmm->array[iGaussian] = gaussian_1d_construct_weightmusigma(obj->sst->active_weight[iGaussian],
                                                                                    obj->sst->active_mu[iGaussian],
                                                                                    obj->sst->active_sigma[iGaussian]);

        }

        cfg->inactive_gmm = gaussians_1d_construct_null(obj->sst->inactive_G);

        for (iGaussian = 0; iGaussian < obj->sst->inactive_G; iGaussian++) {

            cfg->inactive_gmm->array[iGaussian] = gaussian_1d_construct_weightmusigma(obj->sst->inactive_weight[iGaussian],
                                                                                      obj->sst->inactive_mu[iGaussian],
                                                                                      obj->sst->inactive_sigma[iGaussian]);

        }        
        
        cfg->Pfalse = obj->sst->Pfalse;
        cfg->Pnew = obj->sst->Pnew;
        cfg->Ptrack = obj->sst->Ptrack;
        cfg->shape = (char *) malloc(sizeof(char) * (strlen(obj->ssl->shape)+1));
        strcpy(cfg->shape,obj->ssl->shape);
        cfg->theta_new = obj->sst->theta_new;
        cfg->N_prob = obj->sst->N_prob;
        cfg->theta_prob = obj->sst->theta_prob;
        cfg->N_inactive = (unsigned int *) malloc(sizeof(unsigned int) * obj->sst->nTracks);
        memcpy(cfg->N_inactive, obj->sst->N_inactive, sizeof(unsigned int) * obj->sst->nTracks);
        cfg->theta_inactive = obj->sst->theta_inactive;

        return cfg;

    }

    msg_tracks_cfg * parameters2msg_tracks(const parameters_obj * obj) {

        msg_tracks_cfg * cfg;

        cfg = msg_tracks_cfg_construct();

        cfg->nTracks = obj->sst->nTracks;

        return cfg;

    }

    snk_tracks_cfg * parameters2snk_tracks(const parameters_obj * obj) {

        snk_tracks_cfg * cfg;

        cfg = snk_tracks_cfg_construct();

        cfg->fileName = (char *) malloc(sizeof(char) * 1024);
        strcpy(cfg->fileName, "");
        cfg->format = (char *) malloc(sizeof(char) * 64);
        strcpy(cfg->fileName, "");

        return cfg;

    }