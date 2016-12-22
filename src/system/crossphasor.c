    
    #include "crossphasor.h"

    crossphasor_obj * crossphasor_construct(const unsigned int frameSize) {

        crossphasor_obj * obj;

        obj = (crossphasor_obj *) malloc(sizeof(crossphasor_obj));

        obj->frameSize = frameSize;
        obj->halfFrameSize = frameSize/2 + 1;

        return obj;

    }

    void crossphasor_destroy(crossphasor_obj * obj) {

        free((void *) obj);

    }

    int crossphasor_process(crossphasor_obj * obj, const vector_float * phase1, const vector_float * phase2, vector_float * phase12) {

        unsigned int iSample;

        float phase1_real;
        float phase1_imag;
        float phase2_real;
        float phase2_imag;
        float phase12_real;
        float phase12_imag;

        for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

            phase1_real = phase1->array[iSample*2+0];
            phase1_imag = phase1->array[iSample*2+1];
            phase2_real = phase2->array[iSample*2+0];
            phase2_imag = phase2->array[iSample*2+1];

            phase12_real = phase1_real * phase2_real + phase1_imag * phase2_imag;
            phase12_imag = phase1_imag * phase2_real - phase1_real * phase2_imag;

            phase12->array[iSample*2+0] = phase12_real;
            phase12->array[iSample*2+1] = phase12_imag;

        }

        return 0;

    }
