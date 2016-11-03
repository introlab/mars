
    #include "window.h"

    #include <math.h>

    vector_float * window_hann(const unsigned int frameSize) {

        unsigned int iSample;
        vector_float * window;

        window = vector_float_malloc(frameSize);

        if ( frameSize == 1 ) {

            window->array[0] = 1.0f;
                        
        }
        else {
            
            for ( iSample = 0; iSample < frameSize; iSample++ ) {
                
                window->array[iSample] = 0.5f * ( 1.0f - cosf( 2 * M_PI * ( (float) iSample ) / ( (float) ( frameSize - 1 ) ) ) );
                                
            }
            
        }

        return window;

    }