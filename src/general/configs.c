    
    #include "configs.h"

    configs * configs_construct_null(void) {

        configs * cfgs;

        cfgs = (configs *) malloc(sizeof(configs));

        cfgs->src_raw_file = (src_raw_file_cfg *) NULL;
        cfgs->msg_hops = (msg_hops_cfg *) NULL;
        cfgs->mod_stft = (mod_stft_cfg *) NULL;
        cfgs->msg_spectra = (msg_spectra_cfg *) NULL;
        cfgs->mod_ssl = (mod_ssl_cfg *) NULL;
        cfgs->msg_pots = (msg_pots_cfg *) NULL;
        cfgs->snk_pots_file = (snk_pots_file_cfg *) NULL;
        cfgs->mod_sst = (mod_sst_cfg *) NULL;
        cfgs->msg_tracks = (msg_tracks_cfg *) NULL;
        cfgs->snk_tracks_file = (snk_tracks_file_cfg *) NULL;

        return cfgs;

    }

    void configs_destroy(configs * cfgs) {

        if (cfgs->src_raw_file != NULL) {
            src_raw_file_cfg_destroy(cfgs->src_raw_file);
        }
        if (cfgs->msg_hops != NULL) {
            msg_hops_cfg_destroy(cfgs->msg_hops);
        }
        if (cfgs->mod_stft != NULL) {
            mod_stft_cfg_destroy(cfgs->mod_stft);
        }
        if (cfgs->msg_spectra != NULL) {
            msg_spectra_cfg_destroy(cfgs->msg_spectra);
        }
        if (cfgs->mod_ssl != NULL) {
            mod_ssl_cfg_destroy(cfgs->mod_ssl);
        }
        if (cfgs->msg_pots != NULL) {
            msg_pots_cfg_destroy(cfgs->msg_pots);
        }
        if (cfgs->snk_pots_file != NULL) {
            snk_pots_file_cfg_destroy(cfgs->snk_pots_file);
        }
        if (cfgs->mod_sst != NULL) {
            mod_sst_cfg_destroy(cfgs->mod_sst);
        }
        if (cfgs->msg_tracks != NULL) {
            msg_tracks_cfg_destroy(cfgs->msg_tracks);
        }
        if (cfgs->snk_tracks_file != NULL) {
            snk_tracks_file_cfg_destroy(cfgs->snk_tracks_file);
        }

        free((void *) cfgs);

    }