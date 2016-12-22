    
    #include "xcorr.h"

    xcorr_obj * xcorr_construct(const unsigned int frameSize) {

        xcorr_obj * obj;

        obj = (xcorr_obj *) malloc(sizeof(xcorr_obj));

        obj->frameSize = frameSize;
        obj->halfFrameSize = (frameSize/2)+1;

        obj->fft = fft_construct(obj->frameSize);

        return obj;

    }

    void xcorr_destroy(xcorr_obj * obj) {

        fft_destroy(obj->fft);

        free((void *) obj);

    }


    int xcorr_process(xcorr_obj * obj, const vector_float * phasex, vector_float * xcorr) {

        unsigned int iPair;

        fft_c2r(obj->fft,
                phasex->array,
                xcorr->array);

        return 0;

    }
