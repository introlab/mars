	
	#include "phases2xcorr.h"

	phases2xcorr_obj * phases2xcorr_construct(const unsigned int frameSize) {

		phases2xcorr_obj * obj;

		obj = (phases2xcorr_obj *) malloc(sizeof(phases2xcorr_obj));

		obj->frameSize = frameSize;
		obj->halfFrameSize = (frameSize/2)+1;

		obj->fft = fft_construct(obj->frameSize);

		return obj;

	}

	void phases2xcorr_destroy(phases2xcorr_obj * obj) {

		fft_destroy(obj->fft);

		free((void *) obj);

	}


	int phases2xcorr_process(phases2xcorr_obj * obj, const vector_float * phase12, vector_float * xcorr) {

		fft_c2r(obj->fft,
			    phase12->array,
			    xcorr->array);

		return 0;

	}
