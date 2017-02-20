#ifndef __MARS_MODULE_RESAMPLE
#define __MARS_MODULE_RESAMPLE

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    #include "../init/lowpass.h"
    #include "../signal/fir.h"
    #include "../signal/impulse.h"
    #include "../system/hop2hop.h"
    #include "../message/msg_hops.h"

    typedef struct mod_resample_obj {

        unsigned int nHops;
        unsigned int hopSizeIn;
        unsigned int hopSizeOut;

        hops_obj * hops;
        unsigned int factor;

        impulse_obj * impulse;
        firs_obj * firs;

        hop2hop_obj * hop2hop;

    } mod_resample_obj;

    typedef struct mod_resample_cfg {

        unsigned int nHops;
        unsigned int hopSizeIn;
        unsigned int hopSizeOut;

    } mod_resample_cfg;

    mod_resample_obj * mod_resample_construct(const mod_resample_cfg * cfg);

    void mod_resample_destroy(mod_resample_obj * obj);

    void mod_resample_process(mod_resample_obj * obj, const msg_hops_obj * msg_hopsIn, msg_hops_obj * msg_hopsOut);

    mod_resample_cfg * mod_resample_cfg_construct(void);

    void mod_resample_cfg_destroy(mod_resample_cfg * cfg);

#endif