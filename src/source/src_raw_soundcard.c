    
    #include "src_raw_soundcard.h"

    src_raw_soundcard_obj * src_raw_soundcard_construct(const src_raw_soundcard_cfg * cfg) {

        src_raw_soundcard_obj * obj;
        snd_pcm_hw_params_t * hw_params;
        snd_pcm_format_t format;
        int err;

        obj = (src_raw_soundcard_obj *) malloc(sizeof(src_raw_soundcard_obj));

        obj->hopSize = cfg->hopSize;
        obj->nMics = cfg->nMics;
        obj->nBits = cfg->nBits;
        obj->fS = cfg->fS;

        if (!((cfg->nBits == 8) | (cfg->nBits == 16) | (cfg->nBits == 32))) {
            printf("Invalid number of bits.\n");
            exit(EXIT_FAILURE);         
        }

        switch(cfg->nBits) {

            case 8:

                format = SND_PCM_FORMAT_S8_LE;

            break;

            case 16:

                format = SND_PCM_FORMAT_S16_LE;

            break;

            case 32:

                format = SND_PCM_FORMAT_S32_LE;

            break;

        }

        

        obj->cardName = (char *) malloc(sizeof(char) * (strlen(cfg->cardName) + 1));
        strcpy(obj->cardName, cfg->cardName);

        // Open sound card
        
        if ((err = snd_pcm_open(&(obj->captureHandle), obj->cardName, SND_PCM_STREAM_CAPTURE, SND_PCM_ASYNC)) < 0) {
            printf("Cannot open audio device %s: %s\n",obj->cardName, snd_strerror(err));
            exit(EXIT_FAILURE);
        }

        if ((err = snd_pcm_hw_params_malloc(&hw_params)) < 0) {
            printf("Cannot allocate hardware parameter structure: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }

        if ((err = snd_pcm_hw_params_any(obj->captureHandle, hw_params)) < 0) {
            printf("Cannot initialize hardware parameter structure: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }

        if ((err = snd_pcm_hw_params_set_access(obj->captureHandle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
            printf("Cannot set access type: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }

        if ((err = snd_pcm_hw_params_set_format(obj->captureHandle, hw_params, format)) < 0) {
            printf("Cannot set sample format: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }

        if ((err = snd_pcm_hw_params_set_rate(obj->captureHandle, hw_params, obj->fS, 0)) < 0) {
            printf("Cannot set sample rate: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }

        if ((err = snd_pcm_hw_params_set_channels(obj->captureHandle, hw_params, obj->nMics)) < 0) {
            printf("Cannot set channel count: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }

        if ((err = snd_pcm_hw_params(obj->captureHandle, hw_params)) < 0) {
            printf("Cannot set parameters: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }

        snd_pcm_hw_params_free(hw_params);

        if ((err = snd_pcm_prepare(obj->captureHandle)) < 0) {
            printf("Cannot prepare audio interface for use: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }

        return obj;

    }

    void src_raw_8soundusb_destroy(src_raw_8soundusb_obj * obj) {

        free((void *) obj->cardName);
        free((void *) obj);

    }

    int src_raw_8soundusb_process(src_raw_8soundusb_obj * obj, msg_hops_obj * msg_hops) {

    }

    src_raw_8soundusb_cfg * src_raw_8soundusb_cfg_construct(void) {

        src_raw_8soundusb_cfg * cfg;

        cfg = (src_raw_8soundusb_cfg *) malloc(sizeof(src_raw_8soundusb_cfg));

        cfg->hopSize = 0;
        cfg->nMics = 0;
        cfg->nBits = 0;
        cfg->fS = 0;
        cfg->cardName = (char *) NULL;

        return cfg;

    }

    void src_raw_8soundusb_cfg_destroy(src_raw_8soundusb_cfg * cfg) {

        if (cfg->cardName != NULL) {
            free((void *) cfg->cardName);
        }

        free((void *) cfg);

    }