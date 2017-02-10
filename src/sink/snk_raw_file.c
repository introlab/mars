    
    #include "snk_raw_file.h"

    snk_raw_file_obj * snk_raw_file_construct(const snk_raw_file_cfg * cfg) {

        snk_raw_file_obj * obj;

        obj = (snk_raw_file_obj *) malloc(sizeof(snk_raw_file_obj));

        obj->timeStamp = 0;

        obj->hopSize = cfg->hopSize;
        obj->nMics = cfg->nMics;
        obj->nBits = cfg->nBits;

        obj->fileName = (char *) malloc(sizeof(char) * (strlen(cfg->fileName)+1));
        strcpy(obj->fileName, cfg->fileName);

        obj->fp = fopen(obj->fileName, "wb");

        if (obj->fp == NULL) {
            printf("Cannot open raw file.\n");
            exit(EXIT_FAILURE);
        }

        if (!((cfg->nBits == 16) | (cfg->nBits == 32))) {
            printf("Invalid number of bits.\n");
            exit(EXIT_FAILURE);         
        }

        return obj;

    }

    void snk_raw_file_destroy(const snk_raw_file_obj * obj) {

        fclose(obj->fp);
        free((void *) obj->fileName);
        free((void *) obj);        

    }

    int snk_raw_file_process(snk_raw_file_obj * obj, msg_hops_obj * msg_hops) {

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

                sample = msg_hops->hops->array[iMic * msg_hops->hops->hopSize + iSample];

                switch (obj->nBits) {
                    
                    case 16:

                        sampleShort = pcm_normalized2signed16bits(sample);
                        tmp = fwrite(&sampleShort, sizeof(signed short), 1, obj->fp);                    
                    
                    break;

                    case 32:

                        sampleInt = pcm_normalized2signed32bits(sample);
                        tmp = fwrite(&sampleInt, sizeof(signed int), 1, obj->fp);                    

                    break;

                }

            }

        }

        obj->timeStamp++;

        msg_hops->timeStamp = obj->timeStamp;

        return rtnValue;        

    }

    snk_raw_file_cfg * snk_raw_file_cfg_construct(void) {

        snk_raw_file_cfg * cfg;

        cfg = (snk_raw_file_cfg *) malloc(sizeof(snk_raw_file_cfg));

        cfg->fileName = (char *) NULL;

        return cfg;

    }

    void snk_raw_file_cfg_destroy(snk_raw_file_cfg * cfg) {

        if (cfg->fileName != NULL) {
            free((void *) cfg->fileName);
        }

        free((void *) cfg);

    }