    
    #include "freq.h"

    freqs_obj * freqs_construct_zero(const unsigned int nSignals, const unsigned int halfFrameSize) {

        freqs_obj * obj;

        obj = (freqs_obj *) malloc(sizeof(freqs_obj));

        obj->nSignals = nSignals;
        obj->halfFrameSize = halfFrameSize;
        obj->array = (float *) malloc(sizeof(float) * nSignals * halfFrameSize * 2);
        memset(obj->array, 0x00, nSignals * halfFrameSize * 2 * sizeof(float));

        return obj;

    }

    void freqs_destroy(freqs_obj * obj) {

    	free((void *) obj->array);
    	free((void *) obj);

    }

    void freqs_printf(const freqs_obj * obj) {

        unsigned int iSignal;
        unsigned int iSample;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            printf("(%04u): ",iSignal);

            for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

                printf("(%+1.5f + %+1.5fj) ",
                       obj->array[iSignal*obj->halfFrameSize*2 + iSample*2 + 0],
                       obj->array[iSignal*obj->halfFrameSize*2 + iSample*2 + 1]);

                if ((((iSample+1) % 8) == 0) && ((iSample+1)!=obj->halfFrameSize)) {
                    printf("\n        ");
                }

            }

            printf("\n");

        }        

    }