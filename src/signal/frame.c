    
    #include "frame.h"

    frame_obj * frame_construct_zero(const unsigned int frameSize) {

        frame_obj * obj;
        unsigned int iSample;

        obj = (frame_obj *) malloc(sizeof(frame_obj));

        obj->frameSize = frameSize;
        obj->array = (float *) malloc(sizeof(float) * frameSize);

        for (iSample = 0; iSample < frameSize; iSample++) {
        	obj->array[iSample] = 0.0f;
        }

        return obj;

    }

    void frame_destroy(frame_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void frame_printf(const frame_obj * obj) {

        unsigned int iSample;
        unsigned int iElement;
        unsigned char stop;

        iSample = 0;
        stop = 0; 

        while(stop == 0) {

            printf("(%04u): ",iSample);

            for (iElement = 0; iElement < 8; iElement++) {

                printf("%+1.8f ",obj->array[iSample]);

                iSample++;

                if (iSample == obj->frameSize) {
                    stop = 1;
                    break;
                }

            }

            printf("\n");

        }

    }

    frames_obj * frames_construct_null(const unsigned int nSignals) {

        frames_obj * obj;
        unsigned int iSignal;

        obj = (frames_obj *) malloc(sizeof(frames_obj));

        obj->nSignals = nSignals;
        obj->array = (frame_obj **) malloc(sizeof(frame_obj *) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {
            obj->array[iSignal] = NULL;
        }

        return obj;

    }

    frames_obj * frames_construct_zero(const unsigned int nSignals, const unsigned int frameSize) {

        frames_obj * obj;
        unsigned int iSignal;

        obj = (frames_obj *) malloc(sizeof(frames_obj));

        obj->nSignals = nSignals;
        obj->array = (frame_obj **) malloc(sizeof(frame_obj *) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {
            obj->array[iSignal] = frame_construct_zero(frameSize);
        }

        return obj;

    }

    void frames_destroy(frames_obj * obj) {

    	unsigned int iSignal;

    	for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
    		if (obj->array[iSignal] != NULL) {
    		    frame_destroy(obj->array[iSignal]);
    		}
    	}

    	free((void *) obj->array);
    	free((void *) obj);

    }

    void frames_printf(const frames_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            printf("(%02u): %p\n",iSignal,obj->array[iSignal]);

        }

    }