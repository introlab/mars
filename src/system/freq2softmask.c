
	#include "freq2softmask.h"

	freq2softmask_obj * freq2softmask_construct(const unsigned int frameSize, const float alphaP, const float epsilon) {

		freq2softmask_obj * obj;
		unsigned int iSample;

		obj = (freq2softmask_obj *) malloc(sizeof(freq2softmask_obj));

		obj->frameSize = frameSize;
		obj->halfFrameSize = frameSize/2 + 1;
		obj->alphaP = alphaP;
		obj->epsilon = epsilon;

		obj->X2 = vector_float_malloc(obj->halfFrameSize);
		obj->zeta = vector_float_malloc(obj->halfFrameSize);
		obj->xi = vector_float_malloc(obj->halfFrameSize);

		for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {
			
			obj->X2->array[iSample] = 0.0f;
			obj->zeta->array[iSample] = 0.0f;
			obj->xi->array[iSample] = 0.0f;

		}

		return obj;

	}

	void freq2softmask_destroy(freq2softmask_obj * obj) {

		vector_float_free(obj->X2);
		vector_float_free(obj->zeta);
		vector_float_free(obj->xi);

		free((void *) obj);

	}

	int freq2softmask_process(freq2softmask_obj * obj, const vector_float * freq, const vector_float * mcra, vector_float * mask) {

		unsigned int iSample;
		float X2;

		// Xi

		for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

			X2 = freq->array[iSample*2+0]*freq->array[iSample*2+0] + freq->array[iSample*2+1]*freq->array[iSample*2+1];
			obj->xi->array[iSample] = ((1.0f - obj->alphaP) * (obj->zeta->array[iSample]*obj->zeta->array[iSample]) * obj->X2->array[iSample] + obj->alphaP * X2) / (mcra->array[iSample] + obj->epsilon);
			obj->X2->array[iSample] = X2;

		}

		// Zeta

		for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

			obj->zeta->array[iSample] = obj->xi->array[iSample] / (obj->xi->array[iSample] + 1.0f);
			mask->array[iSample] = obj->zeta->array[iSample];

		}

		return 0;

	}
