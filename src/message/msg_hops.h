#ifndef __MARS_MESSAGE_HOPS
#define __MARS_MESSAGE_HOPS

    #include <stdlib.h>
    #include "../signal/hop.h"

    typedef struct msg_hops_obj {

        unsigned long long timeStamp;
        hops_obj * hops;

    } msg_hops_obj;

    typedef struct msg_hops_cfg {

        unsigned int hopSize;
        unsigned int nMics;

    } msg_hops_cfg;

    msg_hops_obj * msg_hops_construct(const msg_hops_cfg * cfg);

    void msg_hops_destroy(msg_hops_obj * obj);

    msg_hops_cfg * msg_hops_cfg_construct(void);

    void msg_hops_cfg_destroy(msg_hops_cfg * cfg);

#endif