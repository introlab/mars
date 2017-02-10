    
    #include "freq2freq.h"

    freq2freq_obj * freq2freq_construct_zero(const unsigned int halfFrameSize, const float epsilon, const float alpha) {

        freq2freq_obj * obj;

        obj = (freq2freq_obj *) malloc(sizeof(freq2freq_obj));

        obj->halfFrameSize = halfFrameSize;
        obj->epsilon = epsilon;
        obj->alpha = alpha;

        return obj;

    }

    void freq2freq_destroy(freq2freq_obj * obj) {

        free((void *) obj);

    }

    void freq2freq_process_phasor(freq2freq_obj * obj, const freqs_obj * freqs, freqs_obj * phasors) {

        unsigned int iSignal, iSample;
        float real, imag;
        float magnitude;        

        for (iSignal = 0; iSignal < freqs->nSignals; iSignal++) {

            for (iSample = 0; iSample < freqs->halfFrameSize; iSample++) {

                real = freqs->array[iSignal * obj->halfFrameSize * 2 + iSample * 2 + 0];
                imag = freqs->array[iSignal * obj->halfFrameSize * 2 + iSample * 2 + 1];
                magnitude = sqrtf(real*real+imag*imag) + obj->epsilon;

                phasors->array[iSignal * obj->halfFrameSize * 2 + iSample * 2 + 0] = real / magnitude;
                phasors->array[iSignal * obj->halfFrameSize * 2 + iSample * 2 + 1] = imag / magnitude;

            }

        }

    }

    void freq2freq_process_product(freq2freq_obj * obj, const freqs_obj * phasors1, const freqs_obj * phasors2, freqs_obj * phasors12) {

        unsigned int iSignal1, iSignal2, iSignal12, iSample;
        float real1, imag1;
        float real2, imag2;

        iSignal12 = 0;

        for (iSignal1 = 0; iSignal1 < phasors1->nSignals; iSignal1++) {

            for (iSignal2 = (iSignal1+1); iSignal2 < phasors2->nSignals; iSignal2++) {

                for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

                    real1 = phasors1->array[iSignal1 * obj->halfFrameSize * 2 + iSample * 2 + 0];
                    imag1 = phasors1->array[iSignal1 * obj->halfFrameSize * 2 + iSample * 2 + 1];
                    real2 = phasors2->array[iSignal2 * obj->halfFrameSize * 2 + iSample * 2 + 0];
                    imag2 = phasors2->array[iSignal2 * obj->halfFrameSize * 2 + iSample * 2 + 1];

                    phasors12->array[iSignal12 * obj->halfFrameSize * 2 + iSample * 2 + 0] = real1 * real2 + imag1 * imag2;
                    phasors12->array[iSignal12 * obj->halfFrameSize * 2 + iSample * 2 + 1] = imag1 * real2 - imag2 * real1;                    

                }

                iSignal12++;

            }

        }

    }

    void freq2freq_process_smooth(freq2freq_obj * obj, const freqs_obj * phasors, freqs_obj * smooths) {

        unsigned int iSignal;
        unsigned int iSample;
        float smooth;
        float phasor;

        for (iSignal = 0; iSignal < phasors->nSignals; iSignal++) {

            for (iSample = 0; iSample < obj->halfFrameSize * 2; iSample++) {

                smooth = smooths->array[iSignal * obj->halfFrameSize * 2 + iSample];
                phasor = phasors->array[iSignal * obj->halfFrameSize * 2 + iSample];

                smooth = (1-obj->alpha) * smooth + obj->alpha * phasor;

                smooths->array[iSignal * obj->halfFrameSize * 2 + iSample] = smooth;

            }

        }

    }
