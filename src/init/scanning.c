
    #include "scanning.h"

    scans_obj * scanning_init_sphere(const mics_obj * mics, const unsigned int nLevels, const unsigned int * levels, const unsigned int fS, const float c, const float sigma, const unsigned int nMatches, const unsigned int frameSize) {

        scans_obj * obj;
        unsigned int iLevel;

        obj = scans_construct_null(nLevels);

        for (iLevel = 0; iLevel < nLevels; iLevel++) {

            obj->array[iLevel] = scan_construct_null();

            obj->array[iLevel]->points = space_sphere(levels[iLevel]);
            obj->array[iLevel]->tdoas = delay_tdoas(obj->array[iLevel]->points, mics, c, fS, frameSize);
            obj->array[iLevel]->tdoaMin = delay_mins(obj->array[iLevel]->tdoas);
            obj->array[iLevel]->tdoaMax = delay_maxs(obj->array[iLevel]->tdoas);

        }

        scanning_init_link(obj, nMatches, sigma);

        return obj;

    }

    scans_obj * scanning_init_halfsphere(const mics_obj * mics, const unsigned int nLevels, const unsigned int * levels, const unsigned int fS, const float c, const float sigma, const unsigned int nMatches, const unsigned int frameSize) {

        scans_obj * obj;
        unsigned int iLevel;

        obj = scans_construct_null(nLevels);

        for (iLevel = 0; iLevel < nLevels; iLevel++) {

            obj->array[iLevel] = scan_construct_null();

            obj->array[iLevel]->points = space_halfsphere(levels[iLevel]);
            obj->array[iLevel]->tdoas = delay_tdoas(obj->array[iLevel]->points, mics, c, fS, frameSize);
            obj->array[iLevel]->tdoaMin = delay_mins(obj->array[iLevel]->tdoas);
            obj->array[iLevel]->tdoaMax = delay_maxs(obj->array[iLevel]->tdoas);

        }

        scanning_init_link(obj, nMatches, sigma);

        return obj;

    }

    void scanning_init_link(scans_obj * scans, const unsigned int nMatches, const float sigma) {

        unsigned int iLevel;
        maps_obj * maps;

        for (iLevel = 0; iLevel < scans->nSignals; iLevel++) {

            if (iLevel == 0) {

                maps = linking_maps(NULL, scans->array[0]->tdoas, sigma, nMatches);    

            }
            else {

                maps = linking_maps(scans->array[iLevel-1]->tdoas, scans->array[iLevel]->tdoas, sigma, nMatches);    

            }

            scans->array[iLevel]->indexes = linking_indexes(maps);

            maps_destroy(maps);

        }

    }