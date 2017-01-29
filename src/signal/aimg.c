    
    #include "aimg.h"

    aimg_obj * aimg_construct_zero(const unsigned int aimgSize) {

        aimg_obj * obj;
        unsigned int iSample;

        obj = (aimg_obj *) malloc(sizeof(aimg_obj));

        obj->aimgSize = aimgSize;
        obj->array = (float *) malloc(sizeof(float) * aimgSize);

        for (iSample = 0; iSample < aimgSize; iSample++) {
        	obj->array[iSample] = 0.0f;
        }

        return obj;

    }

    void aimg_destroy(aimg_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }