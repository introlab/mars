
    #include "scanning.h"

    scans_obj * scanning_init_sphere(const mics_obj * mics, const unsigned int nLevels, const unsigned int * levels, const unsigned int fS, const soundspeed_obj * soundspeed, const unsigned int nMatches, const unsigned int frameSize, const signed int * deltas, const float probMin, const unsigned int nRefineLevels) {

        scans_obj * obj;
        
        unsigned int iLevel;
        taus_obj * taus;
        points_obj * pointsRefined;

        obj = scans_construct_null(nLevels);

        for (iLevel = 0; iLevel < nLevels; iLevel++) {

            obj->points[iLevel] = space_sphere(levels[iLevel]);
            obj->tdoas[iLevel] = delay_tdoas(obj->points[iLevel], mics, soundspeed, fS, frameSize);
            
            if (deltas[iLevel] < 0) {

                pointsRefined = space_points_fine(obj->points[iLevel],nRefineLevels);
                taus = delay_taus(pointsRefined, mics, soundspeed, fS, frameSize);

                obj->deltas[iLevel] = hit_train(taus, obj->tdoas[iLevel], probMin);

                points_destroy(pointsRefined);
                taus_destroy(taus);


            }
            else {

                obj->deltas[iLevel] = hit_constant(obj->tdoas[iLevel], deltas[iLevel]);

            }

            obj->minmax[iLevel] = delay_tdoas_minmax(obj->tdoas[iLevel], obj->deltas[iLevel]);

        }

        scanning_init_minmax(obj);

        scanning_init_link(obj, nMatches);

        return obj;

    }

    scans_obj * scanning_init_halfsphere(const mics_obj * mics, const unsigned int nLevels, const unsigned int * levels, const unsigned int fS, const soundspeed_obj * soundspeed, const unsigned int nMatches, const unsigned int frameSize, const signed int * deltas, const float probMin, const unsigned int nRefineLevels) {

        scans_obj * obj;

        unsigned int iLevel;
        taus_obj * taus;
        points_obj * pointsRefined;

        obj = scans_construct_null(nLevels);

        for (iLevel = 0; iLevel < nLevels; iLevel++) {

            obj->points[iLevel] = space_halfsphere(levels[iLevel]);
            obj->tdoas[iLevel] = delay_tdoas(obj->points[iLevel], mics, soundspeed, fS, frameSize);
            
            if (deltas[iLevel] < 0) {

                pointsRefined = space_points_fine(obj->points[iLevel],nRefineLevels);
                taus = delay_taus(pointsRefined, mics, soundspeed, fS, frameSize);

                obj->deltas[iLevel] = hit_train(taus, obj->tdoas[iLevel], probMin);

                points_destroy(pointsRefined);
                taus_destroy(taus);

            }
            else {

                obj->deltas[iLevel] = hit_constant(obj->tdoas[iLevel], deltas[iLevel]);

            }

            obj->minmax[iLevel] = delay_tdoas_minmax(obj->tdoas[iLevel], obj->deltas[iLevel]);

        }

        scanning_init_link(obj, nMatches);

        scanning_init_minmax(obj);

        return obj;

    }

    void scanning_init_link(scans_obj * scans, const unsigned int nMatches) {

        unsigned int iLevel;
        maps_obj * maps;

        for (iLevel = 0; iLevel < scans->nScans; iLevel++) {

            if (iLevel == 0) {

                maps = linking_maps(NULL, scans->tdoas[0], NULL, scans->deltas[0], nMatches);                

            }
            else {

                maps = linking_maps(scans->tdoas[iLevel-1], scans->tdoas[iLevel], scans->deltas[iLevel-1], scans->deltas[iLevel], nMatches);    

            }

            scans->indexes[iLevel] = linking_indexes(maps);

            maps_destroy(maps);

        }

    }

    void scanning_init_minmax(scans_obj * scans) {

        unsigned int iLevel;
        unsigned int iPair;
        unsigned int nPairs;

        if (scans->nScans > 0) {

            nPairs = scans->minmax[0]->nPairs;
            scans->allminmax = tdoas_construct_zero(2, nPairs);

            for (iPair = 0; iPair < nPairs; iPair++) {
                scans->allminmax->array[0*nPairs+iPair] = scans->minmax[0]->array[0*nPairs+iPair];
                scans->allminmax->array[1*nPairs+iPair] = scans->minmax[0]->array[1*nPairs+iPair];
            }

            for (iLevel = 0; iLevel < scans->nScans; iLevel++) {

                delay_tdoas_allminmax(scans->allminmax, scans->minmax[iLevel]);

            }

        }

    }