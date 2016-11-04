#include <mars/mars.h>

#include <stdio.h>

int main(int argc, char* argv[])
{
    
	src_raw_obj * src_raw;
	msg_hops_obj * msg_hops;
	
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

	powerValue = (float *) malloc(sizeof(float) * nMics);
	maxValue = (float *) malloc(sizeof(float) * nMics);
	minValue = (float *) malloc(sizeof(float) * nMics);
	for (iMic = 0; iMic < nMics; iMic++) {
		powerValue[iMic] = 0.0f;
		maxValue[iMic] = -INFINITY;
		minValue[iMic] = INFINITY;
	}

    msg_hops = msg_hops_construct(hopSize, nMics);
	src_raw = src_raw_construct(hopSize, nMics, nBits, fileName);

	printf("Reading file... "); fflush(stdout);

	nHops = 0;

	while(src_raw_process(src_raw, msg_hops) == 0) {

		for (iMic = 0; iMic < nMics; iMic++) {

			for (iSample = 0; iSample < hopSize; iSample++) {

				powerValue[iMic] += (msg_hops->samples[iMic][iSample] * msg_hops->samples[iMic][iSample]);

				if (msg_hops->samples[iMic][iSample] > maxValue[iMic]) {
					maxValue[iMic] = msg_hops->samples[iMic][iSample];
				}
				if (msg_hops->samples[iMic][iSample] < minValue[iMic]) {
					minValue[iMic] = msg_hops->samples[iMic][iSample];
				}

			}

		}

		nHops++;

	}

	for (iMic = 0; iMic < nMics; iMic++) {

		powerValue[iMic] /= (float) (hopSize*nHops);

	}

	printf("[OK]\n");

    src_raw_destroy(src_raw);
    msg_hops_destroy(msg_hops);

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