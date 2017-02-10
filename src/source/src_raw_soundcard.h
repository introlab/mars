#ifndef __MARS_SOURCE_RAW_8SOUNDUSB
#define __MARS_SOURCE_RAW_8SOUNDUSB

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <alsa/asoundlib.h>

    #include "../message/msg_hops.h"

    typedef struct src_raw_8soundusb_obj {

        unsigned long long timeStamp;   

        unsigned int hopSize;           
        unsigned int nMics;             
        unsigned int nBits;    
        unsigned int fS;
        char * cardName;  

        snd_pcm_t * captureHandle;       

    } src_raw_8soundusb_obj;

    typedef struct src_raw_8soundusb_cfg {

        unsigned int hopSize;
        unsigned int nMics;
        unsigned int nBits;
        unsigned int fS;
        char * cardName;

    } src_raw_8soundusb_cfg;

    src_raw_8soundusb_obj * src_raw_8soundusb_construct(const src_raw_8soundusb_cfg * cfg);

    void src_raw_8soundusb_destroy(src_raw_8soundusb_obj * obj);

    int src_raw_8soundusb_process(src_raw_8soundusb_obj * obj, msg_hops_obj * msg_hops);

    src_raw_8soundusb_cfg * src_raw_8soundusb_cfg_construct(void);

    void src_raw_8soundusb_cfg_destroy(src_raw_8soundusb_cfg * cfg);

#endif