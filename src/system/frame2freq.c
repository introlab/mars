    
    #include "frame2freq.h"

    frame2freq_obj * frame2freq_construct(const unsigned int frameSize, const unsigned int nMics) {

        frame2freq_obj * obj;

        obj = (frame2freq_obj *) malloc(sizeof(frame2freq_obj));

        obj->frameSize = frameSize;
        obj->halfFrameSize = frameSize/2+1;
        obj->nMics = nMics;

        obj->frameWindowed = vector_float_malloc(obj->frameSize);

        obj->fft = fft_construct(obj->frameSize);

        return obj;

    }

    void frame2freq_destroy(frame2freq_obj * obj) {

        vector_float_free(obj->frameWindowed);
        
        fft_destroy(obj->fft);

        free((void *) obj);

    }

    int frame2freq_process(frame2freq_obj * obj, const matrix_float * frames, const vector_float * window, matrix_float * freqs) {

        unsigned int iSample;
        unsigned int iMic;

        for (iMic = 0; iMic < obj->nMics; iMic++) {

            for (iSample = 0; iSample < obj->frameSize; iSample++) {

                obj->frameWindowed->array[iSample] = frames->array[iMic][iSample] * window->array[iSample];

            }

            fft_r2c(obj->fft,
                    obj->frameWindowed->array,
                    freqs->array[iMic]);

        }

        return 0;

    }