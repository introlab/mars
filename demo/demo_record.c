#include <mars/mars.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, char* argv[])
{

    src_eightsnd_obj * src_eightsnd;
    msg_hops_obj * msg_hops;
    snk_raw_obj * snk_raw;

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

    src_eightsnd = src_eightsnd_construct(hopSize, sampleRate, sndCardName);
    msg_hops = msg_hops_construct(hopSize, nMics);
    snk_raw = snk_raw_construct(hopSize, nMics, nBits, fileName);

	while(1) {

    	src_eightsnd_process(src_eightsnd, msg_hops);
        snk_raw_process(snk_raw, msg_hops);

	}

    msg_hops_destroy(msg_hops);
    
    snk_raw_destroy(snk_raw);
    src_eightsnd_destroy(src_eightsnd);

    return 0;
}