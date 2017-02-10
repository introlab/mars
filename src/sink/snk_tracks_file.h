#ifndef __MARS_SINK_TRACKS_FILE
#define __MARS_SINK_TRACKS_FILE

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <math.h>
    #include <limits.h>

    #include "../message/msg_tracks.h"

    typedef struct snk_tracks_file_obj {

        char * fileName;
        FILE * fp;
        char format;

    } snk_tracks_file_obj;    

    typedef struct snk_tracks_file_cfg {

        char * fileName;
        char format;

    } snk_tracks_file_cfg;

    snk_tracks_file_obj * snk_tracks_file_construct(const snk_tracks_file_cfg * cfg);

    void snk_tracks_file_destroy(snk_tracks_file_obj * obj);

    void snk_tracks_file_process(snk_tracks_file_obj * obj, msg_tracks_obj * msg_tracks);

    void snk_tracks_file_process_xml(snk_tracks_file_obj * obj, msg_tracks_obj * msg_tracks);

    void snk_tracks_file_process_bin(snk_tracks_file_obj * obj, msg_tracks_obj * msg_tracks);

    snk_tracks_file_cfg * snk_tracks_file_cfg_construct(void);

    void snk_tracks_file_cfg_destroy(snk_tracks_file_cfg * cfg);

#endif