    
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

    void freq2freq_process_phasor_single(freq2freq_obj * obj, const freq_obj * freq, freq_obj * phasor) {

        unsigned int iSample;
        float real, imag;
        float magnitude;

        for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

            real = freq->array[iSample*2+0];
            imag = freq->array[iSample*2+1];
            magnitude = sqrtf(real*real+imag*imag) + obj->epsilon;

            phasor->array[iSample*2+0] = real / magnitude;
            phasor->array[iSample*2+1] = imag / magnitude;

        }

    }

    void freq2freq_process_product_single(freq2freq_obj * obj, const freq_obj * phasor1, const freq_obj * phasor2, freq_obj * phasor12) {

        unsigned int iSample;
        float real1, imag1;
        float real2, imag2;

        for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

            real1 = phasor1->array[iSample*2+0];
            imag1 = phasor1->array[iSample*2+1];
            real2 = phasor2->array[iSample*2+0];
            imag2 = phasor2->array[iSample*2+1];

            phasor12->array[iSample*2+0] = real1*real2+imag1*imag2;
            phasor12->array[iSample*2+1] = imag1*real2-imag2*real1;

        }

    }

    void freq2freq_process_smooth_single(freq2freq_obj * obj, const freq_obj * phasor, freq_obj * smooth) {

        unsigned int iSample;

        for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

            smooth->array[iSample*2+0] = (1-obj->alpha) * smooth->array[iSample*2+0] + obj->alpha * phasor->array[iSample*2+0];
            smooth->array[iSample*2+1] = (1-obj->alpha) * smooth->array[iSample*2+1] + obj->alpha * phasor->array[iSample*2+1];

        }        

    }

    void freq2freq_process_phasor_many(freq2freq_obj * obj, const freqs_obj * freqs, freqs_obj * phasors) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < freqs->nSignals; iSignal++) {
        	freq2freq_process_phasor_single(obj, freqs->array[iSignal], phasors->array[iSignal]);
        }

    }

    void freq2freq_process_product_many(freq2freq_obj * obj, const freqs_obj * phasors1, const freqs_obj * phasors2, freqs_obj * phasors12) {

        unsigned int iSignal1;
        unsigned int iSignal2;
        unsigned int iSignal;

        iSignal = 0;

        for (iSignal1 = 0; iSignal1 < phasors1->nSignals; iSignal1++) {

            for (iSignal2 = (iSignal1+1); iSignal2 < phasors2->nSignals; iSignal2++) {

                freq2freq_process_product_single(obj, phasors1->array[iSignal1], phasors2->array[iSignal2], phasors12->array[iSignal]);

                iSignal++;

            }

        }

    }

    void freq2freq_process_smooth_many(freq2freq_obj * obj, const freqs_obj * phasors, freqs_obj * smooths) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < phasors->nSignals; iSignal++) {
        	freq2freq_process_smooth_single(obj, phasors->array[iSignal], smooths->array[iSignal]);
        }

    }