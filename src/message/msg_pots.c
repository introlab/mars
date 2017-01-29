    
    #include "msg_pots.h"

    msg_pots_obj * msg_pots_construct(const msg_pots_cfg * cfg) {

        msg_pots_obj * obj;

        obj = (msg_pots_obj *) malloc(sizeof(msg_pots_obj));

        obj->timeStamp = 0;
        obj->pots = pots_construct_zero(cfg->nPots);

        return obj;

    }

    void msg_pots_destroy(msg_pots_obj * obj) {

        pots_destroy(obj->pots);
        free((void *) obj);

    }

    msg_pots_cfg * msg_pots_cfg_construct(void) {

        msg_pots_cfg * cfg;

        cfg = (msg_pots_cfg *) malloc(sizeof(msg_pots_cfg));

        cfg->nPots = 0;

        return cfg;

    }

    void msg_pots_cfg_destroy(msg_pots_cfg * cfg) {

        free((void *) cfg);

    }