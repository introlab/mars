
    #include "linking.h"

    maps_obj * linking_maps(const tdoas_obj * tdoasCoarse, const tdoas_obj * tdoasFine, const deltas_obj * deltasCoarse, const deltas_obj * deltasFine, const float ratioMatch) {

        maps_obj * obj;
        float * scores;
        
        unsigned int lambdaCoarseLeft;
        unsigned int lambdaCoarseRight;
        unsigned int lambdaFineLeft;
        unsigned int lambdaFineRight;

        float score;

        unsigned int iFine;
        unsigned int iCoarse;
        unsigned int iPair;
        unsigned int iMatch;

        unsigned int nFines;
        unsigned int nCoarses;
        unsigned int nPairs;
        unsigned int nMatches;

        float maxValue;
        unsigned int maxIndex;

        if (tdoasCoarse != NULL) {

            nFines = tdoasFine->nPoints;
            nCoarses = tdoasCoarse->nPoints;
            nPairs = tdoasFine->nPairs;

            nMatches = (unsigned int) (roundf(((float) nCoarses) * ratioMatch));

            obj = maps_construct_zero(nCoarses, nFines);
            scores = (float *) malloc(sizeof(float) * nCoarses);

            for (iFine = 0; iFine < nFines; iFine++) {

                for (iCoarse = 0; iCoarse < nCoarses; iCoarse++) {

                    scores[iCoarse] = 0.0f;

                    for (iPair = 0; iPair < nPairs; iPair++) {

                        lambdaCoarseLeft = tdoasCoarse->array[iCoarse * nPairs + iPair] - deltasCoarse->array[iPair];
                        lambdaCoarseRight = tdoasCoarse->array[iCoarse * nPairs + iPair] + deltasCoarse->array[iPair];
                        lambdaFineLeft = tdoasFine->array[iFine * nPairs + iPair] - deltasFine->array[iPair];
                        lambdaFineRight = tdoasFine->array[iFine * nPairs + iPair] + deltasFine->array[iPair];

                        scores[iCoarse] += linking_overlap(lambdaCoarseLeft,lambdaCoarseRight,lambdaFineLeft,lambdaFineRight);

                    }

                }

                for (iMatch = 0; iMatch < nMatches; iMatch++) {

                    maxValue = 0.0f;
                    maxIndex = 0;

                    for (iCoarse = 0; iCoarse < nCoarses; iCoarse++) {

                        if (scores[iCoarse] > maxValue) {

                            maxValue = scores[iCoarse];
                            maxIndex = iCoarse;

                        }

                    }

                    obj->array[iFine * obj->nCoarses + maxIndex] = 0x01;
                    scores[maxIndex] = 0.0f;

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

    float linking_overlap(const float lambdaCoarseLeft, const float lambdaCoarseRight, const float lambdaFineLeft, const float lambdaFineRight) {

        float overlap;
        float lambdaMaxLeft;
        float lambdaMinRight;

        if ((lambdaCoarseRight >= lambdaFineLeft) && (lambdaCoarseLeft <= lambdaFineRight)) {

            if (lambdaCoarseLeft > lambdaFineLeft) {

                lambdaMaxLeft = lambdaCoarseLeft;

            }
            else {

                lambdaMaxLeft = lambdaFineLeft;

            }

            if (lambdaCoarseRight < lambdaFineRight) {

                lambdaMinRight = lambdaCoarseRight;

            }
            else {

                lambdaMinRight = lambdaFineRight;

            }
            
            overlap = lambdaMinRight - lambdaMaxLeft + 1.0f;

        }
        else {
            
            overlap = 0.0f;

        }

        return overlap;

    }