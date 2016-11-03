#include <mars/mars.h>

#include <stdio.h>

int main(int argc, char* argv[])
{
    
	raw2hop_obj *raw2hop;
	matrix_float *hops;
	
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
		printf("Four arguments expected: size of hop, number of channels, number of bits, raw file name.\n");
		exit(EXIT_FAILURE);
	}

	hopSize = (unsigned int) atoi(argv[1]);
	nMics = (unsigned char) atoi(argv[2]);
	nBits = (unsigned char) atoi(argv[3]);
	fileName = argv[4];

    hops = matrix_float_malloc(nMics, hopSize);

	powerValue = (float *) malloc(sizeof(float) * nMics);
	maxValue = (float *) malloc(sizeof(float) * nMics);
	minValue = (float *) malloc(sizeof(float) * nMics);
	for (iMic = 0; iMic < nMics; iMic++) {
		powerValue[iMic] = 0.0f;
		maxValue[iMic] = -INFINITY;
		minValue[iMic] = INFINITY;
	}

	raw2hop = raw2hop_construct(hopSize,nMics,nBits,fileName);

	printf("Reading file... "); fflush(stdout);

	nHops = 0;

	while(raw2hop_process(raw2hop, hops) == 0) {

		for (iMic = 0; iMic < nMics; iMic++) {

			for (iSample = 0; iSample < hopSize; iSample++) {

				powerValue[iMic] += (hops->array[iMic][iSample] * hops->array[iMic][iSample]);

				if (hops->array[iMic][iSample] > maxValue[iMic]) {
					maxValue[iMic] = hops->array[iMic][iSample];
				}
				if (hops->array[iMic][iSample] < minValue[iMic]) {
					minValue[iMic] = hops->array[iMic][iSample];
				}

			}

		}

		nHops++;

	}

	for (iMic = 0; iMic < nMics; iMic++) {

		powerValue[iMic] /= (float) (hopSize*nHops);

	}

	printf("[OK]\n");

	raw2hop_destroy(raw2hop);
	matrix_float_free(hops);

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