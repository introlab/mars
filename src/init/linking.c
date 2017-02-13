
    #include "linking.h"

    maps_obj * linking_maps(const tdoas_obj * tdoasCoarse, const tdoas_obj * tdoasFine, const float sigma, const unsigned int nMatches) {

        maps_obj * obj;
        float * scores;
        
        float score;
        float tauCoarse;
        float tauFine;
        float tauDiff;

        unsigned int iFine;
        unsigned int iCoarse;
        unsigned int iPair;
        unsigned int iMatch;

        float maxValue;
        unsigned int maxIndex;

        if (tdoasCoarse != NULL) {

            obj = maps_construct_zero(tdoasCoarse->nPoints, tdoasFine->nPoints);
            scores = (float *) malloc(sizeof(float) * tdoasCoarse->nPoints);

            for (iFine = 0; iFine < tdoasFine->nPoints; iFine++) {

                for (iCoarse = 0; iCoarse < tdoasCoarse->nPoints; iCoarse++) {

                    scores[iCoarse] = 0.0f;

                    for (iPair = 0; iPair < tdoasFine->nPairs; iPair++) {

                        tauCoarse = (float) (tdoasCoarse->array[iCoarse][iPair]);
                        tauFine = (float) (tdoasFine->array[iFine][iPair]);
                        tauDiff = tauCoarse - tauFine;

                        scores[iCoarse] += exp(-1.0f * tauDiff * tauDiff / (2.0f * sigma));

                    }

                }

                for (iMatch = 0; iMatch <  nMatches; iMatch++) {

                    maxIndex = 0;
                    maxValue = scores[maxIndex];

                    for (iCoarse = 1; iCoarse < tdoasCoarse->nPoints; iCoarse++) {

                        if (scores[iCoarse] > maxValue) {

                            maxValue = scores[iCoarse];
                            maxIndex = iCoarse;

                        }

                    }

                    obj->array[iFine * obj->nCoarses + maxIndex] = 0x01;
                    scores[maxIndex] = -INFINITY;

                }

            }

            free((void *) scores);

        }
        else {

            obj = maps_construct_zero(1, tdoasFine->nPoints);
            memset(obj->array, 0x01, sizeof(unsigned char) * tdoasFine->nPoints);

        }

        return obj;

    }

    indexes_obj * linking_indexes(const maps_obj * maps) {

        indexes_obj * obj;

        unsigned int iFine;
        unsigned int iCoarse;
        unsigned int nFines;
        unsigned int nFinesMax;

        nFinesMax = 0;

        for (iCoarse = 0; iCoarse < maps->nCoarses; iCoarse++) {

            nFines = 0;

            for (iFine = 0; iFine < maps->nFines; iFine++) {

                if (maps->array[iFine * maps->nCoarses + iCoarse] == 0x01) {

                    nFines++;

                }

            }

            if (nFines > nFinesMax) {
                nFinesMax = nFines;
            }

        }

        obj = indexes_construct_zero(maps->nCoarses,nFinesMax);

        for (iCoarse = 0; iCoarse < maps->nCoarses; iCoarse++) {

            nFines = 0;

            for (iFine = 0; iFine < maps->nFines; iFine++) {

                if (maps->array[iFine * maps->nCoarses + iCoarse] == 0x01) {

                    obj->array[iCoarse * nFinesMax + nFines] = iFine;
                    nFines++;

                }

            }

            obj->count[iCoarse] = nFines;

        }        

        return obj;

    }