
    #include "mod_gcc.h"

    mod_gcc_obj * mod_gcc_construct(const mod_gcc_cfg * cfg) {

        mod_gcc_obj * obj;

        obj = (mod_gcc_obj *) malloc(sizeof(mod_gcc_obj));

        obj->nChannels = cfg->nChannels;
        obj->nPairs = cfg->nChannels * (cfg->nChannels - 1) / 2;
        obj->frameSize = cfg->frameSize;

        obj->phasors = freqs_construct_zero(obj->nChannels, obj->frameSize/2+1);
        obj->products = freqs_construct_zero(obj->nPairs, obj->frameSize/2+1);
        obj->smooths = freqs_construct_zero(obj->nPairs, obj->frameSize/2+1);

        obj->freq2freq = freq2freq_construct_zero(obj->frameSize/2+1, cfg->epsilon, cfg->alpha);
        obj->freq2xcorr = freq2xcorr_construct_zero(obj->frameSize, obj->frameSize/2+1);

        return obj;

    }

    void mod_gcc_destroy(mod_gcc_obj * obj) {

        freqs_destroy(obj->phasors);
        freqs_destroy(obj->products);
        freqs_destroy(obj->smooths);

        freq2freq_destroy(obj->freq2freq);
        freq2xcorr_destroy(obj->freq2xcorr);

        free((void *) obj);

    }

    void mod_gcc_process(mod_gcc_obj * obj, const msg_spectra_obj * msg_spectra, msg_xcs_obj * msg_xcs) {

        freq2freq_process_phasor(obj->freq2freq, msg_spectra->freqs, obj->phasors);
        freq2freq_process_product(obj->freq2freq, obj->phasors, obj->phasors, obj->products);
        freq2freq_process_smooth(obj->freq2freq, obj->products, obj->smooths);
        freq2xcorr_process(obj->freq2xcorr, obj->smooths, msg_xcs->xcorrs);

        msg_xcs->timeStamp = msg_spectra->timeStamp;

    }

    mod_gcc_cfg * mod_gcc_cfg_construct(void) {

        mod_gcc_cfg * cfg;

        cfg = (mod_gcc_cfg *) malloc(sizeof(mod_gcc_cfg));

        cfg->nChannels = 0;
        cfg->frameSize = 0;
        cfg->epsilon = 0.0f;
        cfg->alpha = 0.0f;

        return cfg;

    }

    void mod_gcc_cfg_destroy(mod_gcc_cfg * cfg) {

        free((void *) cfg);

    }