
    #include "frame2freq.h"

    frame2freq_obj * frame2freq_construct_zero(const unsigned int frameSize, const unsigned int halfFrameSize) {

        frame2freq_obj * obj;

        obj = (frame2freq_obj *) malloc(sizeof(frame2freq_obj));

        obj->frameSize = frameSize;
        obj->halfFrameSize = halfFrameSize;

        obj->win =windowing_hann(frameSize);
        obj->frame = frame_construct_zero(frameSize);

        obj->fft = fft_construct(frameSize);

        return obj;

    }

    void frame2freq_destroy(frame2freq_obj * obj) {

        window_destroy(obj->win);
        frame_destroy(obj->frame);

        free((void *) obj);

    }

    void frame2freq_process_single(frame2freq_obj * obj, const frame_obj * frame, freq_obj * freq) {

        unsigned int iSample;

        for (iSample = 0; iSample < obj->frameSize; iSample++) {
        	obj->frame->array[iSample] = obj->win->array[iSample] * frame->array[iSample];
        }

        fft_r2c(obj->fft, obj->frame->array, freq->array);

    }

    void frame2freq_process_many(frame2freq_obj * obj, const frames_obj * frames, freqs_obj * freqs) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < frames->nSignals; iSignal++) {

            frame2freq_process_single(obj, frames->array[iSignal], freqs->array[iSignal]);

        }

    }