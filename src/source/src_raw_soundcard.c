    
    #include "src_raw_8soundusb.h"

    src_raw_8soundusb_obj * src_raw_8soundusb_construct(const src_raw_8soundusb_cfg * cfg) {

        src_raw_8soundusb_obj * obj;
        snd_pcm_hw_params_t * hw_params;
        snd_pcm_format_t format;
        int err;

        obj = (src_raw_8soundusb_obj *) malloc(sizeof(src_raw_8soundusb_obj));

        if (cfg->nMics != 8) {
            printf("Number of channels should be set to 8 with this sound card.\n");
            exit(EXIT_FAILURE);
        }
        if (cfg->nBits != 16) {
            printf("Number of bits should be set to 16 with this sound card.\n");
            exit(EXIT_FAILURE);
        }

        obj->hopSize = cfg->hopSize;
        obj->nMics = cfg->nMics;
        obj->nBits = cfg->nBits;
        obj->fS = cfg->fS;

        format = SND_PCM_FORMAT_S32_LE;

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