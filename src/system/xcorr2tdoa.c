	
	#include "xcorr2tdoa.h"

	#include "../utils/indexing.h"

	xcorr2tdoa_obj * xcorr2tdoa_construct(const unsigned int frameSize, const unsigned int nPairs, const float epsilon) {

		xcorr2tdoa_obj * obj;

		obj = (xcorr2tdoa_obj *) malloc(sizeof(xcorr2tdoa_obj));

		obj->frameSize = frameSize;
		obj->nPairs = nPairs;
		obj->epsilon = epsilon;

		return obj;

	}

	void * xcorr2tdoa_destroy(xcorr2tdoa_obj * obj) {

		free((void *) obj);

	}
	
	int xcorr2tdoa_process(const xcorr2tdoa_obj * obj, const vector_float ** xcorr, const vector_signedint * minIndex, const vector_signedint * maxIndex, vector_float * tdoaIndex, vector_float * tdoaEnergy) {

		unsigned int iPair;
		signed int iSample;

		unsigned int iSamplePrev;
		unsigned int iSampleNow;
		unsigned int iSampleNext;

		float a, b, c;
		float ym1, y0, yp1;
		float xmax, ymax;

		float sampleMaxValue;
		signed int sampleMaxIndex;

		for (iPair = 0; iPair < obj->nPairs; iPair++) {

			sampleMaxValue = -INFINITY;
			sampleMaxIndex = 0;

			for (iSample = minIndex->array[iPair]; iSample < maxIndex->array[iPair]; iSample++) {

				if (xcorr[iPair]->array[indexing_wrap(iSample, obj->frameSize)] > sampleMaxValue) {

					sampleMaxValue = xcorr[iPair]->array[indexing_wrap(iSample, obj->frameSize)];
					sampleMaxIndex = iSample;

				}

			}

			iSamplePrev = indexing_wrap(sampleMaxIndex-1,obj->frameSize);
			iSampleNow = indexing_wrap(sampleMaxIndex,obj->frameSize);
			iSampleNext = indexing_wrap(sampleMaxIndex+1,obj->frameSize);

			ym1 = xcorr[iPair]->array[iSamplePrev];
			y0 = xcorr[iPair]->array[iSampleNow];
			yp1 = xcorr[iPair]->array[iSampleNext];

			a = (ym1/2.0f) - y0 + (yp1/2.0f);
			b = (yp1/2.0f) - (ym1/2.0f);
			c = y0;

			xmax = -1.0f * b / (2.0f * a + obj->epsilon);
			ymax = a*xmax*xmax + b*xmax + c;

			tdoaIndex->array[iPair] = xmax + sampleMaxIndex;
			tdoaEnergy->array[iPair] = ymax;

		}

	}