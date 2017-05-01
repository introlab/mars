
    #include "parameters2configs.h"

    void parameters2configs(configs * cfgs, const parameters * params) {

        cfgs->src_raw_file = parameters2configs_src_raw_file(params);
        cfgs->src_raw_soundcard = parameters2configs_src_raw_soundcard(params);
        cfgs->src_wav_file = parameters2configs_src_wav_file(params);
        cfgs->msg_hops_raw_in = parameters2configs_msg_hops_raw_in(params);
        cfgs->mod_resample_raw_in = parameters2configs_mod_resample_raw_in(params);
        cfgs->msg_hops_raw = parameters2configs_msg_hops_raw(params);
        cfgs->mod_resample_raw_out = parameters2configs_mod_resample_raw_out(params);
        cfgs->msg_hops_raw_out = parameters2configs_msg_hops_raw_out(params);
        cfgs->snk_raw_file = parameters2configs_snk_raw_file(params);
        cfgs->mod_stft = parameters2configs_mod_stft(params);
        cfgs->msg_spectra = parameters2configs_msg_spectra(params);
        cfgs->snk_spectra_file = parameters2configs_snk_spectra_file(params);
        cfgs->mod_gcc = parameters2configs_mod_gcc(params);
        cfgs->msg_xcs = parameters2configs_msg_xcs(params);
        cfgs->snk_xcs_file = parameters2configs_snk_xcs_file(params);
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

        cfg->hopSize = params->raw->hopSizeIn;
        cfg->nMics = params->general->mics->nMics;
        cfg->nBits = params->raw->nBitsIn;

        return cfg;

    }

    src_raw_soundcard_cfg * parameters2configs_src_raw_soundcard(const parameters * params) {

        src_raw_soundcard_cfg * cfg;

        cfg = src_raw_soundcard_cfg_construct();

        cfg->hopSize = params->raw->hopSizeIn;
        cfg->nMics = params->general->mics->nMics;
        cfg->nBits = params->raw->nBitsIn;
        cfg->fS = params->general->fS * (params->raw->hopSizeIn/params->general->hopSize);

        return cfg;

    }

    src_wav_file_cfg * parameters2configs_src_wav_file(const parameters * params) {

        src_wav_file_cfg * cfg;

        cfg = src_wav_file_cfg_construct();

        cfg->hopSize = params->raw->hopSizeIn;
        cfg->nMics = params->general->mics->nMics;
        cfg->nBits = params->raw->nBitsIn;

        return cfg;

    }

    msg_hops_cfg * parameters2configs_msg_hops_raw_in(const parameters * params) {

        msg_hops_cfg * cfg;

        cfg = msg_hops_cfg_construct();

        cfg->hopSize = params->raw->hopSizeIn;
        cfg->nMics = params->general->mics->nMics;

        return cfg;

    }

    mod_resample_cfg * parameters2configs_mod_resample_raw_in(const parameters * params) {

        mod_resample_cfg * cfg;

        cfg = mod_resample_cfg_construct();

        cfg->nHops = params->general->mics->nMics;
        cfg->hopSizeIn = params->raw->hopSizeIn;
        cfg->hopSizeOut = params->general->hopSize;

        return cfg;

    }

    msg_hops_cfg * parameters2configs_msg_hops_raw(const parameters * params) {

        msg_hops_cfg * cfg;

        cfg = msg_hops_cfg_construct();

        cfg->hopSize = params->general->hopSize;
        cfg->nMics = params->general->mics->nMics;

        return cfg;        

    }

    msg_hops_cfg * parameters2configs_msg_hops_raw_out(const parameters * params) {

        msg_hops_cfg * cfg;

        cfg = msg_hops_cfg_construct();

        cfg->hopSize = params->raw->hopSizeOut;
        cfg->nMics = params->general->mics->nMics;

        return cfg;

    }

    mod_resample_cfg * parameters2configs_mod_resample_raw_out(const parameters * params) {

        mod_resample_cfg * cfg;

        cfg = mod_resample_cfg_construct();

        cfg->nHops = params->general->mics->nMics;
        cfg->hopSizeIn = params->general->hopSize;
        cfg->hopSizeOut = params->raw->hopSizeOut;

        return cfg;
        
    }    

    snk_raw_file_cfg * parameters2configs_snk_raw_file(const parameters * params) {

        snk_raw_file_cfg * cfg;

        cfg = snk_raw_file_cfg_construct();

        cfg->hopSize = params->raw->hopSizeOut;
        cfg->nMics = params->general->mics->nMics;
        cfg->nBits = params->raw->nBitsOut;
        cfg->fileName = (char *) malloc(sizeof(char) * 1024);
        strcpy(cfg->fileName, "");

        return cfg;

    }

    mod_stft_cfg * parameters2configs_mod_stft(const parameters * params) {

        mod_stft_cfg * cfg;

        cfg = mod_stft_cfg_construct();

        cfg->hopSize = params->general->hopSize;
        cfg->frameSize = params->general->frameSize;
        cfg->nMics = params->general->mics->nMics;

        return cfg;

    }

    msg_spectra_cfg * parameters2configs_msg_spectra(const parameters * params) {

        msg_spectra_cfg * cfg;

        cfg = msg_spectra_cfg_construct();

        cfg->frameSize = params->general->frameSize;
        cfg->nMics = params->general->mics->nMics;

        return cfg;

    }

    snk_spectra_file_cfg * parameters2configs_snk_spectra_file(const parameters * params) {

        snk_spectra_file_cfg * cfg;

        cfg = snk_spectra_file_cfg_construct();

        cfg->fileName = (char *) malloc(sizeof(char) * 1024);
        strcpy(cfg->fileName, "");

        return cfg;

    }

    mod_gcc_cfg * parameters2configs_mod_gcc(const parameters * params) {

        mod_gcc_cfg * cfg;

        cfg = mod_gcc_cfg_construct();

        cfg->nMics = params->general->mics->nMics;
        cfg->frameSize = params->general->frameSize;
        cfg->epsilon = params->gcc->epsilon;
        cfg->alpha = params->gcc->alpha;

        return cfg;

    }

    msg_xcs_cfg * parameters2configs_msg_xcs(const parameters * params) {

        msg_xcs_cfg * cfg;

        cfg = msg_xcs_cfg_construct();

        cfg->nMics = params->general->mics->nMics;
        cfg->frameSize = params->general->frameSize;

        return cfg;

    }

    snk_xcs_file_cfg * parameters2configs_snk_xcs_file(const parameters * params) {

        snk_xcs_file_cfg * cfg;

        cfg = snk_xcs_file_cfg_construct();

        cfg->fileName = (char *) malloc(sizeof(char) * 1024);
        strcpy(cfg->fileName, "");        

        return cfg;

    }

    mod_ssl_cfg * parameters2configs_mod_ssl(const parameters * params) {

        mod_ssl_cfg * cfg;

        cfg = mod_ssl_cfg_construct();

        cfg->mics = mics_construct_zero(params->general->mics->nMics);
        memcpy(cfg->mics->mu, params->general->mics->mu, sizeof(float) * 3 * params->general->mics->nMics);
        memcpy(cfg->mics->sigma, params->general->mics->sigma, sizeof(float) * 9 * params->general->mics->nMics);

        cfg->nPots = params->ssl->nPots;
        cfg->fS = params->general->fS;
        
        cfg->soundspeed = soundspeed_construct_zero();
        cfg->soundspeed->mu = params->general->soundspeed->mu;
        cfg->soundspeed->sigma = params->general->soundspeed->sigma;

        cfg->frameSize = params->general->frameSize;
        cfg->nMatches = params->ssl->nMatches;
        cfg->probMin = params->ssl->probMin;
        cfg->nRefinedLevels = params->ssl->nRefinedLevels;
        cfg->shape = (char *) malloc(sizeof(char) * (strlen(params->ssl->shape)+1));
        strcpy(cfg->shape,params->ssl->shape);
        cfg->nLevels = params->ssl->nLevels;
        cfg->levels = (unsigned int *) malloc(sizeof(unsigned int) * params->ssl->nLevels);
        memcpy(cfg->levels, params->ssl->levels, sizeof(unsigned int) * params->ssl->nLevels);
        cfg->deltas = (signed int *) malloc(sizeof(signed int) * params->ssl->nLevels);
        memcpy(cfg->deltas, params->ssl->deltas, sizeof(signed int) * params->ssl->nLevels);
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