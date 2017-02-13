    
    #include "freq2xcorr.h"

    freq2xcorr_obj * freq2xcorr_construct_zero(const unsigned int frameSize, const unsigned int halfFrameSize) {

        freq2xcorr_obj * obj;

        obj = (freq2xcorr_obj *) malloc(sizeof(freq2xcorr_obj));

        obj->frameSize = frameSize;
        obj->halfFrameSize = halfFrameSize;

        obj->frame = (float *) malloc(sizeof(float) * halfFrameSize * 2);
        memset(obj->frame,0x00,sizeof(float)* halfFrameSize * 2);

        obj->fft = fft_construct(frameSize);

        return obj;

    }

    void freq2xcorr_destroy(freq2xcorr_obj * obj) {

        fft_destroy(obj->fft);
        free((void *) obj->frame);

        free((void *) obj);

    }

    void freq2xcorr_process(freq2xcorr_obj * obj, const freqs_obj * freqs, const tdoas_obj * tdoas, xcorrs_obj * xcorrs) {

        unsigned int iSignal;
        unsigned int iSample;
        unsigned int iSampleSrc;
        unsigned int iSampleDest;

        for (iSignal = 0; iSignal < freqs->nSignals; iSignal++) {

        	fft_c2r(obj->fft, 
                    freqs->array[iSignal],
                    obj->frame);

            for (iSample = tdoas->arrayMin[iSignal]; iSample <= tdoas->arrayMax[iSignal]; iSample++) {

                iSampleDest = iSample;

                if (iSample < obj->frameSize/2) {
                    
                    iSampleSrc = iSample + obj->frameSize/2;

                }
                else {

                    iSampleSrc = iSample - obj->frameSize/2;

                }

                xcorrs->array[iSignal][iSampleDest] = obj->frame[iSampleSrc] / ((float) obj->frameSize);

            }

        }

    }