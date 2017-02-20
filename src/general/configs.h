#ifndef __MARS_GENERAL_CONFIGS
#define __MARS_GENERAL_CONFIGS

    #include <stdlib.h>

    #include "../source/src_raw_file.h"
    #include "../source/src_raw_soundcard.h"
    #include "../source/src_wav_file.h"
    #include "../message/msg_hops.h"
    #include "../module/mod_resample.h"
    #include "../sink/snk_raw_file.h"
    #include "../module/mod_stft.h"
    #include "../message/msg_spectra.h"
    #include "../module/mod_ssl.h"
    #include "../message/msg_pots.h"
    #include "../sink/snk_pots_file.h"
    #include "../module/mod_sst.h"
    #include "../message/msg_tracks.h"
    #include "../sink/snk_tracks_file.h"

    typedef struct configs {

        src_raw_file_cfg * src_raw_file;
        src_raw_soundcard_cfg * src_raw_soundcard;
        src_wav_file_cfg * src_wav_file;
        msg_hops_cfg * msg_hops_raw_in;
        mod_resample_cfg * mod_resample_raw_in;
        msg_hops_cfg * msg_hops_raw;
        mod_resample_cfg * mod_resample_raw_out;
        msg_hops_cfg * msg_hops_raw_out;
        snk_raw_file_cfg * snk_raw_file;
        mod_stft_cfg * mod_stft;
        msg_spectra_cfg * msg_spectra;
        mod_ssl_cfg * mod_ssl;
        msg_pots_cfg * msg_pots;
        snk_pots_file_cfg * snk_pots_file;
        mod_sst_cfg * mod_sst;
        msg_tracks_cfg * msg_tracks;
        snk_tracks_file_cfg * snk_tracks_file;

    } configs;

    configs * configs_construct_null(void);

    void configs_destroy(configs * cfgs);

#endif