    
    #include "phasex2xcorr.h"

    phasex2xcorr_obj * phasex2xcorr_construct(const unsigned int frameSize) {

        phasex2xcorr_obj * obj;

        obj = (phasex2xcorr_obj *) malloc(sizeof(phasex2xcorr_obj));

        obj->frameSize = frameSize;
        obj->halfFrameSize = (frameSize/2)+1;

        obj->fft = fft_construct(obj->frameSize);

        return obj;

    }

    void phasex2xcorr_destroy(phasex2xcorr_obj * obj) {

        fft_destroy(obj->fft);

        free((void *) obj);

    }


    int phasex2xcorr_process(phasex2xcorr_obj * obj, const vector_float * phasex, vector_float * xcorr) {

        unsigned int iPair;

        fft_c2r(obj->fft,
                phasex->array,
                xcorr->array);

        return 0;

    }
