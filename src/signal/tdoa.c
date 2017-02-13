    
    #include "tdoa.h"

    tdoas_obj * tdoas_construct_zero(const unsigned int nPoints, const unsigned int nPairs) {

        tdoas_obj * obj;
        unsigned int iPoint;

        obj = (tdoas_obj *) malloc(sizeof(tdoas_obj));

        obj->nPoints = nPoints;
        obj->nPairs = nPairs;

        obj->array = (unsigned short **) malloc(sizeof(unsigned short *) * nPoints);
        for (iPoint = 0; iPoint < nPoints; iPoint++) {
            obj->array[iPoint] = (unsigned short *) malloc(sizeof(unsigned short) * nPairs);
            memset(obj->array[iPoint], 0x00, sizeof(unsigned short) * nPairs);    
        }
        

        obj->arrayMin = (unsigned short *) malloc(sizeof(unsigned short) * nPairs);
        memset(obj->arrayMin, 0x00, sizeof(unsigned short) * nPairs);

        obj->arrayMax = (unsigned short *) malloc(sizeof(unsigned short) * nPairs);
        memset(obj->arrayMax, 0x00, sizeof(unsigned short) * nPairs);

        return obj;

    }

    void tdoas_destroy(tdoas_obj * obj) {

        unsigned int iPoint;

        for (iPoint = 0; iPoint < obj->nPoints; iPoint++) {
            free((void *) obj->array[iPoint]);
        }
        free((void *) obj->array);

        free((void *) obj->arrayMin);
        free((void *) obj->arrayMax);
        free((void *) obj);

    }

    void tdoas_printf(const tdoas_obj * obj) {

        unsigned int iPoint;
        unsigned int iPair;

        for (iPoint = 0; iPoint < obj->nPoints; iPoint++) {

            printf("(%04u): ",iPoint);

            for (iPair = 0; iPair < obj->nPairs; iPair++) {

                printf("%04u ",obj->array[iPoint][iPair]);

            }

            printf("\n");

        }

    }
