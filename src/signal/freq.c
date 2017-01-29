    
    #include "freq.h"

    freq_obj * freq_construct_zero(const unsigned int halfFrameSize) {

        freq_obj * obj;
        unsigned int iSample;

        obj = (freq_obj *) malloc(sizeof(freq_obj));

        obj->halfFrameSize = halfFrameSize;
        obj->array = (float *) malloc(sizeof(float) * halfFrameSize * 2);

        for (iSample = 0; iSample < (halfFrameSize * 2); iSample++) {
        	obj->array[iSample] = 0.0f;
        }

        return obj;

    }

    void freq_destroy(freq_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void freq_printf(freq_obj * obj) {

        unsigned int iSample;
        unsigned int iElement;
        unsigned char stop;

        iSample = 0;
        stop = 0; 

        while(stop == 0) {

            printf("(%04u): ",iSample);

            for (iElement = 0; iElement < 4; iElement++) {

                printf("%+1.8f + %+1.8fi ",obj->array[iSample*2+0],obj->array[iSample*2+1]);

                iSample++;

                if (iSample == obj->halfFrameSize) {
                    stop = 1;
                    break;
                }

            }

            printf("\n");

        }        

    }

    freqs_obj * freqs_construct_null(const unsigned int nSignals) {

        freqs_obj * obj;
        unsigned int iSignal;

        obj = (freqs_obj *) malloc(sizeof(freqs_obj));

        obj->nSignals = nSignals;
        obj->array = (freq_obj **) malloc(sizeof(freq_obj *) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {
            obj->array[iSignal] = NULL;
        }

        return obj;

    }

    freqs_obj * freqs_construct_zero(const unsigned int nSignals, const unsigned int halfFrameSize) {

        freqs_obj * obj;
        unsigned int iSignal;

        obj = (freqs_obj *) malloc(sizeof(freqs_obj));

        obj->nSignals = nSignals;
        obj->array = (freq_obj **) malloc(sizeof(freq_obj *) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {
            obj->array[iSignal] = freq_construct_zero(halfFrameSize);
        }

        return obj;

    }

    void freqs_destroy(freqs_obj * obj) {

    	unsigned int iSignal;

    	for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
    		if (obj->array[iSignal] != NULL) {
    		    freq_destroy(obj->array[iSignal]);
    		}
    	}

    	free((void *) obj->array);
    	free((void *) obj);

    }

    void freqs_printf(freqs_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            printf("(%02u): %p\n",iSignal,obj->array[iSignal]);

        }

    }

