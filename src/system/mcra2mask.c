    
    #include "mcra2mask.h"

    mcra2mask_obj * mcra2mask_construct(unsigned int frameSize, const float alphaP, const float epsilon) {

        mcra2mask_obj * obj;
        unsigned int iSample;

        obj = (mcra2mask_obj *) malloc(sizeof(mcra2mask_obj));

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

    void mcra2mask_destroy(mcra2mask_obj * obj) {

        vector_float_free(obj->X2);
        vector_float_free(obj->zeta);
        vector_float_free(obj->xi);

        free((void *) obj);

    }

    int mcra2mask_process(mcra2mask_obj * obj, const vector_float * freq, const vector_float * mcra, vector_float * mask) {

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