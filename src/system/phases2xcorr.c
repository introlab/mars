    
    #include "phases2xcorr.h"

    phases2xcorr_obj * phases2xcorr_construct(const unsigned int frameSize, const unsigned int nMics) {

        phases2xcorr_obj * obj;

        obj = (phases2xcorr_obj *) malloc(sizeof(phases2xcorr_obj));

        obj->frameSize = frameSize;
        obj->halfFrameSize = (frameSize/2)+1;
        obj->nMics = nMics;
        obj->nPairs = (nMics-1) * nMics / 2;

        obj->fft = fft_construct(obj->frameSize);

        return obj;

    }

    void phases2xcorr_destroy(phases2xcorr_obj * obj) {

        fft_destroy(obj->fft);

        free((void *) obj);

    }


    int phases2xcorr_process(phases2xcorr_obj * obj, const matrix_float * phasesx, matrix_float * xcorrs) {

        unsigned int iPair;

        for (iPair = 0; iPair < obj->nPairs; iPair++) {

            fft_c2r(obj->fft,
                    phasesx->array[iPair],
                    xcorrs->array[iPair]);

        }

        return 0;

    }
