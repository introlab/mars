
	#include "freq2mcra.h"

	freq2mcra_obj * freq2mcra_construct(const unsigned int frameSize, const unsigned int w, const unsigned int L, const float alphaS, const float alphaD, const float delta) {

		freq2mcra_obj * obj;
		vector_float * window;
		unsigned short iSample;

		obj = (freq2mcra_obj *) malloc(sizeof(freq2mcra_obj));

		obj->frameSize = frameSize;
		obj->halfFrameSize = frameSize/2 + 1;
		obj->w = w;
		obj->L = L;
		obj->alphaS = alphaS;
		obj->alphaD = alphaD;
		obj->delta = delta;

		obj->b = vector_float_malloc(obj->w*2+1);

		window = window_hann(obj->w*2+3);

		for (iSample = 0; iSample < (obj->w*2+1); iSample++) {
			obj->b->array[iSample] = window->array[iSample+1];
		}

		vector_float_free(window);

		obj->X2 = vector_float_malloc(obj->halfFrameSize);
		obj->Sf = vector_float_malloc(obj->halfFrameSize);
		obj->S = vector_float_malloc(obj->halfFrameSize);
		obj->Smin = vector_float_malloc(obj->halfFrameSize);
		obj->Stmp = vector_float_malloc(obj->halfFrameSize);
		obj->lambdaD = vector_float_malloc(obj->halfFrameSize);

		for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

			obj->X2->array[iSample] = 0.0f;
			obj->Sf->array[iSample] = 0.0f;
			obj->S->array[iSample] = 0.0f;
			obj->Smin->array[iSample] = 0.0f;
			obj->Stmp->array[iSample] = 0.0f;
			obj->lambdaD->array[iSample] = 0;

		}

		obj->l = 0;

		return obj;

	}

	void freq2mcra_destroy(freq2mcra_obj * obj) {

		vector_float_free(obj->b);
		vector_float_free(obj->X2);
		vector_float_free(obj->Sf);
		vector_float_free(obj->S);
		vector_float_free(obj->Smin);
		vector_float_free(obj->Stmp);
		vector_float_free(obj->lambdaD);

		free((void *) obj);

	}

	int freq2mcra_process(freq2mcra_obj * obj, const vector_float * freq, vector_float * mcra) {

		unsigned int iSample;
		signed int iSubSample;

		// X2

		for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

			obj->X2->array[iSample] = freq->array[iSample*2+0]*freq->array[iSample*2+0]+freq->array[iSample*2+1]*freq->array[iSample*2+1];

		}

		// Sf

		for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

			obj->Sf->array[iSample] = 0.0f;

			for (iSubSample = (-1 * ((signed int) obj->w)); iSubSample <= ((signed int) obj->w); iSubSample++) {

				obj->Sf->array[iSample] += obj->X2->array[indexing_cycle(((signed int) iSample)+iSubSample,obj->halfFrameSize)] * obj->b->array[(unsigned int) (iSubSample+((signed int) obj->w))];

			}

		}

		// S

		for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

			obj->S->array[iSample] = obj->alphaS * obj->S->array[iSample] + (1.0f - obj->alphaS) * obj->Sf->array[iSample];

		}

		// Smin, Stmp

		obj->l++;

		if (obj->l >= obj->L) {

			obj->l = 0;

			for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

				if (obj->Stmp->array[iSample] < obj->S->array[iSample]) {
					obj->Smin->array[iSample] = obj->Stmp->array[iSample];
				}
				else {
					obj->Smin->array[iSample] = obj->S->array[iSample];
				}

				obj->Stmp->array[iSample] = obj->S->array[iSample];

			}

		}
		else {

			for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

				if (obj->S->array[iSample] < obj->Smin->array[iSample]) {
					obj->Smin->array[iSample] = obj->S->array[iSample];
				}

				if (obj->S->array[iSample] < obj->Stmp->array[iSample]) {
					obj->Stmp->array[iSample] = obj->S->array[iSample];
				}

			}

		}

		// lambda

		for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

			if ((obj->S->array[iSample] < obj->delta * obj->Smin->array[iSample]) || (obj->lambdaD->array[iSample] > obj->X2->array[iSample])) {
				obj->lambdaD->array[iSample] = obj->alphaD * obj->lambdaD->array[iSample] + (1 - obj->alphaD) * obj->X2->array[iSample];
			}

		}

		for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {
			mcra->array[iSample] = obj->lambdaD->array[iSample];
		}

		return 0;

	}