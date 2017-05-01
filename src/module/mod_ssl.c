    
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

        if (strcmp(cfg->shape,"sphere") == 0) {

            obj->scans = scanning_init_sphere(cfg->mics, cfg->nLevels, cfg->levels, cfg->fS, cfg->soundspeed, cfg->nMatches, cfg->frameSize, cfg->deltas, cfg->probMin, cfg->nRefinedLevels);

        }
        else {

            obj->scans = scanning_init_halfsphere(cfg->mics, cfg->nLevels, cfg->levels, cfg->fS, cfg->soundspeed, cfg->nMatches, cfg->frameSize, cfg->deltas, cfg->probMin, cfg->nRefinedLevels);

        }

        obj->r = 0;
        obj->R = cfg->R;

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

        xcorr2xcorr_destroy(obj->xcorr2xcorr);

        for (iLevel = 0; iLevel < obj->nScans; iLevel++) {
            xcorr2aimg_destroy(obj->xcorr2aimg[iLevel]);
        }

        free((void *) obj->xcorr2aimg);

        pots_destroy(obj->pots);

        free((void *) obj);

    }

    void mod_ssl_process(mod_ssl_obj * obj, msg_xcs_obj * msg_xcs, msg_pots_obj * msg_pots) {

        unsigned int iPot;
        unsigned int iScan;
        unsigned int iPoint;

        float maxValue;
        unsigned int maxIndex;

        obj->r++;

        if (obj->r == obj->R) {

            obj->r = 0;
 
            for (iPot = 0; iPot < obj->nPots; iPot++) {

                if (iPot == 0) {

                    xcorr2xcorr_process_copy(obj->xcorr2xcorr, 
                                             msg_xcs->xcorrs,
                                             obj->xcorrsReset[0]);

                }
                else {

                    xcorr2xcorr_process_reset(obj->xcorr2xcorr, 
                	                          obj->xcorrsReset[iPot-1],
                	                          obj->scans->tdoas[obj->nScans-1],
                                              obj->scans->allminmax,
                                              obj->scans->deltas[obj->nScans-1],
                                              maxIndex,
                                              obj->xcorrsReset[iPot]);

                }

                maxIndex = 0;

                for (iScan = 0; iScan < obj->nScans; iScan++) {

                    xcorr2xcorr_process_max(obj->xcorr2xcorr, 
            	                            obj->xcorrsReset[iPot], 
            	                            obj->scans->minmax[iScan],
         	                                obj->scans->deltas[iScan],
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
        msg_pots->timeStamp = msg_xcs->timeStamp;

    }

    mod_ssl_cfg * mod_ssl_cfg_construct(void) {

        mod_ssl_cfg * cfg;

        cfg = (mod_ssl_cfg *) malloc(sizeof(mod_ssl_cfg));

        cfg->mics = (mics_obj *) NULL;
        cfg->nPots = 0;
        cfg->fS = 0;
        cfg->soundspeed = (soundspeed_obj *) NULL;
        cfg->frameSize = 0;
        cfg->R = 0;
        cfg->shape = (char *) NULL;
        
        cfg->nLevels = 0;;
        cfg->levels = (unsigned int *) NULL;
        cfg->deltas = (unsigned int *) NULL;
        cfg->nMatches = 0;
        cfg->probMin = 0.0f;
        cfg->nRefinedLevels = 0;

        return cfg;

    }

    void mod_ssl_cfg_destroy(mod_ssl_cfg * cfg) {

        if (cfg->mics != NULL) {
            mics_destroy(cfg->mics);
        }

        if (cfg->soundspeed != NULL) {
            soundspeed_destroy(cfg->soundspeed);
        }

        if (cfg->shape != NULL) {
            free((void *) cfg->shape);            
        }

        if (cfg->levels != NULL) {
            free((void *) cfg->levels);
        }

        if (cfg->deltas != NULL) {
            free((void *) cfg->deltas);
        }

        free((void *) cfg);

    }