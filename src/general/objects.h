#ifndef __MARS_GENERAL_OBJECTS
#define __MARS_GENERAL_OBJECTS

    #include <stdlib.h>

    #include "../source/src_raw_file.h"
    #include "../source/src_raw_soundcard.h"
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
    
    typedef struct objects {

        src_raw_file_obj * src_raw_file;
        src_raw_soundcard_obj * src_raw_soundcard;
        msg_hops_obj * msg_hops_raw_in;
        mod_resample_obj * mod_resample_raw_in;
        msg_hops_obj * msg_hops_raw;
        mod_resample_obj * mod_resample_raw_out;
        msg_hops_obj * msg_hops_raw_out;
        snk_raw_file_obj * snk_raw_file;
        mod_stft_obj * mod_stft;
        msg_spectra_obj * msg_spectra;
        mod_ssl_obj * mod_ssl;
        msg_pots_obj * msg_pots;
        snk_pots_file_obj * snk_pots_file;
        mod_sst_obj * mod_sst;
        msg_tracks_obj * msg_tracks;
        snk_tracks_file_obj * snk_tracks_file;

    } objects;

    objects * objects_construct_null(void);

    void objects_destroy(objects * objs);

#endif