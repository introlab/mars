
    #include "mod_stft.h"

    mod_stft_obj * mod_stft_construct(const mod_stft_cfg * cfg) {

        mod_stft_obj * obj;

        obj = (mod_stft_obj *) malloc(sizeof(mod_stft_obj));

        obj->hop2frame =  hop2frame_construct_zero(cfg->hopSize, cfg->frameSize);
        obj->frames = frames_construct_zero(cfg->nMics,cfg->frameSize);
        obj->frame2freq = frame2freq_construct_zero(cfg->frameSize, cfg->frameSize/2+1);

        return obj;

    }

    void mod_stft_destroy(mod_stft_obj * obj) {

        hop2frame_destroy(obj->hop2frame);
        frames_destroy(obj->frames);
        frame2freq_destroy(obj->frame2freq);

        free((void *) obj);

    }

    void mod_stft_process(mod_stft_obj * obj, const msg_hops_obj * msg_hops, msg_spectra_obj * msg_spectra) {

        hop2frame_process(obj->hop2frame, msg_hops->hops, obj->frames);
        frame2freq_process(obj->frame2freq, obj->frames, msg_spectra->freqs);

    }

    mod_stft_cfg * mod_stft_cfg_construct(void) {

        mod_stft_cfg * cfg;

        cfg = (mod_stft_cfg *) malloc(sizeof(mod_stft_cfg));

        cfg->nMics = 0;
        cfg->hopSize = 0;
        cfg->frameSize = 0;

        return cfg;

    }

    void mod_stft_cfg_destroy(mod_stft_cfg * cfg) {

        free((void *) cfg);

    }