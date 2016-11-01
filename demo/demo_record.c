#include <mars/mars.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, char* argv[])
{

    eightsnd2hop_obj *myEightsnd2hop;
    vector_float **hops;
    hop2raw_obj *myHop2raw;

    unsigned int hopSize;
    unsigned int nMics;
    unsigned char nBits;
    unsigned int sampleRate;

    unsigned int iMic;

    char *sndCardName;
    char *fileName;

    if (argc != 3) {
        printf("Two arguments expected: sound card name and raw file name.\n");
        exit(EXIT_FAILURE);
    }

    hopSize = 512;
    nMics = 8;
    nBits = 16;
    sampleRate = 48000;
    
    sndCardName = argv[1];
    fileName = argv[2];

    myEightsnd2hop = eightsnd2hop_construct(hopSize, sampleRate, sndCardName);
    myHop2raw = hop2raw_construct(hopSize, nMics, nBits, fileName);

	hops = (vector_float **) malloc(sizeof(vector_float *) * nMics);
	for (iMic = 0; iMic < nMics; iMic++) {
		hops[iMic] = vector_float_malloc(hopSize);
	}

	while(1) {

    	eightsnd2hop_process(myEightsnd2hop, hops);
		hop2raw_process(myHop2raw, hops);

	}

	printf("Out of process\n");
	while(1);

	for (iMic = 0; iMic < nMics; iMic++) {
		vector_float_free(hops[iMic]);
	}
	free((void *) hops);

    hop2raw_destroy(myHop2raw);
    eightsnd2hop_destroy(myEightsnd2hop);

    return 0;
}