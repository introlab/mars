    
    #include "frame.h"

    frames_obj * frames_construct_zero(const unsigned int nSignals, const unsigned int frameSize) {

        frames_obj * obj;

        obj = (frames_obj *) malloc(sizeof(frames_obj));

        obj->nSignals = nSignals;
        obj->frameSize = frameSize;
        obj->array = (float *) malloc(sizeof(float) * nSignals * frameSize);
        memset(obj->array, 0x00, nSignals * frameSize * sizeof(float));

        return obj;

    }

    void frames_destroy(frames_obj * obj) {

    	free((void *) obj->array);
    	free((void *) obj);

    }

    void frames_printf(const frames_obj * obj) {

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