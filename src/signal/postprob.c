
    #include "postprob.h"

    postprob_obj * postprob_construct_zero(const unsigned int nPots) {

        postprob_obj * obj;
        unsigned int iPot;

        obj = (postprob_obj *) malloc(sizeof(postprob_obj));

        obj->nPots = nPots;
        obj->probs = (float *) malloc(sizeof(float) * nPots);

        for (iPot = 0; iPot < nPots; iPot++) {
            obj->probs[iPot] = 0.0f;
        }

        obj->probTotal = 0.0f;

        return obj;

    }

    void postprob_destroy(postprob_obj * obj) {

        free((void *) obj->probs);
        free((void *) obj);

    }

    void postprob_printf(const postprob_obj * obj) {

        unsigned int iPot;

        for (iPot = 0; iPot < obj->nPots; iPot++) {

            printf("(%02u): %+1.3f",iPot,obj->probs[iPot]);

            if (iPot != (obj->nPots - 1)) {
                printf(" - ");
            }

        }       

        printf(" > %f",obj->probTotal);

        printf("\n");

    }


    postprobs_obj * postprobs_construct_zero(const unsigned int nPots, const unsigned int nTracks) {

        postprobs_obj * obj;
        unsigned int iTrack;

        obj = (postprobs_obj *) malloc(sizeof(postprobs_obj));

        obj->nTracks = nTracks;

        obj->p_track = (postprob_obj **) malloc(sizeof(postprob_obj *) * nTracks);

        for (iTrack = 0; iTrack < nTracks; iTrack++) {

            obj->p_track[iTrack] = postprob_construct_zero(nPots);

        }

        obj->p_new = postprob_construct_zero(nPots);

        return obj;

    }

    void postprobs_destroy(postprobs_obj * obj) {

        unsigned int iTrack;

        for (iTrack = 0; iTrack < obj->nTracks; iTrack++) {

            postprob_destroy(obj->p_track[iTrack]);

        }

        free((void *) obj->p_track);

        postprob_destroy(obj->p_new);

    }

    void postprobs_printf(const postprobs_obj * obj) {

        unsigned int iTrack;

        postprob_printf(obj->p_new);

        for (iTrack = 0; iTrack < obj->nTracks; iTrack++) {
            postprob_printf(obj->p_track[iTrack]);
        }

    }