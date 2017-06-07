    
    #include "src_raw_soundcard.h"

    src_raw_soundcard_obj * src_raw_soundcard_construct(const src_raw_soundcard_cfg * cfg) {

        src_raw_soundcard_obj * obj;
        snd_pcm_hw_params_t * hw_params;
        snd_pcm_format_t format;
        int err;

        obj = (src_raw_soundcard_obj *) malloc(sizeof(src_raw_soundcard_obj));

        obj->hopSize = cfg->hopSize;
        obj->nChannels = cfg->nChannels;
        obj->nBits = cfg->nBits;
        obj->fS = cfg->fS;
		obj->timeStamp = 0;

        if (!((cfg->nBits == 16) | (cfg->nBits == 32))) {
            printf("Invalid number of bits.\n");
            exit(EXIT_FAILURE);         
        }

        switch(cfg->nBits) {

            case 16:

                format = SND_PCM_FORMAT_S16_LE;

                obj->nBytes = 2;
                obj->buffer = (void *) malloc(sizeof(char) * obj->nBytes * obj->nChannels * obj->hopSize);

            break;

            case 32:

                format = SND_PCM_FORMAT_S32_LE;

                obj->nBytes = 4;
                obj->buffer = (void *) malloc(sizeof(char) * obj->nBytes * obj->nChannels * obj->hopSize);

            break;

        }

        obj->cardName = (char *) malloc(sizeof(char) * (strlen(cfg->cardName) + 1));
        strcpy(obj->cardName, cfg->cardName);

        // Open sound card
        
        if ((err = snd_pcm_open(&(obj->captureHandle), obj->cardName, SND_PCM_STREAM_CAPTURE, 0)) < 0) {
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

        if ((err = snd_pcm_hw_params_set_channels(obj->captureHandle, hw_params, obj->nChannels)) < 0) {
            printf("Cannot set channel count: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }

		// Params tests period, periods and buffer size.
		
		long unsigned int period_size = obj->hopSize *10;

		if ((err = snd_pcm_hw_params_set_period_size_near (obj->captureHandle, hw_params, &period_size, 0)) < 0) { // In frames!!
			printf ("cannot set period size (%s)\n",snd_strerror (err));
			exit(EXIT_FAILURE);
		}

		printf("Period size = %ld\n",period_size);

		long unsigned int nb_periods = 10;
		long unsigned int buffer_size = period_size * nb_periods;

		if ((err = snd_pcm_hw_params_set_buffer_size_near (obj->captureHandle, hw_params, &buffer_size)) < 0) { // In frames
			printf ("cannot set buffer time (%s)\n",snd_strerror (err));
			exit(EXIT_FAILURE);
		}

		printf("Buffer size = %ld\n",buffer_size);

        if ((err = snd_pcm_hw_params(obj->captureHandle, hw_params)) < 0) {
            printf("Cannot set parameters: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }

		// End of params tests		
		
		

        snd_pcm_hw_params_free(hw_params);

        if ((err = snd_pcm_prepare(obj->captureHandle)) < 0) {
            printf("Cannot prepare audio interface for use: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }

        return obj;

    }

    void src_raw_soundcard_destroy(src_raw_soundcard_obj * obj) {

        snd_pcm_close(obj->captureHandle);

        free((void *) obj->buffer);
        free((void *) obj->cardName);
        free((void *) obj);

    }

    int src_raw_soundcard_process(src_raw_soundcard_obj * obj, msg_hops_obj * msg_hops) {

        int err;
        unsigned int iSample;
        unsigned int iChannel;
        unsigned int iByte;
        unsigned int sampleShort;
        unsigned long sampleLong;
        float sampleFloat;

        if ((err = snd_pcm_readi(obj->captureHandle, obj->buffer, obj->hopSize)) != obj->hopSize) {
			
			perror("Read error!");
            return 1;

        }

        for (iSample = 0; iSample < obj->hopSize; iSample++) {

            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                iByte = (iSample * obj->nChannels + iChannel) * obj->nBytes;

                switch(obj->nBytes) {

                    case 2:

                        sampleShort = ((((unsigned short) (((char *) obj->buffer)[iByte+1])) << 8) & 0xFF00) + 
                                      ((((unsigned short) (((char *) obj->buffer)[iByte+0]))) & 0x00FF);

                        sampleFloat = pcm_signed16bits2normalized(sampleShort);


                    break;

                    case 4:

                        sampleLong = ((((unsigned long) (((char *) obj->buffer)[iByte+3])) << 24) & 0xFF000000) + 
                                     ((((unsigned long) (((char *) obj->buffer)[iByte+2])) << 16) & 0x00FF0000) + 
                                     ((((unsigned long) (((char *) obj->buffer)[iByte+1])) << 8) & 0x0000FF00) + 
                                     ((((unsigned long) (((char *) obj->buffer)[iByte+0]))) & 0x000000FF);            

                        sampleFloat = pcm_signed32bits2normalized(sampleLong);            

                    break;

                }

                msg_hops->hops->array[iChannel][iSample] = sampleFloat;

            }

        }

        obj->timeStamp++;

        msg_hops->timeStamp = obj->timeStamp;

        return 0;

    }

    src_raw_soundcard_cfg * src_raw_soundcard_cfg_construct(void) {

        src_raw_soundcard_cfg * cfg;

        cfg = (src_raw_soundcard_cfg *) malloc(sizeof(src_raw_soundcard_cfg));

        cfg->hopSize = 0;
        cfg->nChannels = 0;
        cfg->nBits = 0;
        cfg->fS = 0;
        cfg->cardName = (char *) NULL;

        return cfg;

    }

    void src_raw_soundcard_cfg_destroy(src_raw_soundcard_cfg * cfg) {

        if (cfg->cardName != NULL) {
            free((void *) cfg->cardName);
        }

        free((void *) cfg);

    }
