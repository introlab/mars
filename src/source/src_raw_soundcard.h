#ifndef __MARS_SOURCE_RAW_SOUNDCARD
#define __MARS_SOURCE_RAW_SOUNDCARD

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <alsa/asoundlib.h>

    #include "../message/msg_hops.h"

    typedef struct src_raw_soundcard_obj {

        unsigned long long timeStamp;   

        unsigned int hopSize;           
        unsigned int nMics;             
        unsigned int nBits;    
        unsigned int fS;
        char * cardName;  

        snd_pcm_t * captureHandle;       

    } src_raw_soundcard_obj;

    typedef struct src_raw_soundcard_cfg {

        unsigned int hopSize;
        unsigned int nMics;
        unsigned int nBits;
        unsigned int fS;
        char * cardName;

    } src_raw_soundcard_cfg;

    src_raw_soundcard_obj * src_raw_soundcard_construct(const src_raw_soundcard_cfg * cfg);

    void src_raw_soundcard_destroy(src_raw_soundcard_obj * obj);

    int src_raw_soundcard_process(src_raw_soundcard_obj * obj, msg_hops_obj * msg_hops);

    src_raw_soundcard_cfg * src_raw_soundcard_cfg_construct(void);

    void src_raw_soundcard_cfg_destroy(src_raw_soundcard_cfg * cfg);

#endif