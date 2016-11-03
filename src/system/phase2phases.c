    
    #include "phase2phases.h"

    phase2phases_obj * phase2phases_construct(const unsigned int frameSize, const unsigned int nMics) {

        phase2phases_obj * obj;

        obj = (phase2phases_obj *) malloc(sizeof(phase2phases_obj));

        obj->frameSize = frameSize;
        obj->halfFrameSize = frameSize/2 + 1;
        obj->nMics = nMics;
        obj->nPairs = (nMics - 1) * nMics / 2;

        return obj;

    }

    void phase2phases_destroy(phase2phases_obj * obj) {

        free((void *) obj);

    }

    int phase2phases_process(phase2phases_obj * obj, const matrix_float * phases, matrix_float * phasesx) {

        unsigned int iMic1;
        unsigned int iMic2;
        unsigned int iPair;
        unsigned int iSample;

        float phases1_real;
        float phases1_imag;
        float phases2_real;
        float phases2_imag;
        float phases12_real;
        float phases12_imag;

        iPair = 0;

        for (iMic1 = 0; iMic1 < obj->nMics; iMic1++) {

            for (iMic2 = (iMic1+1); iMic2 < obj->nMics; iMic2++) {

                for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

                    phases1_real = phases->array[iMic1][iSample*2+0];
                    phases1_imag = phases->array[iMic1][iSample*2+1];
                    phases2_real = phases->array[iMic2][iSample*2+0];
                    phases2_imag = phases->array[iMic2][iSample*2+1];

                    phases12_real = phases1_real * phases2_real + phases1_imag * phases2_imag;
                    phases12_imag = phases1_imag * phases2_real - phases1_real * phases2_imag;

                    phasesx->array[iPair][iSample*2+0] = phases12_real;
                    phasesx->array[iPair][iSample*2+1] = phases12_imag;

                }

            }

        }

        return 0;

    }
