    #include "pcm.h"

    float pcm_signed08bits2normalized(const signed char sample) {

    	return (((float) sample) / (fabs(SCHAR_MIN)));

    }

    float pcm_signed16bits2normalized(const signed short sample) {
    	
        return (((float) sample) / (fabs(SHRT_MIN)));

    }

    float pcm_signed32bits2normalized(const signed int sample) {
    	
        return (((float) sample) / (fabs(INT_MIN)));

    }

    signed char pcm_normalized2signed08bits(const float sample) {
    	
        float sampleCrop;

        if (sample > (fabs(SCHAR_MAX)/fabs(SCHAR_MIN))) {
        	sampleCrop = (fabs(SCHAR_MAX)/fabs(SCHAR_MIN));
        }
        else if (sample < -1.0f) {
        	sampleCrop = -1.0f;
        }
        else {
        	sampleCrop = sample;
        }

        return ((signed char) (sampleCrop*fabs(SCHAR_MIN)));

    }

    signed short pcm_normalized2signed16bits(const float sample) {

        float sampleCrop;

        if (sample > (fabs(SHRT_MAX)/fabs(SHRT_MIN))) {
        	sampleCrop = (fabs(SHRT_MAX)/fabs(SHRT_MIN));
        }
        else if (sample < -1.0f) {
        	sampleCrop = -1.0f;
        }
        else {
        	sampleCrop = sample;
        }

        return ((signed short) (sampleCrop*fabs(SHRT_MIN)));
    	
    }

    signed int pcm_normalized2signed32bits(const float sample) {

        float sampleCrop;

        if (sample > (fabs(INT_MAX)/fabs(INT_MIN))) {
        	sampleCrop = (fabs(INT_MAX)/fabs(INT_MIN));
        }
        else if (sample < -1.0f) {
        	sampleCrop = -1.0f;
        }
        else {
        	sampleCrop = sample;
        }

        return ((signed int) (sampleCrop*fabs(INT_MIN)));
    	
    }