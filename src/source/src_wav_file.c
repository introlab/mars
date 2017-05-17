    
    #include "src_wav_file.h"

    src_wav_file_obj * src_wav_file_construct(const src_wav_file_cfg * cfg) {

        src_wav_file_obj * obj;
        signed char bytes[44];
        int tmp;

        obj = (src_wav_file_obj *) malloc(sizeof(src_wav_file_obj));

        obj->timeStamp = 0;

        obj->hopSize = cfg->hopSize;
        obj->nChannels = cfg->nChannels;
        obj->nBits = cfg->nBits;
        
        obj->fileName = (char *) malloc(sizeof(char) * (strlen(cfg->fileName)+1));
        strcpy(obj->fileName, cfg->fileName);
        
        obj->fp = fopen(obj->fileName,"rb");

        if (obj->fp == NULL) {
            printf("Cannot open wav file.\n");
            exit(EXIT_FAILURE);
        }

        if (!((cfg->nBits == 16) | (cfg->nBits == 32))) {
            printf("Invalid number of bits.\n");
            exit(EXIT_FAILURE);         
        }

        // Flush the header (we don't need it)
        tmp = fread(bytes, sizeof(signed char), 44, obj->fp);

        return obj;

    }

    void src_wav_file_destroy(src_wav_file_obj * obj) {

        fclose(obj->fp);
        free((void *) obj->fileName);
        free((void *) obj);

    }

    int src_wav_file_process(src_wav_file_obj * obj, msg_hops_obj * msg_hops) {

        unsigned int iSample;
        unsigned int iChannel;
        signed short sampleShort;
        signed int sampleInt;
        float sample;
        int rtnValue;
        int tmp;

        rtnValue = 0;

        for (iSample = 0; iSample < obj->hopSize; iSample++) {
            
            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {
            
                if (!feof(obj->fp)) {

                    switch (obj->nBits) {
                        
                        case 16:
                        
                            tmp = fread(&sampleShort, sizeof(signed short), 1, obj->fp);
                            sample = pcm_signed16bits2normalized(sampleShort);
                        
                        break;
                        
                        case 32:
                        
                            tmp = fread(&sampleInt, sizeof(signed int), 1, obj->fp);
                            sample = pcm_signed32bits2normalized(sampleInt);
                        
                        break;
                    }

                }
                else {

                    sample = 0.0f;
                    rtnValue = -1;

                }

                msg_hops->hops->array[iChannel][iSample] = sample;

            }

        }

        obj->timeStamp++;

        msg_hops->timeStamp = obj->timeStamp;

        return rtnValue;

    }

    src_wav_file_cfg * src_wav_file_cfg_construct(void) {

        src_wav_file_cfg * cfg;

        cfg = (src_wav_file_cfg *) malloc(sizeof(src_wav_file_cfg));

        cfg->hopSize = 0;
        cfg->nChannels = 0;
        cfg->nBits = 0;
        cfg->fileName = (char *) NULL;

        return cfg;

    }

    void src_wav_file_cfg_destroy(src_wav_file_cfg * cfg) {

        if (cfg->fileName != NULL) {
            free((void *) cfg->fileName);    
        }
        
        free((void *) cfg);

    }