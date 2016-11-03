    
    #include "freq2phase.h"

    freq2phase_obj * freq2phase_construct(const unsigned int frameSize, const float epsilon, const unsigned int nMics) {

        freq2phase_obj * obj;

        obj = (freq2phase_obj *) malloc(sizeof(freq2phase_obj));

        obj->frameSize = frameSize;
        obj->halfFrameSize = frameSize/2+1;
        obj->nMics = nMics;
        obj->epsilon = epsilon;

        return obj;

    }

    void freq2phase_destroy(freq2phase_obj * obj) {

        free((void *) obj);

    }

    int freq2phase_process(freq2phase_obj * obj, const matrix_float * freqs, const matrix_float * masks, matrix_float * phases) {

        unsigned int iMic;
        unsigned int iSample;
        float sampleReal;
        float sampleImag;
        float magnitude;

        for (iMic = 0; iMic < obj->nMics; iMic++) {

            for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

                sampleReal = freqs->array[iMic][iSample*2+0];
                sampleImag = freqs->array[iMic][iSample*2+1];

                magnitude = sqrtf(sampleReal*sampleReal+sampleImag*sampleImag) + obj->epsilon;

                phases->array[iMic][iSample*2+0] = masks->array[iMic][iSample] * sampleReal / magnitude;
                phases->array[iMic][iSample*2+1] = masks->array[iMic][iSample] * sampleImag / magnitude;

            }

        }

        return 0;

    }