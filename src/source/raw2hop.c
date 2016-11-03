    
    #include "raw2hop.h"

    raw2hop_obj * raw2hop_construct(const unsigned int hopSize, const unsigned int nMics, const unsigned int nBits, const char * fileName) {

        raw2hop_obj * obj;

        obj = (raw2hop_obj *) malloc(sizeof(raw2hop_obj));

        obj->hopSize = hopSize;
        obj->nMics = nMics;
        obj->nBits = nBits;
        obj->fileName = (char *) malloc(sizeof(char) * (strlen(fileName)+1));
        strcpy(obj->fileName, fileName);
        obj->fp = fopen(obj->fileName,"rb");

        if (!((nBits == 8) | (nBits == 16) | (nBits == 32))) {
            printf("Invalid number of bits.\n");
            exit(EXIT_FAILURE);        	
        }

        return obj;

    }

    void raw2hop_destroy(raw2hop_obj * obj) {

        fclose(obj->fp);
        free((void *) obj->fileName);

        free((void *) obj);

    }

    int raw2hop_process(raw2hop_obj * obj, matrix_float * hops) {

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

                hops->array[iMic][iSample] = sample;

            }

        }

        return rtnValue;

    }