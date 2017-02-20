
    #include "scanning.h"

    scans_obj * scanning_init_sphere(const mics_obj * mics, const unsigned int nLevels, const unsigned int * levels, const unsigned int fS, const float c, const float sigma, const unsigned int nMatches, const unsigned int frameSize, const unsigned int delta) {

        scans_obj * obj;
        unsigned int iLevel;

        obj = scans_construct_null(nLevels);

        for (iLevel = 0; iLevel < nLevels; iLevel++) {

            obj->points[iLevel] = space_sphere(levels[iLevel]);
            obj->tdoas[iLevel] = delay_tdoas(obj->points[iLevel], mics, c, fS, frameSize, delta);

        }

        scanning_init_link(obj, nMatches, sigma);

        return obj;

    }

    scans_obj * scanning_init_halfsphere(const mics_obj * mics, const unsigned int nLevels, const unsigned int * levels, const unsigned int fS, const float c, const float sigma, const unsigned int nMatches, const unsigned int frameSize, const unsigned int delta) {

        scans_obj * obj;
        unsigned int iLevel;

        obj = scans_construct_null(nLevels);

        for (iLevel = 0; iLevel < nLevels; iLevel++) {

            obj->points[iLevel] = space_halfsphere(levels[iLevel]);
            obj->tdoas[iLevel] = delay_tdoas(obj->points[iLevel], mics, c, fS, frameSize, delta);

        }

        scanning_init_link(obj, nMatches, sigma);

        return obj;

    }

    scans_obj * scanning_init_arc(const mics_obj * mics, const unsigned int nLevels, const unsigned * levels, const unsigned int fS, const float c, const float sigma, const unsigned int nMatches, const unsigned int frameSize, const unsigned int delta) {

        scans_obj * obj;
        unsigned int iLevel;

        obj = scans_construct_null(nLevels);

        for (iLevel = 0; iLevel < nLevels; iLevel++) {

            obj->points[iLevel] = space_arc(levels[iLevel]);
            obj->tdoas[iLevel] = delay_tdoas(obj->points[iLevel], mics, c, fS, frameSize, delta);

        }

        scanning_init_link(obj, nMatches, sigma);

        return obj;        

    }

    void scanning_init_link(scans_obj * scans, const unsigned int nMatches, const float sigma) {

        unsigned int iLevel;
        maps_obj * maps;

        for (iLevel = 0; iLevel < scans->nScans; iLevel++) {

            if (iLevel == 0) {

                maps = linking_maps(NULL, scans->tdoas[0], sigma, nMatches);    

            }
            else {

                maps = linking_maps(scans->tdoas[iLevel-1], scans->tdoas[iLevel], sigma, nMatches);    

            }

            scans->indexes[iLevel] = linking_indexes(maps);

            maps_destroy(maps);

        }

    }