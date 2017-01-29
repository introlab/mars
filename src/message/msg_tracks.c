
    #include "msg_tracks.h"

    msg_tracks_obj * msg_tracks_construct(const msg_tracks_cfg * cfg) {

        msg_tracks_obj * obj;

        obj = (msg_tracks_obj *) malloc(sizeof(msg_tracks_obj));

        obj->timeStamp = 0;
        obj->tracks = tracks_construct_zero(cfg->nTracks);

        return obj;

    }

    void msg_tracks_destroy(msg_tracks_obj * obj) {

        tracks_destroy(obj->tracks);
        free((void *) obj);

    }

    msg_tracks_cfg * msg_tracks_cfg_construct(void) {

        msg_tracks_cfg * cfg;

        cfg = (msg_tracks_cfg *) malloc(sizeof(msg_tracks_cfg));

        cfg->nTracks = 0;

        return cfg;

    }

    void msg_tracks_cfg_destroy(msg_tracks_cfg * cfg) {

        free((void *) cfg);

    }