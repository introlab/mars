    
    #include "mask.h"

    mask_obj * mask_construct(unsigned int frameSize, const float alphaP, const float epsilon) {

        mask_obj * obj;
        unsigned int iSample;

        obj = (mask_obj *) malloc(sizeof(mask_obj));

        obj->frameSize = frameSize;
        obj->halfFrameSize = frameSize/2 + 1;
        obj->alphaP = alphaP;
        obj->epsilon = epsilon;

        obj->zeta = vector_float_malloc(obj->halfFrameSize);
        obj->xi = vector_float_malloc(obj->halfFrameSize);

        for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {
        	obj->zeta->array[iSample] = 0.0f;
        	obj->xi->array[iSample] = 0.0f;
        }

        return obj;

    }

    void mask_destroy(mask_obj * obj) {

        vector_float_free(obj->X2);
        vector_float_free(obj->zeta);
        vector_float_free(obj->xi);

        free((void *) obj);

    }

    int mask_process(mask_obj * obj, const vector_float * freq, const vector_float * mcra, vector_float * mask) {

        unsigned int iSample;
        float Xreal, Ximag;
        float X2;
        float zeta;
        float noise;
        float xi;

        for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

            Xreal = freq->array[iSample*2+0];
            Ximag = freq->array[iSample*2+1];
            X2 = Xreal * Xreal + Ximag * Ximag;

            zeta = obj->zeta->array[iSample];
            noise = mcra->array[iSample];

            xi = ((1 - obj->alphaP) * (zeta*zeta) * X2 + obj->alphaP * X2) / (noise + obj->epsilon);
            zeta = xi / (xi + 1.0f);

            obj->xi->array[iSample] = xi;
            obj->zeta->array[iSample] = zeta;

            mask->array[iSample] = zeta;

        }

    }