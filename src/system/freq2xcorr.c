    
    #include "freq2xcorr.h"

    freq2xcorr_obj * freq2xcorr_construct_zero(const unsigned int frameSize, const unsigned int halfFrameSize) {

        freq2xcorr_obj * obj;

        obj = (freq2xcorr_obj *) malloc(sizeof(freq2xcorr_obj));

        obj->frameSize = frameSize;
        obj->halfFrameSize = halfFrameSize;

        obj->frame = frame_construct_zero(frameSize);
        obj->fft = fft_construct(frameSize);

        return obj;

    }

    void freq2xcorr_destroy(freq2xcorr_obj * obj) {

        fft_destroy(obj->fft);
        frame_destroy(obj->frame);

        free((void *) obj);

    }

    void freq2xcorr_process_single(freq2xcorr_obj * obj, const freq_obj * freq, const unsigned int minTdoa, const unsigned maxTdoa, xcorr_obj * xcorr) {

        unsigned int iSample;

        fft_c2r(obj->fft, freq->array, obj->frame->array);

        for (iSample = minTdoa; iSample < maxTdoa; iSample++) { 
            if (iSample < obj->frameSize/2) {
                xcorr->array[iSample] = obj->frame->array[iSample+obj->frameSize/2] / ((float) obj->frameSize);    
            }
            else {
                xcorr->array[iSample] = obj->frame->array[iSample-obj->frameSize/2] / ((float) obj->frameSize);    
            }
            
        }

    }

    void freq2xcorr_process_many(freq2xcorr_obj * obj, const freqs_obj * freqs, const tdoa_obj * minTdoas, const tdoa_obj * maxTdoas, xcorrs_obj * xcorrs) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < freqs->nSignals; iSignal++) {
        	freq2xcorr_process_single(obj, freqs->array[iSignal], minTdoas->array[iSignal], maxTdoas->array[iSignal], xcorrs->array[iSignal]);
        }

    }