    
    #include "spectrum.h"

    spectrum_obj * spectrum_construct(const unsigned int frameSize) {

        spectrum_obj * obj;

        obj = (spectrum_obj *) malloc(sizeof(spectrum_obj));

        obj->frameSize = frameSize;
        obj->halfFrameSize = frameSize/2+1;

        obj->frameWindowed = vector_float_malloc(obj->frameSize);

        obj->fft = fft_construct(obj->frameSize);

        return obj;

    }

    void spectrum_destroy(spectrum_obj * obj) {

        vector_float_free(obj->frameWindowed);
        
        fft_destroy(obj->fft);

        free((void *) obj);

    }

    int spectrum_process(spectrum_obj * obj, const vector_float * frame, const vector_float * window, vector_float * freq) {

        unsigned int iSample;

        for (iSample = 0; iSample < obj->frameSize; iSample++) {

            obj->frameWindowed->array[iSample] = frame->array[iSample] * window->array[iSample];

        }

        fft_r2c(obj->fft,
                obj->frameWindowed->array,
                freq->array);

        return 0;

    }