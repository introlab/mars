#ifndef __MARS_SOURCE_RAW_FILE
#define __MARS_SOURCE_RAW_FILE

    #include "../message/msg_hops.h"
    #include "../utils/pcm.h"

    #include <stdio.h>
    #include <math.h>
    #include <limits.h>
    #include <string.h>

    typedef struct src_raw_file_obj {

        unsigned long long timeStamp;

        unsigned int hopSize;
        unsigned int nMics;
        unsigned int nBits;
        char * fileName;
        FILE * fp;

    } src_raw_file_obj;

    typedef struct src_raw_file_cfg {

        unsigned int hopSize;
        unsigned int nMics;
        unsigned int nBits;
        char * fileName;

    } src_raw_file_cfg;

    src_raw_file_obj * src_raw_file_construct(const src_raw_file_cfg * cfg);

    void src_raw_file_destroy(src_raw_file_obj * obj);

    int src_raw_file_process(src_raw_file_obj * obj, msg_hops_obj * msg_hops);

    src_raw_file_cfg * src_raw_file_cfg_construct(void);

    void src_raw_file_cfg_destroy(src_raw_file_cfg * cfg);

#endif