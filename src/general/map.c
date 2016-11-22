    
    #include "map.h"

	#include <stdio.h>

    matrix_unsignedint * map_generate_forward(const matrix_float * tdoasCoarse, const matrix_float * tdoasFine, const float sigma, const unsigned int nMatches) {

        unsigned int iCoarse;
        unsigned int iFine;
        unsigned int iPair;
        unsigned int iMatch;

        float diff;
        float prob;

        float * probs;

        float maxValue;
        unsigned int maxIndex;

        matrix_unsignedint * map_forward;

        map_forward = matrix_unsignedint_malloc(tdoasFine->nRows, nMatches);

        probs = (float *) malloc(sizeof(float) * tdoasCoarse->nRows);

        for (iFine = 0; iFine < tdoasFine->nRows; iFine++) {

            for (iCoarse = 0; iCoarse < tdoasCoarse->nRows; iCoarse++) {

                prob = 0.0f;

                for (iPair = 0; iPair < tdoasCoarse->nCols; iPair++) {

                    prob += distribution_normal(tdoasFine->array[iFine][iPair],tdoasCoarse->array[iCoarse][iPair],sigma);

                }

                probs[iCoarse] = prob;

            }

            for (iMatch = 0; iMatch < nMatches; iMatch++) {

                maxValue = 0.0f;
                maxIndex = 0;

                for (iCoarse = 0; iCoarse < tdoasCoarse->nRows; iCoarse++) {

	                if (probs[iCoarse] > maxValue) {

	                    maxValue = probs[iCoarse];
	                    maxIndex = iCoarse;

	                }

                }

                map_forward->array[iFine][iMatch] = maxIndex + 1;

                probs[maxIndex] = 0.0f;

            }

        }

        free((void *) probs);

        return map_forward;

    }

    matrix_unsignedint * map_generate_reverse(const matrix_float * tdoasCoarse, const matrix_float * tdoasFine, const float sigma, const unsigned int nMatches) {

        matrix_unsignedint * map_forward;
        matrix_unsignedint * map_reverse;

        unsigned int iCoarse;
        unsigned int iFine;
        unsigned int iMatch;

        unsigned int nLinks;
        unsigned int maxLinks;

        map_forward = map_generate_forward(tdoasCoarse, tdoasFine, sigma, nMatches);

        maxLinks = 0;

        for (iCoarse = 0; iCoarse < tdoasCoarse->nRows; iCoarse++) {

            nLinks = 0;

            for (iFine = 0; iFine < tdoasFine->nRows; iFine++) {

                for (iMatch = 0; iMatch < nMatches; iMatch++) {

                    if (map_forward->array[iFine][iMatch] == (iCoarse+1)) {

                        nLinks++;

                    }

                }

            }

            if (nLinks > maxLinks) {

                maxLinks = nLinks;

            }

        }

        map_reverse = matrix_unsignedint_malloc(tdoasCoarse->nRows, maxLinks);

        for (iCoarse = 0; iCoarse < tdoasCoarse->nRows; iCoarse++) {

            for (nLinks = 0; nLinks < maxLinks; nLinks++) {

                map_reverse->array[iCoarse][nLinks] = 0;

            }

            nLinks = 0;

            for (iFine = 0; iFine < tdoasFine->nRows; iFine++) {

                for (iMatch = 0; iMatch < nMatches; iMatch++) {

                    if (map_forward->array[iFine][iMatch] == (iCoarse+1)) {

                        map_reverse->array[iCoarse][nLinks] = iFine + 1;

                        nLinks++;

                    }

                }

            }

        }

        matrix_unsignedint_free(map_forward);

        return map_reverse;

    }

    matrix_unsignedint * map_generate_reverse_init(const matrix_float * tdoasFine) {

        matrix_unsignedint * map_reverse;

        unsigned int iPoint;

        map_reverse = matrix_unsignedint_malloc(1, tdoasFine->nRows);

        for (iPoint = 0; iPoint < tdoasFine->nRows; iPoint++)  {

            map_reverse->array[0][iPoint] = iPoint + 1;

        }

        return map_reverse;

    }