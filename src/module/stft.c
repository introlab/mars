
    #include "stft.h"

    stft_obj * stft_construct(const unsigned int hopSize, const unsigned int frameSize, const unsigned int nMics) {

    	stft_obj * obj;
    	unsigned int iMic;

    	obj = (stft_obj *) malloc(sizeof(stft_obj));

    	obj->hopSize = hopSize;
    	obj->frameSize = frameSize;
    	obj->nMics = nMics;

    	obj->frames = (vector_float **) malloc(sizeof(vector_float *) * nMics);
    	obj->hop2frame = (hop2frame_obj **) malloc(sizeof(hop2frame_obj *) * nMics);
    	obj->frame2freq = (frame2freq_obj **) malloc(sizeof(frame2freq_obj *) * nMics);

    	for (iMic = 0; iMic < nMics; iMic++) {

    		obj->frames[iMic] = vector_float_malloc(frameSize);
    		obj->hop2frame[iMic] = hop2frame_construct(hopSize, frameSize);
    		obj->frame2freq[iMic] = frame2freq_construct(frameSize);

    	}

    	obj->window = window_hann(frameSize);

    	return obj;

    }

    void stft_destroy(stft_obj * obj) {

    	unsigned int iMic;

    	for (iMic = 0; iMic < obj->nMics; iMic++) {

    		vector_float_free(obj->frames[iMic]);
    		hop2frame_destroy(obj->hop2frame[iMic]);
    		frame2freq_destroy(obj->frame2freq[iMic]);

    	}

    	free((void *) obj->frames);
    	free((void *) obj->hop2frame);
    	free((void *) obj->frame2freq);

    	free((void *) obj);

    }

    int stft_process(stft_obj * obj, const vector_float ** hops, vector_float ** freqs) {

    	unsigned int iMic;

    	for (iMic = 0; iMic < obj->nMics; iMic++) {

    		hop2frame_process(obj->hop2frame[iMic],hops[iMic],obj->frames[iMic]);
    		frame2freq_process(obj->frame2freq[iMic], obj->frames[iMic], obj->window, freqs[iMic]);

    	}

    }
