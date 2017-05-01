#ifndef __MARS_GENERAL_CONFIGS2OBJECTS
#define __MARS_GENERAL_CONFIGS2OBJECTS

    #include "../source/src_raw_file.h"
    #include "../source/src_raw_soundcard.h"
    #include "../source/src_wav_file.h"
    #include "../message/msg_hops.h"
    #include "../module/mod_resample.h"
    #include "../sink/snk_raw_file.h"
    #include "../module/mod_stft.h"
    #include "../message/msg_spectra.h"
    #include "../module/mod_gcc.h"
    #include "../message/msg_xcs.h"
    #include "../module/mod_ssl.h"
    #include "../message/msg_pots.h"
    #include "../sink/snk_pots_file.h"
    #include "../module/mod_sst.h"
    #include "../message/msg_tracks.h"
    #include "../sink/snk_tracks_file.h"

    #include "objects.h"
    #include "configs.h"
    #include "arguments.h"

    void configs2objects(objects * objs, const configs * cfgs, const arguments * args);

#endif