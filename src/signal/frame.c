    
    #include "frame.h"

    frames_obj * frames_construct_zero(const unsigned int nSignals, const unsigned int frameSize) {

        frames_obj * obj;
        unsigned int iSignal;

        obj = (frames_obj *) malloc(sizeof(frames_obj));

        obj->nSignals = nSignals;
        obj->frameSize = frameSize;
        
        obj->array = (float **) malloc(sizeof(float *) * nSignals);
        for (iSignal = 0; iSignal < nSignals; iSignal++) {
            obj->array[iSignal] = (float *) malloc(sizeof(float) * frameSize);
            memset(obj->array[iSignal], 0x00, frameSize * sizeof(float));
        }

        return obj;

    }

    void frames_destroy(frames_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            free((void *) obj->array[iSignal]);
        }
    	free((void *) obj->array);
    	
        free((void *) obj);

    }

    void frames_printf(const frames_obj * obj) {

        unsigned int iSignal;
        unsigned int iSample;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            printf("(%04u): ",iSignal);

            for (iSample = 0; iSample < obj->frameSize; iSample++) {

                printf("%+1.5f ",obj->array[iSignal][iSample]);

                if ((((iSample+1) % 16) == 0) && ((iSample+1)!=obj->frameSize)) {
                    printf("\n        ");
                }

            }

            printf("\n");

        }

    }