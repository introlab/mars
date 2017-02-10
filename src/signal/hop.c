    
    #include "hop.h"

    hops_obj * hops_construct_zero(const unsigned int nSignals, const unsigned int hopSize) {

        hops_obj * obj;
        unsigned int iSignal;

        obj = (hops_obj *) malloc(sizeof(hops_obj));

        obj->nSignals = nSignals;
        obj->hopSize = hopSize;
        obj->array = (float *) malloc(sizeof(float) * nSignals * hopSize);
        memset(obj->array, 0x00, nSignals * hopSize * sizeof(float));

        return obj;

    }

    void hops_destroy(hops_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void hops_printf(const hops_obj * obj) {

        unsigned int iSignal;
        unsigned int iSample;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            printf("(%04u): ",iSignal);

            for (iSample = 0; iSample < obj->hopSize; iSample++) {

                printf("%+1.5f ",obj->array[iSignal*obj->hopSize + iSample]);

                if ((((iSample+1) % 16) == 0) && ((iSample+1)!=obj->hopSize)) {
                    printf("\n        ");
                }

            }

            printf("\n");

        }

    }