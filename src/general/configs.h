#ifndef __MARS_GENERAL_CONFIGS
#define __MARS_GENERAL_CONFIGS

    #include <stdlib.h>

    #include "../source/src_raw_file.h"
    #include "../message/msg_hops.h"
    #include "../module/mod_stft.h"
    #include "../message/msg_spectra.h"
    #include "../module/mod_ssl.h"
    #include "../message/msg_pots.h"
    #include "../sink/snk_pots.h"
    #include "../module/mod_sst.h"
    #include "../message/msg_tracks.h"
    #include "../sink/snk_tracks.h"

    typedef struct configs {

        src_raw_file_cfg * src_raw_file;
        msg_hops_cfg * msg_hops;
        mod_stft_cfg * mod_stft;
        msg_spectra_cfg * msg_spectra;
        mod_ssl_cfg * mod_ssl;
        msg_pots_cfg * msg_pots;
        snk_pots_cfg * snk_pots;
        mod_sst_cfg * mod_sst;
        msg_tracks_cfg * msg_tracks;
        snk_tracks_cfg * snk_tracks;

    } configs;

    configs * configs_construct_null(void);

    void configs_destroy(configs * cfgs);

#endif