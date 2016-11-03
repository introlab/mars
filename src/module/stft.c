
    #include "stft.h"

    stft_obj * stft_construct(const unsigned int hopSize, const unsigned int frameSize, const unsigned int nMics) {

    	stft_obj * obj;
    	unsigned int iMic;

    	obj = (stft_obj *) malloc(sizeof(stft_obj));

    	obj->hopSize = hopSize;
    	obj->frameSize = frameSize;
    	obj->nMics = nMics;

    	obj->frames = matrix_float_malloc(nMics,frameSize);
    	obj->hop2frame = hop2frame_construct(hopSize,frameSize,nMics);
    	obj->frame2freq = frame2freq_construct(frameSize,nMics);
    	obj->window = window_hann(frameSize);

    	return obj;

    }

    void stft_destroy(stft_obj * obj) {

    	matrix_float_free(obj->frames);
    	hop2frame_destroy(obj->hop2frame);
    	frame2freq_destroy(obj->frame2freq);
        vector_float_free(obj->window);

    	free((void *) obj);

    }

    int stft_process(stft_obj * obj, const matrix_float * hops, matrix_float * freqs) {

        hop2frame_process(obj->hop2frame, hops, obj->frames);
        frame2freq_process(obj->frame2freq, obj->frames, obj->window, freqs);

    }
