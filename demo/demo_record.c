#include <mars/mars.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, char* argv[])
{

    eightsnd2hop_obj *eightsnd2hop;
    matrix_float *hops;
    hop2raw_obj *hop2raw;

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

    eightsnd2hop = eightsnd2hop_construct(hopSize, sampleRate, sndCardName);
    hop2raw = hop2raw_construct(hopSize, nMics, nBits, fileName);

	hops = matrix_float_malloc(nMics,hopSize);

	while(1) {

    	eightsnd2hop_process(eightsnd2hop, hops);
		hop2raw_process(hop2raw, hops);

	}


    matrix_float_free(hops);

    hop2raw_destroy(hop2raw);
    eightsnd2hop_destroy(eightsnd2hop);

    return 0;
}