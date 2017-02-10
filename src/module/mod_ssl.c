    
    #include "mod_ssl.h"    

    mod_ssl_obj * mod_ssl_construct(const mod_ssl_cfg * cfg) {

        mod_ssl_obj * obj;
        unsigned int iLevel;
        unsigned int iPot;

        points_obj * points;

        obj = (mod_ssl_obj *) malloc(sizeof(mod_ssl_obj));

        obj->nMics = cfg->mics->nMics;
        obj->nPairs = obj->nMics * (obj->nMics - 1) / 2;
        obj->nPots = cfg->nPots;
        obj->nScans = cfg->nLevels;

        if (strcmp(cfg->shape,"halfsphere") == 0) {

            obj->scans = scanning_init_halfsphere(cfg->mics, cfg->nLevels, cfg->levels, cfg->fS, cfg->c, cfg->sigma, cfg->nMatches, cfg->frameSize, cfg->deltasMax[0]);

        }
        else {

            obj->scans = scanning_init_sphere(cfg->mics, cfg->nLevels, cfg->levels, cfg->fS, cfg->c, cfg->sigma, cfg->nMatches, cfg->frameSize, cfg->deltasMax[0]);	

        }

        obj->deltasMax = (unsigned int *) malloc(sizeof(unsigned int) * cfg->nLevels);
        memcpy(obj->deltasMax, cfg->deltasMax, sizeof(unsigned int) * cfg->nLevels);

        obj->deltaReset = cfg->deltaReset;
        obj->r = 0;
        obj->R = cfg->R;

        obj->phasors = freqs_construct_zero(obj->nMics, cfg->frameSize/2+1);
        obj->products = freqs_construct_zero(obj->nPairs, cfg->frameSize/2+1);
        obj->smooths = freqs_construct_zero(obj->nPairs, cfg->frameSize/2+1);

        obj->xcorrsReset = (xcorrs_obj **) malloc(sizeof(xcorrs_obj *) * cfg->nPots);
        obj->xcorrsMax = (xcorrs_obj ***) malloc(sizeof(xcorrs_obj **) * cfg->nPots);
        obj->aimgs = (aimg_obj ***) malloc(sizeof(aimg_obj **) * cfg->nPots);
        
        for (iPot = 0; iPot < obj->nPots; iPot++) {
        	
        	obj->xcorrsReset[iPot] = xcorrs_construct_zero(obj->nPairs,cfg->frameSize);
        	obj->xcorrsMax[iPot] = (xcorrs_obj **) malloc(sizeof(xcorrs_obj *) * cfg->nLevels);
        	obj->aimgs[iPot] = (aimg_obj **) malloc(sizeof(aimg_obj *) * cfg->nLevels);

            for (iLevel = 0; iLevel < cfg->nLevels; iLevel++) {

                obj->xcorrsMax[iPot][iLevel] = xcorrs_construct_zero(obj->nPairs,cfg->frameSize);
                obj->aimgs[iPot][iLevel] = aimg_construct_zero(obj->scans->points[iLevel]->nPoints);

            }

        }

        obj->freq2freq = freq2freq_construct_zero((cfg->frameSize/2+1), cfg->epsilon, cfg->alpha);
        obj->freq2xcorr = freq2xcorr_construct_zero(cfg->frameSize, cfg->frameSize/2+1);
        obj->xcorr2xcorr = xcorr2xcorr_construct_zero(cfg->frameSize);

        obj->xcorr2aimg = (xcorr2aimg_obj **) malloc(sizeof(xcorr2aimg_obj *) * cfg->nLevels);

        for (iLevel = 0; iLevel < cfg->nLevels; iLevel++) {
            obj->xcorr2aimg[iLevel] = xcorr2aimg_construct_zero(obj->scans->points[iLevel]->nPoints);	
        }       

        obj->pots = pots_construct_zero(cfg->nPots);

        return obj;

    }

    void mod_ssl_destroy(mod_ssl_obj * obj) {

        unsigned int iLevel;
        unsigned int iPot;

        scans_destroy(obj->scans);

        free((void *) obj->deltasMax);

        freqs_destroy(obj->phasors);
        freqs_destroy(obj->products);
        freqs_destroy(obj->smooths);

        for (iPot = 0; iPot < obj->nPots; iPot++) {

            for (iLevel = 0; iLevel < obj->nScans; iLevel++) {

                xcorrs_destroy(obj->xcorrsMax[iPot][iLevel]);
                aimg_destroy(obj->aimgs[iPot][iLevel]);

            }

            free((void *) obj->xcorrsMax[iPot]);
            free((void *) obj->aimgs[iPot]);

            xcorrs_destroy(obj->xcorrsReset[iPot]);

        }

        free((void *) obj->xcorrsMax);
        free((void *) obj->aimgs);
        free((void *) obj->xcorrsReset);

        freq2freq_destroy(obj->freq2freq);
        freq2xcorr_destroy(obj->freq2xcorr);
        xcorr2xcorr_destroy(obj->xcorr2xcorr);

        for (iLevel = 0; iLevel < obj->nScans; iLevel++) {
            xcorr2aimg_destroy(obj->xcorr2aimg[iLevel]);
        }

        free((void *) obj->xcorr2aimg);

        pots_destroy(obj->pots);

    }

    void mod_ssl_process(mod_ssl_obj * obj, msg_spectra_obj * msg_spectra, msg_pots_obj * msg_pots) {

        unsigned int iPot;
        unsigned int iScan;
        unsigned int iPoint;

        float maxValue;
        unsigned int maxIndex;

        freq2freq_process_phasor(obj->freq2freq, msg_spectra->freqs, obj->phasors);
        freq2freq_process_product(obj->freq2freq, obj->phasors, obj->phasors, obj->products);
        freq2freq_process_smooth(obj->freq2freq, obj->products, obj->smooths);

        obj->r++;

        if (obj->r == obj->R) {

            obj->r = 0;
 
            for (iPot = 0; iPot < obj->nPots; iPot++) {

                if (iPot == 0) {

                    freq2xcorr_process(obj->freq2xcorr, 
                    	               obj->smooths, 
                                       obj->scans->tdoas[obj->nScans-1],
                    	               obj->xcorrsReset[0]);



                }
                else {

                    xcorr2xcorr_process_reset(obj->xcorr2xcorr, 
                	                          obj->xcorrsReset[iPot-1],
                	                          obj->scans->tdoas[obj->nScans-1],
                                              obj->deltaReset,
                                              maxIndex,
                                              obj->xcorrsReset[iPot]);

                }

                maxIndex = 0;

                for (iScan = 0; iScan < obj->nScans; iScan++) {

                    xcorr2xcorr_process_max(obj->xcorr2xcorr, 
            	                            obj->xcorrsReset[iPot], 
            	                            obj->scans->tdoas[obj->nScans-1],
         	                                obj->deltasMax[iScan],
            	                            obj->xcorrsMax[iPot][iScan]);

                    xcorr2aimg_process(obj->xcorr2aimg[iScan],
                	                   obj->scans->tdoas[iScan],
                	                   obj->scans->indexes[iScan],
                                       maxIndex,
                	                   obj->xcorrsMax[iPot][iScan],
                	                   obj->aimgs[iPot][iScan]);

                    maxValue = obj->aimgs[iPot][iScan]->array[0];

                    for (iPoint = 0; iPoint < obj->aimgs[iPot][iScan]->aimgSize; iPoint++) {

                        if (obj->aimgs[iPot][iScan]->array[iPoint] > maxValue) {

                    	    maxValue = obj->aimgs[iPot][iScan]->array[iPoint];
                    	    maxIndex = iPoint;

                        }

                    }

                }

                obj->pots->array[iPot * 4 + 0] = obj->scans->points[obj->nScans-1]->array[maxIndex * 3 + 0];
                obj->pots->array[iPot * 4 + 1] = obj->scans->points[obj->nScans-1]->array[maxIndex * 3 + 1];
                obj->pots->array[iPot * 4 + 2] = obj->scans->points[obj->nScans-1]->array[maxIndex * 3 + 2];
                obj->pots->array[iPot * 4 + 3] = maxValue / ((float) obj->nPairs);

            }

        }

        memcpy(msg_pots->pots->array, obj->pots->array, sizeof(float) * obj->pots->nPots * 4);
        msg_pots->timeStamp = msg_spectra->timeStamp;

    }

    mod_ssl_cfg * mod_ssl_cfg_construct(void) {

        mod_ssl_cfg * cfg;

        cfg = (mod_ssl_cfg *) malloc(sizeof(mod_ssl_cfg));

        cfg->mics = (mics_obj *) NULL;
        cfg->nPots = 0;
        cfg->fS = 0;
        cfg->c = 0;
        cfg->frameSize = 0;
        cfg->nMatches = 0;
        cfg->sigma = 0.0f;
        cfg->epsilon = 0.0f;
        cfg->alpha = 0.0f;
        cfg->shape = (char *) NULL;
        cfg->nLevels = 0;;
        cfg->levels = (unsigned int *) NULL;
        cfg->deltasMax = (unsigned int *) NULL;
        cfg->deltaReset = 0;
        cfg->R = 0;

        return cfg;

    }

    void mod_ssl_cfg_destroy(mod_ssl_cfg * cfg) {

        if (cfg->mics != NULL) {
            free((void *) cfg->mics);
        }

        if (cfg->shape != NULL) {
            free((void *) cfg->shape);            
        }

        free((void *) cfg);

    }