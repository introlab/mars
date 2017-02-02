
    #include "coherence.h"

    coherence_obj * coherence_construct_zero(const unsigned int S) {

        coherence_obj * obj;
        unsigned int iS;

        obj = (coherence_obj *) malloc(sizeof(coherence_obj));

        obj->S = S;
        obj->probs = (float *) malloc(sizeof(float) * S);

        for (iS = 0; iS < S; iS++) {
            obj->probs[iS] = 0.0f;
        }

        return obj;

    }

    void coherence_destroy(coherence_obj * obj) {

        free((void *) obj->probs);
        free((void *) obj);

    }

    coherences_obj * coherences_construct_zero(const unsigned int S, const unsigned int T) {

        coherences_obj * obj;
        unsigned int iSignal;

        obj = (coherences_obj *) malloc(sizeof(coherences_obj));

        obj->nSignals = T;
        obj->array = (coherence_obj **) malloc(sizeof(coherence_obj *) * T);

        for (iSignal = 0; iSignal < T; iSignal++) {

            obj->array[iSignal] = coherence_construct_zero(S);

        }

        return obj;

    }

    void coherences_destroy(coherences_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
        	coherence_destroy(obj->array[iSignal]);
        }

        free((void *) obj->array);
        free((void *) obj);

    }

    void coherences_printf(const coherences_obj * obj) {

        unsigned int iS;
        unsigned int iT;

        for (iT = 0; iT < obj->nSignals; iT++) {

            printf("(%02u): ",iT);

            for (iS = 0; iS < obj->array[iT]->S; iS++) {

                printf("%+1.3e ",obj->array[iT]->probs[iS]);

            }

            printf("\n");

        }

    }