    
    #include "src_raw_file.h"

    src_raw_file_obj * src_raw_file_construct(const src_raw_file_cfg * cfg) {

        src_raw_file_obj * obj;

        obj = (src_raw_file_obj *) malloc(sizeof(src_raw_file_obj));

        obj->timeStamp = 0;

        obj->hopSize = cfg->hopSize;
        obj->nMics = cfg->nMics;
        obj->nBits = cfg->nBits;
        
        obj->fileName = (char *) malloc(sizeof(char) * (strlen(cfg->fileName)+1));
        strcpy(obj->fileName, cfg->fileName);
        
        obj->fp = fopen(obj->fileName,"rb");

        if (obj->fp == NULL) {
            printf("Cannot open raw file.\n");
            exit(EXIT_FAILURE);
        }

        if (!((cfg->nBits == 8) | (cfg->nBits == 16) | (cfg->nBits == 32))) {
            printf("Invalid number of bits.\n");
            exit(EXIT_FAILURE);        	
        }

        return obj;

    }

    void src_raw_file_destroy(src_raw_file_obj * obj) {

        fclose(obj->fp);
        free((void *) obj->fileName);
        free((void *) obj);

    }

    int src_raw_file_process(src_raw_file_obj * obj, msg_hops_obj * msg_hops) {

        unsigned int iSample;
        unsigned int iMic;
        signed char sampleChar;
        signed short sampleShort;
        signed int sampleInt;
        float sample;
        int rtnValue;
        int tmp;

        rtnValue = 0;

        for (iSample = 0; iSample < obj->hopSize; iSample++) {
            
            for (iMic = 0; iMic < obj->nMics; iMic++) {
            
                if (!feof(obj->fp)) {

                    switch (obj->nBits) {
                        
                        case 8:
                        
                            tmp = fread(&sampleChar, sizeof(signed char), 1, obj->fp);
                            sample = pcm_signed08bits2normalized(sampleChar);
                        
                        break;
                        
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

                msg_hops->hops->array[iMic * msg_hops->hops->hopSize + iSample] = sample;

            }

        }

        obj->timeStamp++;

        msg_hops->timeStamp = obj->timeStamp;

        return rtnValue;

    }

    src_raw_file_cfg * src_raw_file_cfg_construct(void) {

        src_raw_file_cfg * cfg;

        cfg = (src_raw_file_cfg *) malloc(sizeof(src_raw_file_cfg));

        cfg->hopSize = 0;
        cfg->nMics = 0;
        cfg->nBits = 0;
        cfg->fileName = (char *) NULL;

        return cfg;

    }

    void src_raw_file_cfg_destroy(src_raw_file_cfg * cfg) {

        if (cfg->fileName != NULL) {
            free((void *) cfg->fileName);    
        }
        
        free((void *) cfg);

    }