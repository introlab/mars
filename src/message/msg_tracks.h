#ifndef __MARS_MESSAGE_TRACKS
#define __MARS_MESSAGE_TRACKS

    #include <stdlib.h>

    #include "../signal/track.h"

    typedef struct msg_tracks_obj {

        unsigned long long timeStamp;
        tracks_obj * tracks;

    } msg_tracks_obj;

    typedef struct msg_tracks_cfg {

        unsigned int nTracks;

    } msg_tracks_cfg;

    msg_tracks_obj * msg_tracks_construct(const msg_tracks_cfg * cfg);

    void msg_tracks_destroy(msg_tracks_obj * obj);

    msg_tracks_cfg * msg_tracks_cfg_construct(void);

    void msg_tracks_cfg_destroy(msg_tracks_cfg * cfg);

#endif