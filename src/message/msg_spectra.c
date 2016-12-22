    
    #include "msg_spectra.h"

    msg_spectra_obj * msg_spectra_construct(const unsigned int frameSize, const unsigned int nMics) {

        msg_spectra_obj * obj;
        unsigned int iMic;

        obj = (msg_spectra_obj *) malloc(sizeof(msg_spectra_obj));

        obj->timeStamp = 0;

        obj->frameSize = frameSize;
        obj->halfFrameSize = frameSize/2 + 1;
        obj->nMics = nMics;

        obj->samples = (float **) malloc(sizeof(float *) * nMics);

        for (iMic = 0; iMic < nMics; iMic++) {
        	obj->samples[iMic] = (float *) malloc(sizeof(float) * (2 * obj->halfFrameSize));
        }

        return obj;

    }

    void msg_spectra_destroy(msg_spectra_obj * obj) {

        unsigned int iMic;

        for (iMic = 0; iMic < obj->nMics; iMic++) {

            free((void *) obj->samples[iMic]);

        }

        free((void *) obj->samples);
        free((void *) obj);

    }