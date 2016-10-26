    
    #include "eightsnd2hop.h"

    eightsnd2hop_obj * eightsnd2hop_construct(const unsigned int hopSize, const unsigned int sampleRate, const char * sndCardName) {

        eightsnd2hop_obj * obj;
        int err;

        snd_pcm_hw_params_t * hw_params;
        snd_pcm_format_t format = SND_PCM_FORMAT_S32_LE;

        obj = (eightsnd2hop_obj *) malloc(sizeof(eightsnd2hop_obj));

        // Save parameters

        obj->hopSize = hopSize;
        obj->nMics = 8;
        obj->sampleRate = sampleRate;
        
        obj->sndCardName = (char *) malloc(sizeof(char) * (strlen(sndCardName)+1));
        strcpy(obj->sndCardName,sndCardName);

        obj->nMaxElements = 100;

        obj->bufferAvailable = (fifo_obj*) fifo_construct(obj->nMaxElements);
        obj->bufferFilled = (fifo_obj*) fifo_construct(obj->nMaxElements);

        // Open sound card

        if ((err = snd_pcm_open(&(obj->captureHandle), obj->sndCardName, SND_PCM_STREAM_CAPTURE, SND_PCM_ASYNC)) < 0) {
            printf("Cannot open audio device %s: %s\n",obj->sndCardName, snd_strerror(err));
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

        if ((err = snd_pcm_hw_params_set_rate(obj->captureHandle, hw_params, obj->sampleRate, 0)) < 0) {
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

        // Reset semaphore

        sem_init(&(obj->semaphore), 0, 0);

        // Set the state to not running

        obj->state = 0;

        return obj;

    }

    void eightsnd2hop_destroy(eightsnd2hop_obj * obj) {

        snd_pcm_close(obj->captureHandle);

        free((void *) obj->sndCardName);
        fifo_destroy(obj->bufferAvailable);
        fifo_destroy(obj->bufferFilled);
        free((void *) obj);

    }

    int eightsnd2hop_process(eightsnd2hop_obj * obj, vector_float ** hops) {

        char * frame;
        unsigned int iSample;
        unsigned int iMic;
        unsigned int iByte;
        unsigned long sampleLong;
        signed short sampleShort;
        float sampleFloat;

        // Start thread if not running already

        if (obj->state == 0) {

            pthread_create(&(obj->thread), NULL, eightsnd2hop_thread, (void *) obj);

            obj->state = 1;

        }

        // Wait for next frame

        sem_wait(&(obj->semaphore));

        frame = (char *) fifo_pop(obj->bufferFilled);

        // Fill

        for (iSample = 0; iSample < obj->hopSize; iSample++) {

            for (iMic = 0; iMic < obj->nMics; iMic++) {

                iByte = (iSample * obj->nMics + iMic) * 4;

                sampleLong = ((((unsigned long) frame[iByte+3]) << 24) & 0xFF000000) + 
                             ((((unsigned long) frame[iByte+2]) << 16) & 0x00FF0000) + 
                             ((((unsigned long) frame[iByte+1]) << 8) & 0x0000FF00) + 
                             ((((unsigned long) frame[iByte+0])) & 0x000000FF);

                sampleShort = (signed short) (sampleLong >> 16);
                sampleFloat = ((float) sampleShort) / fabs(SHRT_MIN);

                hops[iMic]->array[iSample] = sampleFloat;

            }

        }

        fifo_push(obj->bufferAvailable, (void *) frame);

    }

    void * eightsnd2hop_thread( void * dataPtr ) {

        eightsnd2hop_obj * obj;
        void * frame;
        int err;

        obj = (eightsnd2hop_obj *) dataPtr;

        while(1) {

            frame = fifo_pop(obj->bufferAvailable);

            if ((err = snd_pcm_readi(obj->captureHandle, frame, obj->hopSize)) != obj->hopSize) {

                printf("Read from audio interface failed: %s\n",snd_strerror(err));
                exit(EXIT_FAILURE);

            }

            fifo_push(obj->bufferFilled, frame);

            sem_post(&(obj->semaphore));

        }

    }