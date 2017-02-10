    
    #include "xcorr.h"

    xcorrs_obj * xcorrs_construct_zero(const unsigned int nSignals, const unsigned int frameSize) {

        xcorrs_obj * obj;

        obj = (xcorrs_obj *) malloc(sizeof(xcorrs_obj));

        obj->nSignals = nSignals;
        obj->frameSize = frameSize;
        obj->array = (float *) malloc(sizeof(float) * nSignals * frameSize);
        memset(obj->array, 0x00, nSignals * frameSize * sizeof(float));

        return obj;

    }

    void xcorrs_destroy(xcorrs_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void xcorrs_printf(const xcorrs_obj * obj) {

        unsigned int iSignal;
        unsigned int iSample;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            printf("(%04u): ",iSignal);

            for (iSample = 0; iSample < obj->frameSize; iSample++) {

                printf("%+1.5f ",obj->array[iSignal*obj->frameSize + iSample]);

                if ((((iSample+1) % 16) == 0) && ((iSample+1)!=obj->frameSize)) {
                    printf("\n        ");
                }

            }

            printf("\n");

        }

    }