
    #include "linking.h"

    maps_obj * linking_maps(const tdoas_obj * tdoasCoarse, const tdoas_obj * tdoasFine, const float sigma, const unsigned int nMatches) {

        maps_obj * obj;
        float * scores;
        unsigned int iFine;
        unsigned int iCoarse;
        unsigned int iMatch;
        float maxValue;
        unsigned int maxIndex;

        if (tdoasCoarse != NULL) {

            obj = maps_construct_null(tdoasFine->nSignals);
        
            for (iFine = 0; iFine < tdoasFine->nSignals; iFine++) {

                obj->array[iFine] = map_construct_zero(tdoasCoarse->nSignals);

                scores = linking_scores(tdoasCoarse, tdoasFine->array[iFine], sigma);

                for (iMatch = 0; iMatch < nMatches; iMatch++) {

                    maxValue = scores[0];
                    maxIndex = 0;

                    for (iCoarse = 0; iCoarse < tdoasCoarse->nSignals; iCoarse++) {

                        if (scores[iCoarse] > maxValue) {

                            maxValue = scores[iCoarse];
                            maxIndex = iCoarse;

                        }

                    }

                    obj->array[iFine]->array[maxIndex] = 1;
                    scores[maxIndex] = 0.0f;

                }

                free((void *) scores);

            }

        }
        else {

            obj = maps_construct_null(tdoasFine->nSignals);

            for (iFine = 0; iFine < tdoasFine->nSignals; iFine++) {
            	obj->array[iFine] = map_construct_zero(1);
            	obj->array[iFine]->array[0] = 1;
            }

        }

        return obj;

    }

    float * linking_scores(const tdoas_obj * tdoasCoarse, const tdoa_obj * tdoaFine, const float sigma) {

        unsigned int iSignal;
        float * scores;

        scores = (float *) malloc(sizeof(float) * tdoasCoarse->nSignals);

        for (iSignal = 0; iSignal < tdoasCoarse->nSignals; iSignal++) {
        	scores[iSignal] = linking_score(tdoasCoarse->array[iSignal],tdoaFine,sigma);
        }

        return scores;

    }

    float linking_score(const tdoa_obj * tdoaCoarse, const tdoa_obj * tdoaFine, const float sigma) {

        unsigned int iPair;
        float tauCoarse;
        float tauFine;
        float tauDiff;
        float score;

        score = 0.0f;

        for (iPair = 0; iPair < tdoaCoarse->nPairs; iPair++) {

            tauCoarse = (float) (tdoaCoarse->array[iPair]);
            tauFine = (float) (tdoaFine->array[iPair]);
            tauDiff = tauCoarse - tauFine;

            score += exp(-1.0f * tauDiff * tauDiff / (2.0f * sigma));

        }

        return score;

    }

    indexes_obj * linking_indexes(const maps_obj * maps) {

        indexes_obj * obj;

        unsigned int iSignal;
        unsigned int iLink;
        unsigned int nLinks;
        unsigned int nIndexes;

        nLinks = 0;

        for (iSignal = 0; iSignal < maps->nSignals; iSignal++) {

            if (maps->array[iSignal]->nLinks > nLinks) {
            	nLinks = maps->array[iSignal]->nLinks;
            }

        }

        obj = indexes_construct_null(nLinks);

        for (iLink = 0; iLink < nLinks; iLink++) {

            nIndexes = 0;

            for (iSignal = 0; iSignal < maps->nSignals; iSignal++) {

                if (iLink < maps->array[iSignal]->nLinks) {

                    if (maps->array[iSignal]->array[iLink] == 1) {

                        nIndexes++;

                    }

                }

            }

            obj->array[iLink] = index_construct_zero(nIndexes);

            nIndexes = 0;

            for (iSignal = 0; iSignal < maps->nSignals; iSignal++) {

                if (iLink < maps->array[iSignal]->nLinks) {

                    if (maps->array[iSignal]->array[iLink] == 1) {

                        obj->array[iLink]->array[nIndexes] = iSignal;
                        nIndexes++;

                    }

                }

            }            

        }

        return obj;

    }