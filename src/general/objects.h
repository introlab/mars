#ifndef __MARS_GENERAL_OBJECTS
#define __MARS_GENERAL_OBJECTS

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
    
    typedef struct objects {

        src_raw_file_obj * src_raw_file;
        msg_hops_obj * msg_hops;
        mod_stft_obj * mod_stft;
        msg_spectra_obj * msg_spectra;
        mod_ssl_obj * mod_ssl;
        msg_pots_obj * msg_pots;
        snk_pots_obj * snk_pots;
        mod_sst_obj * mod_sst;
        msg_tracks_obj * msg_tracks;
        snk_tracks_obj * snk_tracks;

    } objects;

    objects * objects_construct_null(void);

    void objects_destroy(objects * objs);

#endif