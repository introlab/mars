    
    #include "distribution.h"

    float distribution_normal(const float x, const float mu, const float sigma) {

        float diff;
        float y;

        diff = x - mu;

        y = (1.0f/(sqrtf(2*M_PI)*sigma)) * exp(-1.0f * diff*diff/(2*sigma*sigma));

        return y;

    }
