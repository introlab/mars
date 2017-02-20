#ifndef __MARS_SOURCE_WAV_FILE
#define __MARS_SOURCE_WAV_FILE

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    #include "../message/msg_hops.h"
    #include "../utils/pcm.h"

    typedef struct src_wav_file_obj {

        unsigned long long timeStamp;

        unsigned int hopSize;
        unsigned int nMics;
        unsigned int nBits;
        char * fileName;
        FILE * fp;

    } src_wav_file_obj;

    typedef struct src_wav_file_cfg {

        unsigned int hopSize;
        unsigned int nMics;
        unsigned int nBits;
        char * fileName;

    } src_wav_file_cfg;

    src_wav_file_obj * src_wav_file_construct(const src_wav_file_cfg * cfg);

    void src_wav_file_destroy(src_wav_file_obj * obj);

    int src_wav_file_process(src_wav_file_obj * obj, msg_hops_obj * msg_hops);

    src_wav_file_cfg * src_wav_file_cfg_construct(void);

    void src_wav_file_cfg_destroy(src_wav_file_cfg * cfg);

#endif