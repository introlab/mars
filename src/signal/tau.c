    
    #include "tau.h"

    taus_obj * taus_construct_zero(const unsigned int nPoints, const unsigned int nPairs) {

        taus_obj * obj;

        obj = (taus_obj *) malloc(sizeof(taus_obj));

        obj->nPoints = nPoints;
        obj->nPairs = nPairs;

        obj->mu = (float *) malloc(sizeof(float) * nPoints * nPairs);
        memset(obj->mu, 0x00, sizeof(float) * nPoints * nPairs);

        obj->sigma = (float *) malloc(sizeof(float) * nPoints * nPairs);
        memset(obj->sigma, 0x00, sizeof(float) * nPoints * nPairs);

        return obj;

    }

    void taus_destroy(taus_obj * obj) {

        free((void *) obj->mu);
        free((void *) obj->sigma);

    }

    void taus_printf(const taus_obj * obj) {

        unsigned int iPoint;
        unsigned int iPair;

        for (iPoint = 0; iPoint < obj->nPoints; iPoint++) {

            printf("(%04u): ",iPoint);

            for (iPair = 0; iPair < obj->nPairs; iPair++) {

                printf("%03.3f (%03.3f) ",obj->mu[iPoint * obj->nPairs + iPair],obj->sigma[iPoint * obj->nPairs + iPair]);

            }

            printf("\n");

        }

    }