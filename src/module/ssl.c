
    #include "ssl.h"

    ssl_obj * ssl_construct(const matrix_float * mics, const unsigned int frameSize, const unsigned int fS, const float c, const unsigned int bufferSize, const unsigned int bufferDelta, const vector_unsignedint * levels, const vector_unsignedint * deltas, const float sigma, const unsigned int nMatches, const float epsilon ) {

        ssl_obj * obj;

        unsigned int iLevel;
        unsigned int iMic;
        unsigned int iPair;
        unsigned int iSample;
        matrix_float * tdoaFloat;
        matrix_signedint * tdoaSignedInt;

        matrix_float ** tdoasFloat;
        matrix_signedint ** tdoasMinMax;

        signed int tdoaValue;
        signed int tdoaMin;
        signed int tdoaMax;
        
        unsigned int indexSorted;
        unsigned int deltaPrev;

        obj = (ssl_obj *) malloc(sizeof(ssl_obj));

        // Copy parameters

        obj->frameSize = frameSize;
        obj->halfFrameSize = frameSize/2 + 1;
        obj->bufferSize = bufferSize;
        obj->bufferDelta = bufferDelta;
        obj->nMics = mics->nRows;
        obj->nPairs = pair_nPairs(obj->nMics);
        obj->nLevels = levels->nElements;
        obj->fS = fS;
        obj->c = c;
        obj->epsilon = epsilon;
        obj->bValue = 0;
        obj->vPointPrev = 0.0f;
        obj->iPointPrev = 0;

        obj->mics = matrix_float_clone(mics);
        obj->points = array_1d_malloc(obj->nLevels);
        obj->tdoas = array_1d_malloc(obj->nLevels);
        obj->invmap = array_1d_malloc(obj->nLevels);

        // Generate TDOAs and mapping between various levels

        tdoasFloat = (matrix_float **) malloc(sizeof(matrix_float *) * obj->nLevels);
        tdoasMinMax = (matrix_signedint **) malloc(sizeof(matrix_signedint *) * obj->nLevels);
        
        for (iLevel = 0; iLevel < obj->nLevels; iLevel++) {

            obj->points->ptr[iLevel] = sphere_generate(levels->array[iLevel], 1.0f);

            tdoasFloat[iLevel] = tdoa_delay(obj->points->ptr[iLevel], obj->mics, fS, c);
            tdoaSignedInt = tdoa_round(tdoasFloat[iLevel]);    
            obj->tdoas->ptr[iLevel] = tdoa_wrap(tdoaSignedInt, frameSize);
        
            tdoasMinMax[iLevel] = matrix_signedint_malloc(obj->nPairs, 2);

            for (iPair = 0; iPair < obj->nPairs; iPair++) {

                 tdoaMin = tdoaSignedInt->array[0][iPair];
                 tdoaMax = tdoaSignedInt->array[0][iPair];

                 for (iSample = 1; iSample < tdoaSignedInt->nRows; iSample++) {
                     
                     tdoaValue = tdoaSignedInt->array[iSample][iPair];

                     if (tdoaValue > tdoaMax) {
                         tdoaMax = tdoaValue;
                     }

                     if (tdoaValue < tdoaMin) {
                         tdoaMin = tdoaValue;
                     }

                 }

                 tdoasMinMax[iLevel]->array[iPair][0] = tdoaMin;
                 tdoasMinMax[iLevel]->array[iPair][1] = tdoaMax;

            }
            
        }       

        obj->invmap->ptr[0] = map_generate_reverse_init(obj->points->ptr[0]);

        for (iLevel = 1; iLevel < obj->nLevels; iLevel++) {            

            obj->invmap->ptr[iLevel] = map_generate_reverse(tdoasFloat[iLevel-1], tdoasFloat[iLevel], sigma, nMatches);

        }

        for (iLevel = 0; iLevel < obj->nLevels; iLevel++) {
        	matrix_float_free(tdoasFloat[iLevel]);
        }
        free((void *) tdoasFloat);

        // Compute the deltas to filter xcorr and retrieve max, and sort them to perform optimal operations later

        obj->deltaSortValue = vector_unsignedint_malloc(obj->nLevels);
        obj->deltaSortIndex = vector_unsignedint_malloc(obj->nLevels);
 
        sort_ascend_unsignedint(obj->deltaSortValue->array, obj->deltaSortIndex->array, deltas->array, obj->nLevels);

        obj->deltaDiff = vector_unsignedint_malloc(obj->nLevels);

        deltaPrev = 0;

        for (iLevel = 0; iLevel < obj->nLevels; iLevel++) {
            
            indexSorted = obj->deltaSortIndex->array[iLevel];
            obj->deltaDiff->array[indexSorted] = deltas->array[indexSorted] - deltaPrev;
            deltaPrev = deltas->array[indexSorted];

        }

        // Generate all signals and systems

        obj->freqs = array_1d_malloc(obj->nMics);
        obj->phasors = array_1d_malloc(obj->nMics);
        obj->phases = array_1d_malloc(obj->nMics);

        for (iMic = 0; iMic < obj->nMics; iMic++) {

            obj->freqs->ptr[iMic] = vector_float_malloc(obj->halfFrameSize*2);
            obj->phasors->ptr[iMic] = phasor_construct(frameSize, epsilon);
            obj->phases->ptr[iMic] = vector_float_malloc(obj->halfFrameSize*2);

        }
        
        obj->crossphasors = array_1d_malloc(obj->nPairs);
        obj->phasexs = array_1d_malloc(obj->nPairs);
        obj->bufferphasors = array_1d_malloc(obj->nPairs);
        obj->phasexsmooths = array_1d_malloc(obj->nPairs);
        obj->xcorrs = array_1d_malloc(obj->nPairs);
        obj->xcorrsoriginal = array_1d_malloc(obj->nPairs);

        for (iPair = 0; iPair < obj->nPairs; iPair++) {

            obj->crossphasors->ptr[iPair] = crossphasor_construct(frameSize);
            obj->phasexs->ptr[iPair] = vector_float_malloc(obj->halfFrameSize*2);
            obj->bufferphasors->ptr[iPair] = bufferphasor_construct(frameSize, obj->bufferSize);
            obj->phasexsmooths->ptr[iPair] = vector_float_malloc(obj->halfFrameSize*2);
            obj->xcorrs->ptr[iPair] = xcorr_construct(frameSize);
            obj->xcorrsoriginal->ptr[iPair] = vector_float_malloc(frameSize);

        }

        obj->maxxcorrs = array_2d_malloc(obj->nLevels, obj->nPairs);
        obj->xcorrsfiltered = array_2d_malloc(obj->nLevels, obj->nPairs);

        for (iLevel = 0; iLevel < obj->nLevels; iLevel++) {

            for (iPair = 0; iPair < obj->nPairs; iPair++) {

                obj->maxxcorrs->ptr[iLevel][iPair] = maxxcorr_construct(frameSize, obj->deltaDiff->array[iLevel], tdoasMinMax[iLevel]->array[iPair][0], tdoasMinMax[iLevel]->array[iPair][1]);
                obj->xcorrsfiltered->ptr[iLevel][iPair] = vector_float_malloc(frameSize);

                for (iSample = 0; iSample < frameSize; iSample++) {
                    ((vector_float *) obj->xcorrsfiltered->ptr[iLevel][iPair])->array[iSample] = 0.0f;
                }

            }

            matrix_signedint_free(tdoasMinMax[iLevel]);

        }

        free((void *) tdoasMinMax);

        obj->aimgs = array_1d_malloc(obj->nLevels);
        obj->aimages = array_1d_malloc(obj->nLevels);

        for (iLevel = 0; iLevel < obj->nLevels; iLevel++) {
        	obj->aimgs->ptr[iLevel] = aimg_construct(frameSize, obj->nMics, ((matrix_float *) obj->points->ptr[iLevel])->nRows);
        	obj->aimages->ptr[iLevel] = vector_float_malloc(((matrix_float *) obj->points->ptr[iLevel])->nRows);
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

        unsigned int indexSorted;
        unsigned int indexSortedPrev;

        unsigned int iPoint;
        float vPoint;

        for (iMic = 0; iMic < obj->nMics; iMic++) {

            for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

                ((vector_float *) obj->freqs->ptr[iMic])->array[iSample*2+0] = spectra->samples[iMic][iSample*2+0];
                ((vector_float *) obj->freqs->ptr[iMic])->array[iSample*2+1] = spectra->samples[iMic][iSample*2+1];

            }

            phasor_process(obj->phasors->ptr[iMic], obj->freqs->ptr[iMic], NULL, obj->phases->ptr[iMic]);

        }

        for (iMic1 = 0; iMic1 < obj->nMics; iMic1++) {

            for (iMic2 = (iMic1+1); iMic2 < obj->nMics; iMic2++) {

                iPair = pair_iPair(obj->nMics, iMic1, iMic2);

                crossphasor_process(obj->crossphasors->ptr[iPair], obj->phases->ptr[iMic1], obj->phases->ptr[iMic2], obj->phasexs->ptr[iPair]);
                bufferphasor_process(obj->bufferphasors->ptr[iPair], obj->phasexs->ptr[iPair], obj->phasexsmooths->ptr[iPair]);

            }

        }

        obj->bValue++;

        if (obj->bValue == obj->bufferDelta) {          

            obj->bValue = 0;

            for (iMic1 = 0; iMic1 < obj->nMics; iMic1++) {

                for (iMic2 = (iMic1+1); iMic2 < obj->nMics; iMic2++) {

                    iPair = pair_iPair(obj->nMics, iMic1, iMic2);

                    xcorr_process(obj->xcorrs->ptr[iPair], obj->phasexsmooths->ptr[iPair], obj->xcorrsoriginal->ptr[iPair]);

                }

            }

            for (iLevel = 0; iLevel < obj->nLevels; iLevel++) {

                indexSorted = obj->deltaSortIndex->array[iLevel];

                for (iMic1 = 0; iMic1 < obj->nMics; iMic1++) {

                    for (iMic2 = (iMic1+1); iMic2 < obj->nMics; iMic2++) {

                        iPair = pair_iPair(obj->nMics, iMic1, iMic2);

                        if (iLevel == 0) {

                            maxxcorr_process(obj->maxxcorrs->ptr[indexSorted][iPair], obj->xcorrsoriginal->ptr[iPair], obj->xcorrsfiltered->ptr[indexSorted][iPair]);

                        }
                        else {

                            maxxcorr_process(obj->maxxcorrs->ptr[indexSorted][iPair], obj->xcorrsfiltered->ptr[indexSortedPrev][iPair], obj->xcorrsfiltered->ptr[indexSorted][iPair]);

                        }

                    }

                }

                indexSortedPrev = indexSorted;

            }

            iPoint = 0;

            for (iLevel = 0; iLevel < obj->nLevels; iLevel++) {

                aimg_process(obj->aimgs->ptr[iLevel], obj->tdoas->ptr[iLevel], obj->invmap->ptr[iLevel], iPoint, (const vector_float **) (obj->xcorrsfiltered->ptr[iLevel]), obj->aimages->ptr[iLevel]);
                iPoint = minmax_max_float(((vector_float *) obj->aimages->ptr[iLevel])->array, ((vector_float *) obj->aimages->ptr[iLevel])->nElements);   

            }

            vPoint = ((vector_float *) obj->aimages->ptr[obj->nLevels-1])->array[iPoint];
            vPoint /= ((float) obj->bufferSize);

            pots->samples[0] = ((matrix_float *) obj->points->ptr[obj->nLevels-1])->array[iPoint][0];
            pots->samples[1] = ((matrix_float *) obj->points->ptr[obj->nLevels-1])->array[iPoint][1];
            pots->samples[2] = ((matrix_float *) obj->points->ptr[obj->nLevels-1])->array[iPoint][2];
            pots->samples[3] = vPoint;

            pots->timeStamp = spectra->timeStamp;

            obj->vPointPrev = vPoint;
            obj->iPointPrev = iPoint;

        }
        else {

            pots->samples[0] = ((matrix_float *) obj->points->ptr[obj->nLevels-1])->array[obj->iPointPrev][0];
            pots->samples[1] = ((matrix_float *) obj->points->ptr[obj->nLevels-1])->array[obj->iPointPrev][1];
            pots->samples[2] = ((matrix_float *) obj->points->ptr[obj->nLevels-1])->array[obj->iPointPrev][2];
            pots->samples[3] = obj->vPointPrev;

            pots->timeStamp = spectra->timeStamp;

        }

    }