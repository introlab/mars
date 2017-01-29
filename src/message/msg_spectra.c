    
    #include "msg_spectra.h"

    msg_spectra_obj * msg_spectra_construct(const msg_spectra_cfg * cfg) {

        msg_spectra_obj * obj;

        obj = (msg_spectra_obj *) malloc(sizeof(msg_spectra_obj));

        obj->timeStamp = 0;
        obj->freqs = freqs_construct_zero(cfg->nMics, cfg->frameSize/2+1);

        return obj;

    }

    void msg_spectra_destroy(msg_spectra_obj * obj) {

        freqs_destroy(obj->freqs);
        free((void *) obj);

    }

    msg_spectra_cfg * msg_spectra_cfg_construct(void) {

        msg_spectra_cfg * cfg;

        cfg = (msg_spectra_cfg *) malloc(sizeof(msg_spectra_cfg));

        cfg->frameSize = 0;
        cfg->nMics = 0;

        return cfg;

    }

    void msg_spectra_cfg_destroy(msg_spectra_cfg * cfg) {

        free((void *) cfg);

    }