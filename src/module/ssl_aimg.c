    
    #include "ssl_aimg.h"

    ssl_aimg_obj * ssl_aimg_construct(const matrix_float * mics, const matrix_float * points, const matrix_float * bands, const unsigned int frameSize, const unsigned int fS, const float c, const unsigned int nScans, const float epsilon, const unsigned int winSizeMax, const unsigned int winSizeReset) {

        ssl_aimg_obj * obj;

        unsigned int iScan;
        unsigned int iBand;
        unsigned int iMic;
        unsigned int iPair;
        unsigned int iPoint;

        obj = (ssl_aimg_obj *) malloc(sizeof(ssl_aimg_obj));
        
        obj->frameSize = frameSize;
        obj->halfFrameSize = frameSize/2 + 1;
        obj->nMics = mics->nRows;
        obj->nPairs = pair_nPairs(obj->nMics);
        obj->nPoints = points->nRows;
        obj->fS = fS;
        obj->c = c;
        obj->epsilon = epsilon;
        obj->winSizeMax = winSizeMax;
        obj->winSizeReset = winSizeReset;
        obj->nScans = nScans;
        obj->nBands = bands->nRows;

        obj->ref_mics = matrix_float_clone(mics);
        obj->ref_points = matrix_float_clone(points);
        obj->ref_bands = matrix_float_clone(bands);
        obj->ref_tdoas = tdoa_delay(points, mics, fS, c);

        obj->tdoasRound = tdoa_round((const matrix_float *) obj->ref_tdoas);    
        obj->tdoasWrap = tdoa_wrap(obj->tdoasRound, frameSize);
        obj->lowValues = vector_signedint_malloc(obj->nPairs);
        obj->highValues = vector_signedint_malloc(obj->nPairs);

        for (iPair = 0; iPair < obj->nPairs; iPair++) {

            obj->lowValues->array[iPair] = obj->tdoasRound->array[0][iPair];
            obj->highValues->array[iPair] = obj->tdoasRound->array[0][iPair];

            for (iPoint = 0; iPoint < obj->nPoints; iPoint++) {

                if (obj->tdoasRound->array[iPoint][iPair] < obj->lowValues->array[iPair]) {
                    obj->lowValues->array[iPair] = obj->tdoasRound->array[iPoint][iPair];
                }
                if (obj->tdoasRound->array[iPoint][iPair] > obj->highValues->array[iPair]) {
                    obj->highValues->array[iPair] = obj->tdoasRound->array[iPoint][iPair];
                }

            }

        }

        obj->bands = array_1d_malloc(obj->nBands);

        for (iBand = 0; iBand < obj->nBands; iBand++) {

            obj->bands->ptr[iBand] = vector_float_malloc(obj->halfFrameSize);
        	matrix_float_export(bands, obj->bands->ptr[iBand], iBand);

        }

        obj->freqs = array_1d_malloc(obj->nMics);

        for (iMic = 0; iMic < obj->nMics; iMic++) {

        	obj->freqs->ptr[iMic] = vector_float_malloc(obj->halfFrameSize*2);

        }

        obj->freq2phase = array_2d_malloc(obj->nBands, obj->nMics);
        obj->phases = array_2d_malloc(obj->nBands, obj->nMics);
        obj->phase2phasex = array_2d_malloc(obj->nBands, obj->nPairs);
        obj->phasexs = array_2d_malloc(obj->nBands, obj->nPairs);
        obj->phasex2xcorr = array_2d_malloc(obj->nBands, obj->nPairs);
        
        for (iBand = 0; iBand < obj->nBands; iBand++) {
                	        
        	for (iMic = 0; iMic < obj->nMics; iMic++) {
        
        		obj->freq2phase->ptr[iBand][iMic] = freq2phase_construct(obj->frameSize, obj->epsilon);
        		obj->phases->ptr[iBand][iMic] = vector_float_malloc(obj->halfFrameSize*2);
        		
        	}

        	for (iPair = 0; iPair < obj->nPairs; iPair++) {

                obj->phase2phasex->ptr[iBand][iPair] = phase2phasex_construct(obj->frameSize);
                obj->phasexs->ptr[iBand][iPair] = vector_float_malloc(obj->halfFrameSize*2);
                obj->phasex2xcorr->ptr[iBand][iPair] = phasex2xcorr_construct(obj->frameSize);                

        	}

        }  

        obj->xcorrs = array_3d_malloc(obj->nScans, obj->nBands, obj->nPairs);
        obj->xcorr2xcorrmax = array_3d_malloc(obj->nScans, obj->nBands, obj->nPairs);
        obj->xcorrsMax = array_3d_malloc(obj->nScans, obj->nBands, obj->nPairs);
        obj->xcorr2xcorrreset = array_3d_malloc(obj->nScans, obj->nBands, obj->nPairs);

        for (iScan = 0; iScan < obj->nScans; iScan++) {
                    
            for (iBand = 0; iBand < obj->nBands; iBand++) {
        
                for (iPair = 0; iPair < obj->nPairs; iPair++) {

                    obj->xcorrs->ptr[iScan][iBand][iPair] = vector_float_malloc(obj->frameSize);
                    obj->xcorr2xcorrmax->ptr[iScan][iBand][iPair] = xcorr2xcorrmax_construct(obj->frameSize, obj->nMics, obj->winSizeMax, obj->lowValues->array[iPair], obj->highValues->array[iPair]);
                    obj->xcorrsMax->ptr[iScan][iBand][iPair] = vector_float_malloc(obj->frameSize);
                    obj->xcorr2xcorrreset->ptr[iScan][iBand][iPair] = xcorr2xcorrreset_construct(obj->frameSize, obj->winSizeReset);
        			
        		}
        	}
        }

        obj->xcorr2aimg = array_2d_malloc(obj->nScans, obj->nBands);
        obj->aimgs = array_2d_malloc(obj->nScans, obj->nBands);

        for (iScan = 0; iScan < obj->nScans; iScan++) {

            for (iBand = 0; iBand < obj->nBands; iBand++) {

                obj->xcorr2aimg->ptr[iScan][iBand] = xcorr2aimg_construct(obj->frameSize, obj->nMics, obj->nPoints);
                obj->aimgs->ptr[iScan][iBand] = vector_float_malloc(obj->nPoints);

            }

        }

        return obj;

    }

    void ssl_aimg_destroy(ssl_aimg_obj * obj) {

        unsigned int iScan;
        unsigned int iBand;
        unsigned int iMic;
        unsigned int iPair;

        for (iScan = 0; iScan < obj->nScans; iScan++) {

            for (iBand = 0; iBand < obj->nBands; iBand++) {

                xcorr2aimg_destroy(obj->xcorr2aimg->ptr[iScan][iBand]);
                vector_float_free(obj->aimgs->ptr[iScan][iBand]);

            }

        }

        array_2d_free(obj->xcorr2aimg);
        array_2d_free(obj->aimgs);

        for (iScan = 0; iScan < obj->nScans; iScan++) {

        	for (iBand = 0; iBand < obj->nBands; iBand++) {

        		for (iPair = 0; iPair < obj->nPairs; iPair++) {

        			xcorr2xcorrreset_destroy(obj->xcorr2xcorrreset->ptr[iScan][iBand][iPair]);
        			vector_float_free(obj->xcorrsMax->ptr[iScan][iBand][iPair]);
        			xcorr2xcorrmax_destroy(obj->xcorr2xcorrmax->ptr[iScan][iBand][iPair]);
        			vector_float_free(obj->xcorrs->ptr[iScan][iBand][iPair]);

        		}

        	}

        }

        array_3d_free(obj->xcorr2xcorrreset);
        array_3d_free(obj->xcorrsMax);
        array_3d_free(obj->xcorr2xcorrmax);
        array_3d_free(obj->xcorrs);

        for (iBand = 0; iBand < obj->nBands; iBand++) {

            for (iPair = 0; iPair < obj->nPairs; iPair++) {

                phasex2xcorr_destroy(obj->phasex2xcorr->ptr[iBand][iPair]);
                vector_float_free(obj->phasexs->ptr[iBand][iPair]);
                phase2phasex_destroy(obj->phase2phasex->ptr[iBand][iPair]);

            }

            for (iMic = 0; iMic < obj->nMics; iMic++) {
                
                vector_float_free(obj->phases->ptr[iBand][iMic]);
                freq2phase_destroy(obj->freq2phase->ptr[iBand][iMic]);

            }        	

        }

        array_2d_free(obj->phasex2xcorr);
        array_2d_free(obj->phasexs);
        array_2d_free(obj->phase2phasex);
        array_2d_free(obj->phases);
        array_2d_free(obj->freq2phase);

        for (iMic = 0; iMic < obj->nMics; iMic++) {

        	vector_float_free(obj->freqs->ptr[iMic]);

        }

        array_1d_free(obj->freqs);

        for (iBand = 0; iBand < obj->nBands; iBand++) {

        	vector_float_free(obj->bands->ptr[iBand]);

        }

        array_1d_free(obj->bands);

        vector_signedint_free(obj->lowValues);
        vector_signedint_free(obj->highValues);
        matrix_signedint_free(obj->tdoasRound);
        matrix_unsignedint_free(obj->tdoasWrap);

        matrix_float_free(obj->ref_tdoas);
        matrix_float_free(obj->ref_bands);
        matrix_float_free(obj->ref_points);
        matrix_float_free(obj->ref_mics);

        free((void *) obj);

    }

    int ssl_aimg_process(ssl_aimg_obj * obj, const msg_spectra_obj * spectra, msg_pots_obj * pots) {

        unsigned int iScan;
        unsigned int iBand;
        unsigned int iMic;
        unsigned int iMic1;
        unsigned int iMic2;
        unsigned int iPair;
        unsigned int iSample;
        
        unsigned int maxIndex;
        float maxValue;

        // Copy content of message in signals

        for (iMic = 0; iMic < obj->nMics; iMic++) {

            for (iSample = 0; iSample < obj->halfFrameSize; iSample++) {

                ((vector_float *) obj->freqs->ptr[iMic])->array[iSample*2+0] = spectra->samples[iMic][iSample*2+0];
                ((vector_float *) obj->freqs->ptr[iMic])->array[iSample*2+1] = spectra->samples[iMic][iSample*2+1];

            }

        }

        // Process

        for (iBand = 0; iBand < obj->nBands; iBand++) {

            // X_m^b[k] = X_m[k] * zeta_b[k] / |X_m[k]|

            for (iMic = 0; iMic < obj->nMics; iMic++) {

                freq2phase_process(obj->freq2phase->ptr[iBand][iMic], 
                	               obj->freqs->ptr[iMic], 
                	               obj->bands->ptr[iBand], 
                	               obj->phases->ptr[iBand][iMic]);

            }

            // X_m1,m2^b[k] = X_m1^b[k] * X'_m2^b[k]
            // xx_m1,m2^b[n] = ifft(X_m1,m2^b[k])

            for (iMic1 = 0; iMic1 < obj->nMics; iMic1++) {

                for (iMic2 = (iMic1+1); iMic2 < obj->nMics; iMic2++) {

                    iPair = pair_iPair(obj->nMics, iMic1, iMic2);

                    phase2phasex_process(obj->phase2phasex->ptr[iBand][iPair], 
                    	                 obj->phases->ptr[iBand][iMic1], 
                    	                 obj->phases->ptr[iBand][iMic2], 
                    	                 obj->phasexs->ptr[iBand][iPair]);

                    phasex2xcorr_process(obj->phasex2xcorr->ptr[iBand][iPair], 
                    	                 obj->phasexs->ptr[iBand][iPair], 
                    	                 obj->xcorrs->ptr[0][iBand][iPair]);

                }

            }
            

        }

        //printf("Step 1\n");

        // Filter each xx with maximum sliding window
        // Generate acoustic image
        // Remove TDOA associated to max

        for (iScan = 0; iScan < obj->nScans; iScan++) {

            for (iBand = 0; iBand < obj->nBands; iBand++) {

                for (iPair = 0; iPair < obj->nPairs; iPair++) {

                    xcorr2xcorrmax_process(obj->xcorr2xcorrmax->ptr[iScan][iBand][iPair], 
                                           obj->xcorrs->ptr[iScan][iBand][iPair], 
                                           obj->xcorrsMax->ptr[iScan][iBand][iPair]);

                }
                
                xcorr2aimg_process(obj->xcorr2aimg->ptr[iScan][iBand],
                                   obj->tdoasWrap,
                                   (const vector_float **) (obj->xcorrsMax->ptr[iScan][iBand]),
                                   obj->aimgs->ptr[iScan][iBand]);

                maxIndex = minmax_max_float(obj->aimgs->ptr[iScan][iBand], obj->nPoints);
                maxValue = ((vector_float *) obj->aimgs->ptr[iScan][iBand])->array[maxIndex];

                if (iScan < (obj->nScans-1)) {
                
                    for (iPair = 0; iPair < obj->nPairs; iPair++) {

                        xcorr2xcorrreset_process(obj->xcorr2xcorrreset->ptr[iScan][iBand][iPair], 
                                                 obj->xcorrs->ptr[iScan][iBand][iPair], 
                                                 obj->tdoasRound->array[maxIndex][iPair],
                                                 obj->xcorrs->ptr[iScan+1][iBand][iPair]);

                    }
                    
                }

                pots->samples[iScan][iBand][0] = obj->ref_points->array[maxIndex][0];
                pots->samples[iScan][iBand][1] = obj->ref_points->array[maxIndex][1];
                pots->samples[iScan][iBand][2] = obj->ref_points->array[maxIndex][2];
                pots->samples[iScan][iBand][3] = maxValue;

            }

        }

    }
  