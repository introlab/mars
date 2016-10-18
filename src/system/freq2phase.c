	
	#include "freq2phase.h"

	freq2phase_obj * freq2phase_construct(const unsigned int frameSize, const float epsilon) {

		freq2phase_obj * obj;

		obj = (freq2phase_obj *) malloc(sizeof(freq2phase_obj));

		obj->frameSize = frameSize;
		obj->halfFrameSize = frameSize/2+1;
		obj->epsilon = epsilon;

		return obj;

	}

	void freq2phase_destroy(freq2phase_obj * obj) {

		free((void *) obj);

	}

	int freq2phase_process(freq2phase_obj * obj, const vector_float * freq, const vector_float * mask, vector_float * phase) {

		unsigned int iSample;
		float sampleReal;
		float sampleImag;
		float magnitude;

		for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

			sampleReal = freq->array[iSample*2+0];
			sampleImag = freq->array[iSample*2+1];

			magnitude = sqrtf(sampleReal*sampleReal+sampleImag*sampleImag) + obj->epsilon;

			phase->array[iSample*2+0] = mask->array[iSample] * sampleReal / magnitude;
			phase->array[iSample*2+1] = mask->array[iSample] * sampleImag / magnitude;

		}

		return 0;

	}