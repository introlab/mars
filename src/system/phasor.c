    
    #include "phasor.h"

    phasor_obj * phasor_construct(const unsigned int frameSize, const float epsilon) {

        phasor_obj * obj;

        obj = (phasor_obj *) malloc(sizeof(phasor_obj));

        obj->frameSize = frameSize;
        obj->halfFrameSize = frameSize/2+1;
        obj->epsilon = epsilon;

        return obj;

    }

    void phasor_destroy(phasor_obj * obj) {

        free((void *) obj);

    }

    int phasor_process(phasor_obj * obj, const vector_float * freq, const vector_float * mask, vector_float * phase) {

        unsigned int iSample;
        float sampleReal;
        float sampleImag;
        float magnitude;

        if (mask != NULL) {

            for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

                sampleReal = freq->array[iSample*2+0];
                sampleImag = freq->array[iSample*2+1];

                magnitude = sqrtf(sampleReal*sampleReal+sampleImag*sampleImag) + obj->epsilon;

                phase->array[iSample*2+0] = mask->array[iSample] * sampleReal / magnitude;
                phase->array[iSample*2+1] = mask->array[iSample] * sampleImag / magnitude;

            }

        }
        else {

            for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

                sampleReal = freq->array[iSample*2+0];
                sampleImag = freq->array[iSample*2+1];

                magnitude = sqrtf(sampleReal*sampleReal+sampleImag*sampleImag) + obj->epsilon;

                phase->array[iSample*2+0] = sampleReal / magnitude;
                phase->array[iSample*2+1] = sampleImag / magnitude;

            }

        }

        return 0;

    }