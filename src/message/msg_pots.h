#ifndef __MARS_MESSAGE_POTS
#define __MARS_MESSAGE_POTS

    #include <stdlib.h>
    #include "../signal/pot.h"

    typedef struct msg_pots_obj {

        unsigned long long timeStamp;
        pots_obj * pots;

    } msg_pots_obj;

    typedef struct msg_pots_cfg {

        unsigned int nPots;

    } msg_pots_cfg;

    msg_pots_obj * msg_pots_construct(const msg_pots_cfg * cfg);

    void msg_pots_destroy(msg_pots_obj * obj);

    msg_pots_cfg * msg_pots_cfg_construct(void);

    void msg_pots_cfg_destroy(msg_pots_cfg * cfg);

#endif