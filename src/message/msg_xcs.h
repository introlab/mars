#ifndef __MARS_MESSAGE_XCS
#define __MARS_MESSAGE_XCS

    #include <stdlib.h>

    #include "../signal/xcorr.h"

    typedef struct msg_xcs_obj {

        unsigned long long timeStamp;
        xcorrs_obj * xcorrs;

    } msg_xcs_obj;

    typedef struct msg_xcs_cfg {

        unsigned int frameSize;
        unsigned int nMics;

    } msg_xcs_cfg;

    msg_xcs_obj * msg_xcs_construct(const msg_xcs_cfg * cfg);

    void msg_xcs_destroy(msg_xcs_obj * obj);

    msg_xcs_cfg * msg_xcs_cfg_construct(void);

    void msg_xcs_cfg_destroy(msg_xcs_cfg * cfg);

#endif