    
    #include "xcorr.h"

    xcorr_obj * xcorr_construct_zero(const unsigned int frameSize) {

        xcorr_obj * obj;
        unsigned int iSample;

        obj = (xcorr_obj *) malloc(sizeof(xcorr_obj));

        obj->frameSize = frameSize;
        obj->array = (float *) malloc(sizeof(float) * frameSize);

        for (iSample = 0; iSample < frameSize; iSample++) {
            obj->array[iSample] = 0.0f;
        }

        return obj;

    }

    void xcorr_destroy(xcorr_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void xcorr_printf(const xcorr_obj * obj) {

        unsigned int iSample;
        unsigned int iElement;
        unsigned char stop;

        iSample = 0;
        stop = 0; 

        while(stop == 0) {

            printf("(%04u): ",iSample);

            for (iElement = 0; iElement < 16; iElement++) {

                printf("%+1.3f ",obj->array[iSample]);

                iSample++;

                if (iSample == obj->frameSize) {
                    stop = 1;
                    break;
                }

            }

            printf("\n");

        }

    }

    xcorrs_obj * xcorrs_construct_null(const unsigned int nSignals) {

        xcorrs_obj * obj;
        unsigned int iSignal;

        obj = (xcorrs_obj *) malloc(sizeof(xcorrs_obj));

        obj->nSignals = nSignals;
        obj->array = (xcorr_obj **) malloc(sizeof(xcorr_obj *) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {
        	obj->array[iSignal] = NULL;
        }

        return obj;

    }

    xcorrs_obj * xcorrs_construct_zero(const unsigned int nSignals, const unsigned int frameSize) {

        xcorrs_obj * obj;
        unsigned int iSignal;

        obj = (xcorrs_obj *) malloc(sizeof(xcorrs_obj));

        obj->nSignals = nSignals;
        obj->array = (xcorr_obj **) malloc(sizeof(xcorr_obj *) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {
        	obj->array[iSignal] = xcorr_construct_zero(frameSize);
        }

        return obj;

    }

    void xcorrs_destroy(xcorrs_obj * obj) {

    	unsigned int iSignal;

    	for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
    		if (obj->array[iSignal] != NULL) {
    		    xcorr_destroy(obj->array[iSignal]);
    		}
    	}

    	free((void *) obj->array);
    	free((void *) obj);

    }

    void xcorrs_printf(const xcorrs_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            printf("(%02u): %p\n",iSignal,obj->array[iSignal]);

        }

    }