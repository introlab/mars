	#include <mars/mars.h>

	#include <stdio.h>
	#include <stdlib.h>
	#include <time.h>
	#include <math.h>

	int main(int argc, char* argv[])
	{
	    
		const unsigned char L = 10;


		fft_obj *myFFT;
		float *arrayIn, *arrayOut;
		
		unsigned char l;
		unsigned int i, I, n, N;

		unsigned int Ns[] = {32,64,128,256,512,1024,2048,4096,8192,16384};
		unsigned int Is[] = {5000000,2000000,1000000,500000,200000,100000,50000,20000,10000,5000};

		clock_t before, after;
		float duration, durationPerFFT;
		unsigned int nFFTPerSec;

		for (l = 0; l < L; l++) {

			N = Ns[l];
			I = Is[l];

			myFFT = fft_construct(N);
			arrayIn = (float *) malloc(sizeof(float) * N);
			arrayOut = (float *) malloc(sizeof(float) * ((N/2)+1) * 2);

			for (n = 0; n < N; n++) {

				arrayIn[n] = ((float) rand()) / ((float) RAND_MAX) - 0.5f;

			}

			before = clock();

			for (i = 0; i < I; i++) {

				fft_r2c(myFFT, (const float *) arrayIn, arrayOut);

			}

			after = clock();

			duration = ((float) (after-before)) / ((float) CLOCKS_PER_SEC);
			durationPerFFT =  duration / ((float) I);
			nFFTPerSec = (unsigned int) roundf(1.0f / durationPerFFT);

			printf("Processing time for real fft (N = %u): %u ffts/sec\n",N,nFFTPerSec);

			free((void *) arrayIn);
			free((void *) arrayOut);
			fft_destroy(myFFT);

		}

	    return 0;
	}