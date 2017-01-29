    #include "msg_hops.h"

    msg_hops_obj * msg_hops_construct(const msg_hops_cfg * cfg) {

        msg_hops_obj * obj;
        unsigned int iMic;

        obj = (msg_hops_obj *) malloc(sizeof(msg_hops_obj));

        obj->timeStamp = 0;

        obj->hops = hops_construct_zero(cfg->nMics, cfg->hopSize);

        return obj;

    }

    void msg_hops_destroy(msg_hops_obj * obj) {

        hops_destroy(obj->hops);

        free((void *) obj);

    }

    msg_hops_cfg * msg_hops_cfg_construct(void) {

        msg_hops_cfg * cfg;

        cfg = (msg_hops_cfg *) malloc(sizeof(msg_hops_cfg));

        cfg->hopSize = 0;
        cfg->nMics = 0;

        return cfg;

    }

    void msg_hops_cfg_destroy(msg_hops_cfg * cfg) {

        free((void *) cfg);

    }