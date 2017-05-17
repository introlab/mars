
    #include "mic.h"

    mics_obj * mics_construct_zero(const unsigned int nChannels) {

        mics_obj * obj;

        obj = (mics_obj *) malloc(sizeof(mics_obj));

        obj->nChannels = nChannels;
        obj->mu = (float *) malloc(sizeof(float) * nChannels * 3);
        memset(obj->mu, 0x00, sizeof(float) * nChannels * 3);        
        obj->sigma = (float *) malloc(sizeof(float) * nChannels * 9);
        memset(obj->sigma, 0x00, sizeof(float) * nChannels * 9);        

        return obj;

    }

    void mics_destroy(mics_obj * obj) {

        free((void *) obj->mu);
        free((void *) obj->sigma);

        free((void *) obj);

    }