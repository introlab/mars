
    #include "parameters2configs.h"

    void parameters2configs(configs * cfgs, const parameters * params) {

        cfgs->src_raw_file = parameters2configs_src_raw_file(params);
        cfgs->msg_hops = parameters2configs_msg_hops(params);
        cfgs->mod_stft = parameters2configs_mod_stft(params);
        cfgs->msg_spectra = parameters2configs_msg_spectra(params);
        cfgs->mod_ssl = parameters2configs_mod_ssl(params);
        cfgs->msg_pots = parameters2configs_msg_pots(params);
        cfgs->snk_pots_file = parameters2configs_snk_pots_file(params);
        cfgs->mod_sst = parameters2configs_mod_sst(params);
        cfgs->msg_tracks = parameters2configs_msg_tracks(params);
        cfgs->snk_tracks_file = parameters2configs_snk_tracks_file(params);

    }

    src_raw_file_cfg * parameters2configs_src_raw_file(const parameters * params) {

        src_raw_file_cfg * cfg;

        cfg = src_raw_file_cfg_construct();

        cfg->hopSize = params->general->hopSize;
        cfg->nMics = params->general->mics->nSignals;
        cfg->nBits = params->raw->nBits;
        cfg->fileName = (char *) malloc(sizeof(char) * 1024);
        strcpy(cfg->fileName, "");

        return cfg;

    }

    msg_hops_cfg * parameters2configs_msg_hops(const parameters * params) {

        msg_hops_cfg * cfg;

        cfg = msg_hops_cfg_construct();

        cfg->hopSize = params->general->hopSize;
        cfg->nMics = params->general->mics->nSignals;

        return cfg;        

    }

    mod_stft_cfg * parameters2configs_mod_stft(const parameters * params) {

        mod_stft_cfg * cfg;

        cfg = mod_stft_cfg_construct();

        cfg->hopSize = params->general->hopSize;
        cfg->frameSize = params->general->frameSize;
        cfg->nMics = params->general->mics->nSignals;

        return cfg;

    }

    msg_spectra_cfg * parameters2configs_msg_spectra(const parameters * params) {

        msg_spectra_cfg * cfg;

        cfg = msg_spectra_cfg_construct();

        cfg->frameSize = params->general->frameSize;
        cfg->nMics = params->general->mics->nSignals;

        return cfg;

    }

    mod_ssl_cfg * parameters2configs_mod_ssl(const parameters * params) {

        mod_ssl_cfg * cfg;

        cfg = mod_ssl_cfg_construct();

        cfg->mics = mics_construct_mics(params->general->mics);
        cfg->nPots = params->ssl->nPots;
        cfg->fS = params->general->fS;
        cfg->c = params->general->c;
        cfg->frameSize = params->general->frameSize;
        cfg->nMatches = params->ssl->nMatches;
        cfg->sigma = params->ssl->sigma;
        cfg->epsilon = params->ssl->epsilon;
        cfg->alpha = params->ssl->alpha;
        cfg->shape = (char *) malloc(sizeof(char) * (strlen(params->ssl->shape)+1));
        strcpy(cfg->shape,params->ssl->shape);
        cfg->nLevels = params->ssl->nLevels;
        cfg->levels = (unsigned int *) malloc(sizeof(unsigned int) * params->ssl->nLevels);
        memcpy(cfg->levels, params->ssl->levels, sizeof(unsigned int) * params->ssl->nLevels);
        cfg->deltasMax = (unsigned int *) malloc(sizeof(unsigned int) * params->ssl->nLevels);
        memcpy(cfg->deltasMax, params->ssl->deltasMax, sizeof(unsigned int) * params->ssl->nLevels);
        cfg->deltaReset = params->ssl->deltaReset;
        cfg->R = params->ssl->R;

        return cfg;

    }

    msg_pots_cfg * parameters2configs_msg_pots(const parameters * params) {

        msg_pots_cfg * cfg;

        cfg = msg_pots_cfg_construct();

        cfg->nPots = params->ssl->nPots;

        return cfg;

    }

    snk_pots_file_cfg * parameters2configs_snk_pots_file(const parameters * params) {

        snk_pots_file_cfg * cfg;

        cfg = snk_pots_file_cfg_construct();

        cfg->fileName = (char *) malloc(sizeof(char) * 1024);
        strcpy(cfg->fileName, "");

        return cfg;

    }

    mod_sst_cfg * parameters2configs_mod_sst(const parameters * params) {

        mod_sst_cfg * cfg;
        unsigned int iGaussian;

        cfg = mod_sst_cfg_construct();

        cfg->nPots = params->ssl->nPots;
        cfg->nTracks = params->sst->nTracks;
        cfg->mode = (char *) malloc(sizeof(char) * (strlen(params->sst->mode)+1));
        strcpy(cfg->mode, params->sst->mode);
        cfg->R = params->ssl->R;
        cfg->hopSize = params->general->hopSize;
        cfg->fS = params->general->fS;
        cfg->sigmaQ = params->sst->sigmaQ;
        cfg->nParticles = params->sst->nParticles;
        cfg->st_alpha = params->sst->st_alpha;
        cfg->st_beta = params->sst->st_beta;
        cfg->st_ratio = params->sst->st_ratio;
        cfg->ve_alpha = params->sst->ve_alpha;
        cfg->ve_beta = params->sst->ve_beta;
        cfg->ve_ratio = params->sst->ve_ratio;
        cfg->ac_alpha = params->sst->ac_alpha;
        cfg->ac_beta = params->sst->ac_beta;
        cfg->ac_ratio = params->sst->ac_ratio;
        cfg->Nmin = params->sst->Nmin;

        cfg->epsilon = params->sst->epsilon;
        cfg->sigmaR_prob = params->sst->sigmaR_prob;
        cfg->sigmaR_active = params->sst->sigmaR_active;

        cfg->active_gmm = gaussians_1d_construct_null(params->sst->active_G);

        for (iGaussian = 0; iGaussian < params->sst->active_G; iGaussian++) {

            cfg->active_gmm->array[iGaussian] = gaussian_1d_construct_weightmusigma(params->sst->active_weight[iGaussian],
                                                                                    params->sst->active_mu[iGaussian],
                                                                                    params->sst->active_sigma[iGaussian]);

        }

        cfg->inactive_gmm = gaussians_1d_construct_null(params->sst->inactive_G);

        for (iGaussian = 0; iGaussian < params->sst->inactive_G; iGaussian++) {

            cfg->inactive_gmm->array[iGaussian] = gaussian_1d_construct_weightmusigma(params->sst->inactive_weight[iGaussian],
                                                                                      params->sst->inactive_mu[iGaussian],
                                                                                      params->sst->inactive_sigma[iGaussian]);

        }        
        
        cfg->Pfalse = params->sst->Pfalse;
        cfg->Pnew = params->sst->Pnew;
        cfg->Ptrack = params->sst->Ptrack;
        cfg->shape = (char *) malloc(sizeof(char) * (strlen(params->ssl->shape)+1));
        strcpy(cfg->shape,params->ssl->shape);
        cfg->theta_new = params->sst->theta_new;
        cfg->N_prob = params->sst->N_prob;
        cfg->theta_prob = params->sst->theta_prob;
        cfg->N_inactive = (unsigned int *) malloc(sizeof(unsigned int) * params->sst->nTracks);
        memcpy(cfg->N_inactive, params->sst->N_inactive, sizeof(unsigned int) * params->sst->nTracks);
        cfg->theta_inactive = params->sst->theta_inactive;

        return cfg;

    }

    msg_tracks_cfg * parameters2configs_msg_tracks(const parameters * params) {

        msg_tracks_cfg * cfg;

        cfg = msg_tracks_cfg_construct();

        cfg->nTracks = params->sst->nTracks;

        return cfg;

    }

    snk_tracks_file_cfg * parameters2configs_snk_tracks_file(const parameters * params) {

        snk_tracks_file_cfg * cfg;

        cfg = snk_tracks_file_cfg_construct();

        cfg->fileName = (char *) malloc(sizeof(char) * 1024);
        strcpy(cfg->fileName, "");

        return cfg;

    }