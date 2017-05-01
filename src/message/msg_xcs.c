    
    #include "msg_xcs.h"

    msg_xcs_obj * msg_xcs_construct(const msg_xcs_cfg * cfg) {

        msg_xcs_obj * obj;
        unsigned int nPairs;

        obj = (msg_xcs_obj *) malloc(sizeof(msg_xcs_obj));

        nPairs = cfg->nMics*(cfg->nMics-1)/2;

        obj->timeStamp = 0;
        obj->xcorrs = xcorrs_construct_zero(nPairs, cfg->frameSize);

        return obj;

    }

    void msg_xcs_destroy(msg_xcs_obj * obj) {

        xcorrs_destroy(obj->xcorrs);
        free((void *) obj);

    }

    msg_xcs_cfg * msg_xcs_cfg_construct(void) {

        msg_xcs_cfg * cfg;

        cfg = (msg_xcs_cfg *) malloc(sizeof(msg_xcs_cfg));

        cfg->frameSize = 0;
        cfg->nMics = 0;

        return cfg;

    }

    void msg_xcs_cfg_destroy(msg_xcs_cfg * cfg) {

        free((void *) cfg);

    }