	
	#include "raw2hop.h"

	raw2hop_obj * raw2hop_construct(const unsigned int hopSize, const unsigned int nMics, const unsigned char nBits) {

		raw2hop_obj * obj;

		obj = (raw2hop_obj *) malloc(sizeof(raw2hop_obj));

		obj->hopSize = hopSize;
		obj->nMics = nMics;
		obj->nBits = nBits;

		switch(nBits) {
			case 8:
				obj->sizeSample = sizeof(signed char);
				obj->maxAmplitude = (float) fabs(SCHAR_MIN);
			break;
			case 16:
				obj->sizeSample = sizeof(signed short);
				obj->maxAmplitude = (float) fabs(SHRT_MIN);
			break;
			case 32:
				obj->sizeSample = sizeof(signed int);
				obj->maxAmplitude = (float) fabs(INT_MIN);
			break;
			default:
				printf("Invalid number of bits.\n");
				exit(EXIT_FAILURE);
			break;
		}

		return obj;

	}

	void raw2hop_destroy(raw2hop_obj * obj) {

		free((void *) obj);

	}

	int raw2hop_process(raw2hop_obj * obj, FILE * fp, vector_float ** hops) {

		unsigned int iSample;
		unsigned int iMic;
		signed char sampleChar;
		signed short sampleShort;
		signed int sampleInt;
		float sample;
		int rtnValue;
		int tmp;

		rtnValue = 0;

		for (iSample = 0; iSample < obj->hopSize; iSample++) {
			
			for (iMic = 0; iMic < obj->nMics; iMic++) {
			
				if (!feof(fp)) {

					switch (obj->nBits) {
						case 8:
							tmp = fread(&sampleChar, obj->sizeSample, 1, fp);
							sample = (float) sampleChar;
						break;
						case 16:
							tmp = fread(&sampleShort, obj->sizeSample, 1, fp);
							sample = (float) sampleShort;
						break;
						case 32:
							tmp = fread(&sampleInt, obj->sizeSample, 1, fp);
							sample = (float) sampleInt;
						break;
					}

				}
				else {

					sample = 0.0f;
					rtnValue = -1;

				}

				if (hops != NULL) {

					hops[iMic]->array[iSample] = sample / obj->maxAmplitude;

				}

			}

		}

		return rtnValue;

	}