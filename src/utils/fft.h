#ifndef __MARS_UTILS_FFT
#define __MARS_UTILS_FFT

	#include <fftw3.h>
	#include <stdlib.h>

	typedef struct fft_obj {

		unsigned int frameSize;
		unsigned int halfFrameSize;
		fftwf_plan R2C;
		fftwf_plan C2R;
		float * realArray;
		fftwf_complex * complexArray;

	} fft_obj;

	fft_obj * fft_construct(const unsigned int size);

	void fft_destroy(fft_obj * obj);

	void fft_r2c(fft_obj * obj, const float * in, float * out);

	void fft_c2r(fft_obj * obj, const float * in, float * out);

#endif