
    #include "ssl.h"

    ssl_obj * ssl_construct(const matrix_float * mics, const unsigned int frameSize, const unsigned int fS, const float c, const vector_unsignedint * levels, const float sigma, const unsigned int nMatches, const float epsilon, const unsigned int w, const unsigned int L, const float alphaS, const float alphaD, const float delta, const float alphaP) {

        ssl_obj * obj;

        unsigned int iLevel;
        unsigned int iMic;
        unsigned int iPair;
        unsigned int iSample;
        matrix_float * tdoaFloat;
        matrix_signedint * tdoaSignedInt;

        matrix_float ** tdoasFloat;

        obj = (ssl_obj *) malloc(sizeof(ssl_obj));

        obj->frameSize = frameSize;
        obj->halfFrameSize = frameSize/2 + 1;
        obj->nMics = mics->nRows;
        obj->nPairs = pair_nPairs(obj->nMics);
        obj->nLevels = levels->nElements;
        obj->fS = fS;
        obj->c = c;
        obj->epsilon = epsilon;

        obj->w = w;
        obj->L = L;
        obj->alphaS = alphaS;
        obj->alphaD = alphaD;
        obj->delta = delta;
        obj->alphaP = alphaP;

        obj->mics = matrix_float_clone(mics);
        obj->points = array_1d_malloc(obj->nLevels);
        obj->tdoas = array_1d_malloc(obj->nLevels);
        obj->invmap = array_1d_malloc(obj->nLevels);

        tdoasFloat = (matrix_float **) malloc(sizeof(matrix_float *) * obj->nLevels);

        for (iLevel = 0; iLevel < obj->nLevels; iLevel++) {

            obj->points->ptr[iLevel] = sphere_generate(levels->array[iLevel], 1.0f);

            tdoasFloat[iLevel] = tdoa_delay(obj->points->ptr[iLevel], obj->mics, fS, c);
            tdoaSignedInt = tdoa_round(tdoasFloat[iLevel]);    
            obj->tdoas->ptr[iLevel] = tdoa_wrap(tdoaSignedInt, frameSize);
            matrix_signedint_free(tdoaSignedInt);
            
        }

        obj->invmap->ptr[0] = map_generate_reverse_init(obj->points->ptr[0]);

        for (iLevel = 1; iLevel < obj->nLevels; iLevel++) {            

            obj->invmap->ptr[iLevel] = map_generate_reverse(tdoasFloat[iLevel-1], tdoasFloat[iLevel], sigma, nMatches);

        }

        for (iLevel = 0; iLevel < obj->nLevels; iLevel++) {
        	matrix_float_free(tdoasFloat[iLevel]);
        }
        free((void *) tdoasFloat);

        obj->freqs = array_1d_malloc(obj->nMics);
        obj->freq2mcra = array_1d_malloc(obj->nMics);
        obj->mcras = array_1d_malloc(obj->nMics);
        obj->mcra2mask = array_1d_malloc(obj->nMics);
        obj->masks = array_1d_malloc(obj->nMics);
        obj->freq2phase = array_1d_malloc(obj->nMics);
        obj->phases = array_1d_malloc(obj->nMics);

        for (iMic = 0; iMic < obj->nMics; iMic++) {

            obj->freqs->ptr[iMic] = vector_float_malloc(obj->halfFrameSize*2);
            obj->freq2mcra->ptr[iMic] = freq2mcra_construct(obj->frameSize, obj->w, obj->L, obj->alphaS, obj->alphaD, obj->delta);
            obj->mcras->ptr[iMic] = vector_float_malloc(obj->halfFrameSize);
            obj->mcra2mask->ptr[iMic] = mcra2mask_construct(obj->frameSize, obj->alphaP, obj->epsilon);
            obj->masks->ptr[iMic] = vector_float_malloc(obj->halfFrameSize);
            obj->freq2phase->ptr[iMic] = freq2phase_construct(frameSize, epsilon);
            obj->phases->ptr[iMic] = vector_float_malloc(obj->halfFrameSize*2);

        }
        
        obj->phase2phasex = array_1d_malloc(obj->nPairs);
        obj->phasexs = array_1d_malloc(obj->nPairs);
        obj->phasex2xcorr = array_1d_malloc(obj->nPairs);
        obj->xcorrs = array_1d_malloc(obj->nPairs);

        for (iPair = 0; iPair < obj->nPairs; iPair++) {

            obj->phase2phasex->ptr[iPair] = phase2phasex_construct(frameSize);
            obj->phasexs->ptr[iPair] = vector_float_malloc(obj->halfFrameSize*2);
            obj->phasex2xcorr->ptr[iPair] = phasex2xcorr_construct(frameSize);
            obj->xcorrs->ptr[iPair] = vector_float_malloc(frameSize);

        }

        obj->xcorr2aimg = array_1d_malloc(obj->nLevels);
        obj->aimgs = array_1d_malloc(obj->nLevels);

        for (iLevel = 0; iLevel < obj->nLevels; iLevel++) {
        	obj->xcorr2aimg->ptr[iLevel] = xcorr2aimg_construct(frameSize, obj->nMics, ((matrix_float *) obj->points->ptr[iLevel])->nRows);
        	obj->aimgs->ptr[iLevel] = vector_float_malloc(((matrix_float *) obj->points->ptr[iLevel])->nRows);
        }

        return obj;

    }

    void ssl_destroy(ssl_obj * obj) {

        

    }

    int ssl_process(ssl_obj * obj, const msg_spectra_obj * spectra, msg_pots_obj * pots) {

        unsigned int iMic;
        unsigned int iMic1;
        unsigned int iMic2;
        unsigned int iPair;
        unsigned int iSample;
        unsigned int iLevel;
        unsigned int iScan;

        unsigned int iPoint;
        float vPoint;

        for (iMic = 0; iMic < obj->nMics; iMic++) {

            for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

                ((vector_float *) obj->freqs->ptr[iMic])->array[iSample*2+0] = spectra->samples[iMic][iSample*2+0];
                ((vector_float *) obj->freqs->ptr[iMic])->array[iSample*2+1] = spectra->samples[iMic][iSample*2+1];

            }

            freq2mcra_process(obj->freq2mcra->ptr[iMic], obj->freqs->ptr[iMic], obj->mcras->ptr[iMic]);
            mcra2mask_process(obj->mcra2mask->ptr[iMic], obj->freqs->ptr[iMic], obj->mcras->ptr[iMic], obj->masks->ptr[iMic]);
            freq2phase_process(obj->freq2phase->ptr[iMic], obj->freqs->ptr[iMic], obj->masks->ptr[iMic], obj->phases->ptr[iMic]);

        }

        for (iMic1 = 0; iMic1 < obj->nMics; iMic1++) {

            for (iMic2 = (iMic1+1); iMic2 < obj->nMics; iMic2++) {

                iPair = pair_iPair(obj->nMics, iMic1, iMic2);

                phase2phasex_process(obj->phase2phasex->ptr[iPair], obj->phases->ptr[iMic1], obj->phases->ptr[iMic2], obj->phasexs->ptr[iPair]);
                phasex2xcorr_process(obj->phasex2xcorr->ptr[iPair], obj->phasexs->ptr[iPair], obj->xcorrs->ptr[iPair]);

            }

        }

        iPoint = 0;

        for (iLevel = 0; iLevel < obj->nLevels; iLevel++) {

            xcorr2aimg_process(obj->xcorr2aimg->ptr[iLevel], obj->tdoas->ptr[iLevel], obj->invmap->ptr[iLevel], iPoint, (const vector_float **) obj->xcorrs->ptr, obj->aimgs->ptr[iLevel]);
            iPoint = minmax_max_float(((vector_float *) obj->aimgs->ptr[iLevel])->array, ((vector_float *) obj->aimgs->ptr[iLevel])->nElements);   

        }

        vPoint = ((vector_float *) obj->aimgs->ptr[obj->nLevels-1])->array[iPoint];

        pots->samples[0] = ((matrix_float *) obj->points->ptr[obj->nLevels-1])->array[iPoint][0];
        pots->samples[1] = ((matrix_float *) obj->points->ptr[obj->nLevels-1])->array[iPoint][1];
        pots->samples[2] = ((matrix_float *) obj->points->ptr[obj->nLevels-1])->array[iPoint][2];
        pots->samples[3] = vPoint;

        pots->id = spectra->id;

    }