#include <mars/mars.h>

#include <stdio.h>

int main(int argc, char* argv[])
{
    
	src_raw_obj * src_raw;
	msg_hops_obj * msg_hops;
	stft_obj * stft;
	msg_spectra_obj * msg_spectra;
    matrix_float * mics;
    matrix_float * points;
	ssl_obj * ssl;

    msg_pots_obj * msg_pots;
    snk_pots_obj * snk_pots;

	unsigned int hopSize;
	unsigned int frameSize;
	unsigned int halfFrameSize;
	unsigned char nMics;
	unsigned char nBits;

	char * rawFileName;
	char * potsFileName;

    unsigned int fS;
    float c;
    vector_unsignedint * levels;
    float sigma;
    unsigned int nMatches;
    float epsilon;
    unsigned int w;
    unsigned int L;
    float alphaS;
    float alphaD;
    float delta;
    float alphaP;

	unsigned char iMic;
	unsigned int iSample;
	unsigned int nHops;

	time_t start,end;
	float readingTime;
	float processingTime, signalTime, cpuUsage;

	float mic_x, mic_y, mic_z;

	if (argc != 3) {
		printf("Raw file name and pots file name expected.\n");
		exit(EXIT_FAILURE);
	}

	hopSize = 128;
	frameSize = 256;
	halfFrameSize = frameSize/2 + 1;
	nMics = 8;
	nBits = 16;
	rawFileName = argv[1];
	potsFileName = argv[2];

    mics = matrix_float_malloc(nMics, 3);

    mic_x = 0.1150f;
    mic_y = 0.1150f;
    mic_z = 0.1025f;

    mics->array[0][0] = +mic_x;
    mics->array[0][1] = -mic_y;
    mics->array[0][2] = +mic_z;
    mics->array[1][0] = -mic_x;
    mics->array[1][1] = -mic_y;
    mics->array[1][2] = +mic_z;
    mics->array[2][0] = -mic_x;
    mics->array[2][1] = +mic_y;
    mics->array[2][2] = +mic_z;
    mics->array[3][0] = +mic_x;
    mics->array[3][1] = +mic_y;
    mics->array[3][2] = +mic_z;
    mics->array[4][0] = +mic_x;
    mics->array[4][1] = -mic_y;
    mics->array[4][2] = -mic_z;    
    mics->array[5][0] = -mic_x;
    mics->array[5][1] = -mic_y;
    mics->array[5][2] = -mic_z;        
    mics->array[6][0] = -mic_x;
    mics->array[6][1] = +mic_y;
    mics->array[6][2] = -mic_z;        
    mics->array[7][0] = +mic_x;
    mics->array[7][1] = +mic_y;
    mics->array[7][2] = -mic_z;        
    // mics->array[8][0] = +mic_x;
    // mics->array[8][1] = -mic_y;
    // mics->array[8][2] = +mic_z;
    // mics->array[9][0] = -mic_x;
    // mics->array[9][1] = -mic_y;
    // mics->array[9][2] = +mic_z;
    // mics->array[10][0] = -mic_x;
    // mics->array[10][1] = +mic_y;
    // mics->array[10][2] = +mic_z;
    // mics->array[11][0] = +mic_x;
    // mics->array[11][1] = +mic_y;
    // mics->array[11][2] = +mic_z;
    // mics->array[12][0] = +mic_x;
    // mics->array[12][1] = -mic_y;
    // mics->array[12][2] = -mic_z;    
    // mics->array[13][0] = -mic_x;
    // mics->array[13][1] = -mic_y;
    // mics->array[13][2] = -mic_z;        
    // mics->array[14][0] = -mic_x;
    // mics->array[14][1] = +mic_y;
    // mics->array[14][2] = -mic_z;        
    // mics->array[15][0] = +mic_x;
    // mics->array[15][1] = +mic_y;
    // mics->array[15][2] = -mic_z;   
    // mics->array[16][0] = +mic_x;
    // mics->array[16][1] = -mic_y;
    // mics->array[16][2] = +mic_z;
    // mics->array[17][0] = -mic_x;
    // mics->array[17][1] = -mic_y;
    // mics->array[17][2] = +mic_z;
    // mics->array[18][0] = -mic_x;
    // mics->array[18][1] = +mic_y;
    // mics->array[18][2] = +mic_z;
    // mics->array[19][0] = +mic_x;
    // mics->array[19][1] = +mic_y;
    // mics->array[19][2] = +mic_z;
    // mics->array[20][0] = +mic_x;
    // mics->array[20][1] = -mic_y;
    // mics->array[20][2] = -mic_z;    
    // mics->array[21][0] = -mic_x;
    // mics->array[21][1] = -mic_y;
    // mics->array[21][2] = -mic_z;        
    // mics->array[22][0] = -mic_x;
    // mics->array[22][1] = +mic_y;
    // mics->array[22][2] = -mic_z;        
    // mics->array[23][0] = +mic_x;
    // mics->array[23][1] = +mic_y;
    // mics->array[23][2] = -mic_z;        
    // mics->array[24][0] = +mic_x;
    // mics->array[24][1] = -mic_y;
    // mics->array[24][2] = +mic_z;
    // mics->array[25][0] = -mic_x;
    // mics->array[25][1] = -mic_y;
    // mics->array[25][2] = +mic_z;
    // mics->array[26][0] = -mic_x;
    // mics->array[26][1] = +mic_y;
    // mics->array[26][2] = +mic_z;
    // mics->array[27][0] = +mic_x;
    // mics->array[27][1] = +mic_y;
    // mics->array[27][2] = +mic_z;
    // mics->array[28][0] = +mic_x;
    // mics->array[28][1] = -mic_y;
    // mics->array[28][2] = -mic_z;    
    // mics->array[29][0] = -mic_x;
    // mics->array[29][1] = -mic_y;
    // mics->array[29][2] = -mic_z;        
    // mics->array[30][0] = -mic_x;
    // mics->array[30][1] = +mic_y;
    // mics->array[30][2] = -mic_z;        
    // mics->array[31][0] = +mic_x;
    // mics->array[31][1] = +mic_y;
    // mics->array[31][2] = -mic_z;       

    fS = 16000;
    c = 343.0f;
    levels = vector_unsignedint_malloc(1);
    levels->array[0] = 4;
    //levels = vector_unsignedint_malloc(2);
    //levels->array[0] = 2;
    //levels->array[1] = 4;

    sigma = 5.0f;
    nMatches = 5;
    epsilon = 1E-20;
    w = 1;
    L = 150;
    alphaS = 0.8f;
    alphaD = 0.95f;
    delta = 5.0f;
    alphaP = 0.1f;

    msg_hops = msg_hops_construct(hopSize, nMics);
    stft = stft_construct(hopSize, frameSize, nMics);
    msg_spectra = msg_spectra_construct(frameSize, nMics);
    ssl = ssl_construct(mics, frameSize, fS, c, levels, sigma, nMatches, epsilon, w, L, alphaS, alphaD, delta, alphaP);
    msg_pots = msg_pots_construct();

    src_raw = src_raw_construct(hopSize, nMics, nBits, rawFileName);
    
    start = clock();
    printf("Reading file (1/2)... "); fflush(stdout);
    while(src_raw_process(src_raw, msg_hops) == 0);
    printf("[OK]\n");
    end = clock();
    
    src_raw_destroy(src_raw);

    readingTime = (float) ((end-start)/((float) CLOCKS_PER_SEC));

    src_raw = src_raw_construct(hopSize, nMics, nBits, rawFileName);
    snk_pots = snk_pots_construct(potsFileName, "xml");

    start = clock();

	printf("Reading file (2/2)... "); fflush(stdout);

	nHops = 0;

	while(src_raw_process(src_raw, msg_hops) == 0) {

        stft_process(stft, msg_hops, msg_spectra);
        ssl_process(ssl, msg_spectra, msg_pots);
        snk_pots_process(snk_pots, msg_pots);

		nHops++;

	}

	printf("[OK]\n");

	end = clock();

    processingTime = ((float) ((end-start)/((float) CLOCKS_PER_SEC))) - readingTime;
    signalTime = ((float) nHops*hopSize)/fS;
    cpuUsage = 100.0f * processingTime / signalTime;

    printf("Time ellapsed: %1.2f secs.\n",processingTime);
    printf("Signal duration: %1.2f secs.\n",signalTime);
    printf("CPU usage: %1.2f%%.\n",cpuUsage);

    snk_pots_destroy(snk_pots);
    src_raw_destroy(src_raw);

    msg_pots_destroy(msg_pots);
    ssl_destroy(ssl);
    msg_spectra_destroy(msg_spectra);
    stft_destroy(stft);
    msg_hops_destroy(msg_hops);

    return 0;
}