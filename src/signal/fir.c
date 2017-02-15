
    #include "fir.h"

    firs_obj * firs_construct_zero(unsigned int nSignals, unsigned int nCoefficients) {

        firs_obj * obj;
        unsigned int iSignal;

        obj = (firs_obj *) malloc(sizeof(firs_obj));

        obj->nSignals = nSignals;
        obj->nCoefficients = nCoefficients;

        obj->xs = (float **) malloc(sizeof(float *) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {

            obj->xs[iSignal] = (float *) malloc(sizeof(float) * nCoefficients);
            memset(obj->xs[iSignal], 0x00, sizeof(float) * nCoefficients);

        }

        return obj;

    }

    void firs_destroy(firs_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            free((void *) (obj->xs[iSignal]));

        }

        free((void *) obj->xs);
        free((void *) obj);

    }
