    
    #include "ssl_aimg.h"

    ssl_aimg_obj * ssl_aimg_construct(const unsigned int frameSize, const matrix_float * mics, const matrix_float * points, const unsigned int fS, const float c, const unsigned int nScans, const matrix_float * bands, const float epsilon) {

        ssl_aimg_obj * obj;
        matrix_float * tdoas;
        unsigned int iPair;
        matrix_float * tdoasExact;
        unsigned int iBand;
        unsigned int iMic;
        unsigned int iScan;

        obj->frameSize = frameSize;
        obj->halfFrameSize = frameSize/2 + 1;
        obj->nMics = mics->nRows;
        obj->nPoints = points->nRows;
        obj->nPairs = obj->nMics * (obj->nMics - 1) / 2;
        obj->fS = fS;
        obj->c = c;
        obj->epsilon = epsilon;
        obj->nScans = nScans;
        obj->nBands = bands->nRows;

        obj->mics = matrix_float_clone(mics);
        obj->points = matrix_float_clone(points);
        obj->bands = matrix_float_clone(bands);

        tdoasExact = tdoa_delay(points, mics, fS, c);
        obj->tdoas = tdoa_round((const matrix_float *) tdoasExact, frameSize);
        matrix_float_free(tdoasExact);

        obj->bandsMics = (matrix_float **) malloc(sizeof(matrix_float *) * obj->nBands);

        for (iBand = 0; iBand < obj->nBands; iBand++) {
        	
        	obj->bandsMics[iBand] = matrix_float_malloc(obj->nMics,obj->halfFrameSize);

            for (iMic = 0; iMic < obj->nMics; iMic++) {

                matrix_float_importexport(obj->bandsMics[iBand],obj->bands,iMic,iBand);

            }

        }

        obj->phases = matrix_float_malloc(obj->nMics, obj->halfFrameSize);
        obj->phasesx = matrix_float_malloc(obj->nPairs, obj->halfFrameSize);

        obj->xcorrs = (matrix_float ***) malloc(sizeof(matrix_float **) * obj->nScans);

        for (iScan = 0; iScan < obj->nScans; iScan++) {

            obj->xcorrs[iScan] = (matrix_float **) malloc(sizeof(matrix_float *) * obj->nBands);

            for (iBand = 0; iBand < obj->nBands; iBand++) {    

                obj->xcorrs[iScan][iBand] = matrix_float_malloc(obj->nPairs,obj->frameSize);

            }

        }

        obj->aimg = (vector_float ***) malloc(sizeof(vector_float **) * obj->nScans);

        for (iScan = 0; iScan < obj->nScans; iScan++) {

            obj->aimg[iScan] = (vector_float **) malloc(sizeof(vector_float *) * obj->nBands);

            for (iBand = 0; iBand < obj->nBands; iBand++) {    

                obj->aimg[iScan][iBand] = vector_float_malloc(obj->nPoints);

            }

        }

        obj->maxIndexes = matrix_unsignedint_malloc(obj->nScans, obj->nBands);
        obj->maxValues = matrix_float_malloc(obj->nScans, obj->nBands);

        obj->freq2phase = freq2phase_construct(obj->frameSize, obj->epsilon, obj->nMics);
        obj->phase2phases = phase2phases_construct(obj->frameSize, obj->nMics);
        obj->phases2xcorr = phases2xcorr_construct(obj->frameSize, obj->nMics);
        obj->xcorr2aimg = xcorr2aimg_construct(obj->frameSize, obj->nMics, obj->nPoints);

        return obj;

    }

    void ssl_aimg_destroy(ssl_aimg_obj * obj) {


    }

    int ssl_aimg_process(ssl_aimg_obj * obj, const matrix_float * freqs, matrix_float ** positions) {

        unsigned int iBand;
        unsigned int iScan;
        unsigned int iPoint;

        for (iBand = 0; iBand < obj->nBands; iBand++) {

            freq2phase_process(obj->freq2phase, freqs, (const matrix_float *) obj->bandsMics[iBand], obj->phases);
            phase2phases_process(obj->phase2phases, (const matrix_float *) obj->phases, obj->phasesx);
            phases2xcorr_process(obj->phases2xcorr, (const matrix_float *) obj->phasesx, obj->xcorrs[iBand][0]);

        }

        for (iScan = 0; iScan < obj->nScans; iScan++) {

            for (iBand = 0; iBand < obj->nBands; iBand++) {

                xcorr2aimg_process((const xcorr2aimg_obj * ) obj->xcorr2aimg, (const matrix_unsignedint *) obj->tdoas, (const matrix_float *) obj->xcorrs[iBand][iScan], obj->aimg[iBand][iScan]);

                obj->maxValues->array[iScan][iBand] = -INFINITY;

                for (iPoint = 0; iPoint < obj->nPoints; iPoint++) {

                    if (obj->aimg[iBand][iScan]->array[iPoint] > obj->maxValues->array[iScan][iBand]) {

                        obj->maxValues->array[iScan][iBand] = obj->aimg[iBand][iScan]->array[iPoint];
                        obj->maxIndexes->array[iScan][iBand] = iPoint;

                    }

                }

            }

            if (iScan < (obj->nScans - 1)) {

                // Remove

            }

        }

    }