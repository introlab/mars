    
    #include "hop2raw.h"

    hop2raw_obj * hop2raw_construct(const unsigned int hopSize, const unsigned int nMics, const unsigned int nBits, const char * fileName) {

        hop2raw_obj * obj;

        obj = (hop2raw_obj *) malloc(sizeof(hop2raw_obj));

        obj->hopSize = hopSize;
        obj->nMics = nMics;
        obj->nBits = nBits;
        obj->fileName = (char *) malloc(sizeof(char) * (strlen(fileName)+1));
        strcpy(obj->fileName, fileName);
        obj->fp = fopen(obj->fileName,"wb");                

        if (!((nBits == 8) | (nBits == 16) | (nBits == 32))) {
            printf("Invalid number of bits.\n");
            exit(EXIT_FAILURE);         
        }

        return obj;

    }

    void hop2raw_destroy(hop2raw_obj * obj) {

        fclose(obj->fp);
        free((void *) obj->fileName);

        free((void *) obj);

    }

    int hop2raw_process(hop2raw_obj * obj, matrix_float * hops) {

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

                sample = hops->array[iMic][iSample];

                switch (obj->nBits) {
                    case 8:
                        sampleChar = pcm_normalized2signed08bits(sample);
                        tmp = fwrite(&sampleChar, sizeof(signed char), 1, obj->fp);
                    break;
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

        return rtnValue;

    }