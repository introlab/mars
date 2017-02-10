#ifndef __MARS_GENERAL_PARAMETERS2CONFIGS
#define __MARS_GENERAL_PARAMETERS2CONFIGS

    #include "parameters.h"
    #include "configs.h"   

    void parameters2configs(configs * cfgs, const parameters * params);

    src_raw_file_cfg * parameters2configs_src_raw_file(const parameters * params);

    msg_hops_cfg * parameters2configs_msg_hops(const parameters * params);

    snk_raw_file_cfg * parameters2configs_snk_raw_file(const parameters * params);

    mod_stft_cfg * parameters2configs_mod_stft(const parameters * params);

    msg_spectra_cfg * parameters2configs_msg_spectra(const parameters * params);

    mod_ssl_cfg * parameters2configs_mod_ssl(const parameters * params);

    msg_pots_cfg * parameters2configs_msg_pots(const parameters * params);

    snk_pots_file_cfg * parameters2configs_snk_pots_file(const parameters * params);

    mod_sst_cfg * parameters2configs_mod_sst(const parameters * params);

    msg_tracks_cfg * parameters2configs_msg_tracks(const parameters * params);

    snk_tracks_file_cfg * parameters2configs_snk_tracks_file(const parameters * params);

#endif