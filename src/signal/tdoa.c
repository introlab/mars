    
    #include "tdoa.h"

    tdoa_obj * tdoa_construct_zero(const unsigned int nPairs) {

        tdoa_obj * obj;
        unsigned int iPair;

        obj = (tdoa_obj *) malloc(sizeof(tdoa_obj));

        obj->nPairs = nPairs;
        obj->array = (unsigned int *) malloc(sizeof(unsigned int) * nPairs);

        for (iPair = 0; iPair < nPairs; iPair++) {
            obj->array[iPair] = 0;
        }

        return obj;

    }

    tdoa_obj * tdoa_construct_pair(const unsigned int nPairs, const unsigned int * pair) {

        tdoa_obj * obj;
        unsigned int iPair;

        obj = (tdoa_obj *) malloc(sizeof(tdoa_obj));

        obj->nPairs = nPairs;
        obj->array = (unsigned int *) malloc(sizeof(unsigned int) * nPairs);

        for (iPair = 0; iPair < nPairs; iPair++) {
            obj->array[iPair] = pair[iPair];
        }

        return obj;

    }

    tdoa_obj * tdoa_construct_tdoa(const tdoa_obj * tdoa) {

        tdoa_obj * obj;
        unsigned int iPair;

        obj = (tdoa_obj *) malloc(sizeof(tdoa_obj));

        obj->nPairs = tdoa->nPairs;
        obj->array = (unsigned int *) malloc(sizeof(unsigned int) * tdoa->nPairs);

        for (iPair = 0; iPair < tdoa->nPairs; iPair++) {
            obj->array[iPair] = tdoa->array[iPair];
        }

        return obj;

    }

    void tdoa_copy_zero(tdoa_obj * obj) {

        unsigned int iPair;

        for (iPair = 0; iPair < obj->nPairs; iPair++) {
            obj->array[iPair] = 0;
        }

    }

    void tdoa_copy_pair(tdoa_obj * obj, const unsigned int * pair) {

        unsigned int iPair;

        for (iPair = 0; iPair < obj->nPairs; iPair++) {
            obj->array[iPair] = pair[iPair];
        }

    }

    void tdoa_copy_tdoa(tdoa_obj * obj, const tdoa_obj * tdoa) {

        unsigned int iPair;

        for (iPair = 0; iPair < obj->nPairs; iPair++) {
            obj->array[iPair] = tdoa->array[iPair];
        }

    }

    void tdoa_destroy(tdoa_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void tdoa_printf(tdoa_obj * obj) {

        unsigned int iPair;

        for (iPair = 0; iPair < obj->nPairs; iPair++) {
            printf("%04u ",obj->array[iPair]);
        }
        printf("\n");

    }

    tdoas_obj * tdoas_construct_null(const unsigned int nSignals) {

        tdoas_obj * obj;
        unsigned int iSignal;

        obj = (tdoas_obj *) malloc(sizeof(tdoas_obj));

        obj->nSignals = nSignals;
        obj->array = (tdoa_obj **) malloc(sizeof(tdoa_obj *) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {
            obj->array[iSignal] = NULL;
        }

        return obj;

    }

    void tdoas_destroy(tdoas_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            if (obj->array[iSignal] != NULL) {
                tdoa_destroy(obj->array[iSignal]);    
            }
        }

        free((void *) obj->array);
        free((void *) obj);

    }

    void tdoas_printf(tdoas_obj * obj) {

        unsigned int iSignal;
        unsigned int iPair;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
        
            printf("(%04u): ", iSignal);

            if (obj->array[iSignal] != NULL) {               

                for (iPair = 0; iPair < obj->array[iSignal]->nPairs; iPair++) {
                    printf("%04u ",obj->array[iSignal]->array[iPair]);
                }

            }
            else {
                printf("(null)");
            }
        
            printf("\n");            

        }

    }