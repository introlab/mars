    
    #include "hop.h"

    hop_obj * hop_construct_zero(const unsigned int hopSize) {

        hop_obj * obj;
        unsigned int iSample;

        obj = (hop_obj *) malloc(sizeof(hop_obj));

        obj->hopSize = hopSize;
        obj->array = (float *) malloc(sizeof(float) * hopSize);

        for (iSample = 0; iSample < hopSize; iSample++) {
        	obj->array[iSample] = 0.0f;
        }

        return obj;

    }

    void hop_destroy(hop_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void hop_printf(const hop_obj * obj) {

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

                if (iSample == obj->hopSize) {
                    stop = 1;
                    break;
                }

            }

            printf("\n");

        }

    }


    hops_obj * hops_construct_null(const unsigned int nSignals) {

        hops_obj * obj;
        unsigned int iSignal;

        obj = (hops_obj *) malloc(sizeof(hops_obj));

        obj->nSignals = nSignals;
        obj->array = (hop_obj **) malloc(sizeof(hop_obj *) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {
            obj->array[iSignal] = NULL;
        }

        return obj;

    }

    hops_obj * hops_construct_zero(const unsigned int nSignals, const unsigned int hopSize) {

        hops_obj * obj;
        unsigned int iSignal;

        obj = (hops_obj *) malloc(sizeof(hops_obj));

        obj->nSignals = nSignals;
        obj->array = (hop_obj **) malloc(sizeof(hop_obj *) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {
            obj->array[iSignal] = hop_construct_zero(hopSize);
        }

        return obj;

    }

    void hops_destroy(hops_obj * obj) {

    	unsigned int iSignal;

    	for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
    		if (obj->array[iSignal] != NULL) {
    		    hop_destroy(obj->array[iSignal]);
    		}
    	}

    	free((void *) obj->array);
    	free((void *) obj);

    }

    void hops_printf(const hops_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            printf("(%02u): %p\n",iSignal,obj->array[iSignal]);

        }

    }