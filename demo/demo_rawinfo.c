#include <mars/mars.h>

#include <stdio.h>

int main(int argc, char* argv[])
{
    
	FILE *fp;
	raw2hop_obj *myRaw2hop;
	vector_float **hops;
	
	unsigned int hopSize;
	unsigned char nMics;
	unsigned char nBits;
	char * fileName;

	unsigned char iMic;
	unsigned int iSample;
	unsigned int nHops;

	float *powerValue;
	float *maxValue;
	float *minValue;

	if (argc != 5) {
		printf("Three argument expected: size of hop, number of channels, number of bits, raw file name.\n");
		exit(EXIT_FAILURE);
	}

	hopSize = (unsigned int) atoi(argv[1]);
	nMics = (unsigned char) atoi(argv[2]);
	nBits = (unsigned char) atoi(argv[3]);
	fileName = argv[4];

	hops = (vector_float **) malloc(sizeof(vector_float *) * nMics);
	for (iMic = 0; iMic < nMics; iMic++) {
		hops[iMic] = vector_float_malloc(hopSize);
	}

	powerValue = (float *) malloc(sizeof(float) * nMics);
	maxValue = (float *) malloc(sizeof(float) * nMics);
	minValue = (float *) malloc(sizeof(float) * nMics);
	for (iMic = 0; iMic < nMics; iMic++) {
		powerValue[iMic] = 0.0f;
		maxValue[iMic] = -INFINITY;
		minValue[iMic] = INFINITY;
	}


	myRaw2hop = raw2hop_construct(hopSize,nMics,nBits);

	fp = fopen(fileName,"rb");

	printf("Reading file... "); fflush(stdout);

	nHops = 0;

	while(raw2hop_process(myRaw2hop, fp, hops) == 0) {

		for (iMic = 0; iMic < nMics; iMic++) {

			for (iSample = 0; iSample < hopSize; iSample++) {

				powerValue[iMic] += (hops[iMic]->array[iSample] * hops[iMic]->array[iSample]);

				if (hops[iMic]->array[iSample] > maxValue[iMic]) {
					maxValue[iMic] = hops[iMic]->array[iSample];
				}
				if (hops[iMic]->array[iSample] < minValue[iMic]) {
					minValue[iMic] = hops[iMic]->array[iSample];
				}

			}

		}

		nHops++;

	}

	for (iMic = 0; iMic < nMics; iMic++) {

		powerValue[iMic] /= (float) (hopSize*nHops);

	}

	printf("[OK]\n");

	fclose(fp);

	raw2hop_destroy(myRaw2hop);

	for (iMic = 0; iMic < nMics; iMic++) {
		vector_float_free(hops[iMic]);
	}
	free((void *) hops);

	printf("Summary: \n");
	printf(" - nChannels: %d\n",nMics);
	printf(" - hopSize: %u\n",hopSize);
	printf(" - nHops: %u\n",nHops);
	printf(" - power:\n");
	for (iMic = 0; iMic < nMics; iMic++) {
		printf("     [%d]: %+1.6f\n",iMic,powerValue[iMic]);
	}
	printf(" - max:\n");
	for (iMic = 0; iMic < nMics; iMic++) {
		printf("     [%d]: %+1.6f\n",iMic,maxValue[iMic]);
	}
	printf(" - min:\n");
	for (iMic = 0; iMic < nMics; iMic++) {
		printf("     [%d]: %+1.6f\n",iMic,minValue[iMic]);
	}

    return 0;
}