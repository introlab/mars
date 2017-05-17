#ifndef __MARS_SINK_RAW_FILE
#define __MARS_SINK_RAW_FILE

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    #include "../message/msg_hops.h"
    #include "../utils/pcm.h"

    typedef struct snk_raw_file_obj {
    
        unsigned long long timeStamp;

        unsigned int hopSize;
        unsigned int nChannels;
        unsigned int nBits;
        char * fileName;
        FILE * fp;

    } snk_raw_file_obj;

    typedef struct snk_raw_file_cfg {

        unsigned int hopSize;
        unsigned int nChannels;
        unsigned int nBits;
        char * fileName;

    } snk_raw_file_cfg;

    snk_raw_file_obj * snk_raw_file_construct(const snk_raw_file_cfg * cfg);

    void snk_raw_file_destroy(const snk_raw_file_obj * obj);

    int snk_raw_file_process(snk_raw_file_obj * obj, msg_hops_obj * msg_hops);

    snk_raw_file_cfg * snk_raw_file_cfg_construct(void);

    void snk_raw_file_cfg_destroy(snk_raw_file_cfg * cfg);

#endif