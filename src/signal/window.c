
    #include "window.h"

    window_obj * window_construct_zero(const unsigned int frameSize) {

        window_obj * obj;
        unsigned int iSample;

        obj = (window_obj *) malloc(sizeof(window_obj));

        obj->frameSize = frameSize;
        obj->array = (float *) malloc(sizeof(float) * frameSize);

        for (iSample = 0; iSample < frameSize; iSample++) {
        	obj->array[iSample] = 0.0f;
        }

        return obj;

    }

    void window_destroy(window_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }