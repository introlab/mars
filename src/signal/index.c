    
    #include "index.h"

    index_obj * index_construct_zero(const unsigned int nIndexes) {

        index_obj * obj;
        unsigned int iIndex;

        obj = (index_obj *) malloc(sizeof(index_obj));

        obj->nIndexes = nIndexes;
        obj->array = (unsigned int *) malloc(sizeof(unsigned int) * nIndexes);

        for (iIndex = 0; iIndex < nIndexes; iIndex++) {
            obj->array[iIndex] = 0;
        }

        return obj;

    }

    index_obj * index_construct_list(const unsigned int nIndexes, const unsigned int * list) {

        index_obj * obj;
        unsigned int iIndex;

        obj = (index_obj *) malloc(sizeof(index_obj));

        obj->nIndexes = nIndexes;
        obj->array = (unsigned int *) malloc(sizeof(unsigned int) * nIndexes);

        for (iIndex = 0; iIndex < nIndexes; iIndex++) {
            obj->array[iIndex] = list[iIndex];
        }

        return obj;

    }

    index_obj * index_construct_index(const index_obj * index) {

        index_obj * obj;
        unsigned int iIndex;

        obj = (index_obj *) malloc(sizeof(index_obj));

        obj->nIndexes = index->nIndexes;
        obj->array = (unsigned int *) malloc(sizeof(unsigned int) * index->nIndexes);

        for (iIndex = 0; iIndex < index->nIndexes; iIndex++) {
            obj->array[iIndex] = obj->array[iIndex];
        }

        return obj;

    }

    void index_copy_zero(index_obj * obj) {

        unsigned int iIndex;

        for (iIndex = 0; iIndex < obj->nIndexes; iIndex++) {
            obj->array[iIndex] = 0;
        }

    }

    void index_copy_list(index_obj * obj, const unsigned int * list) {

        unsigned int iIndex;

        for (iIndex = 0; iIndex < obj->nIndexes; iIndex++) {
            obj->array[iIndex] = list[iIndex];
        }

    }

    void index_copy_index(index_obj * obj, const index_obj * index) {

        unsigned int iIndex;

        for (iIndex = 0; iIndex < index->nIndexes; iIndex++) {
            obj->array[iIndex] = index->array[iIndex];
        }

    }

    void index_destroy(index_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void index_printf(index_obj * obj) {

        unsigned int iIndex;

        for (iIndex = 0; iIndex < obj->nIndexes; iIndex++) {
            printf("%04u ",obj->array[iIndex]);
        }
        printf("\n");

    }

    indexes_obj * indexes_construct_null(const unsigned int nSignals) {

        indexes_obj * obj;
        unsigned int iSignal;

        obj = (indexes_obj *) malloc(sizeof(indexes_obj));

        obj->nSignals = nSignals;
        obj->array = (index_obj **) malloc(sizeof(index_obj *) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {
            obj->array[iSignal] = NULL;
        }

        return obj;

    }

    void indexes_destroy(indexes_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            if (obj->array[iSignal] != NULL) {
                index_destroy(obj->array[iSignal]);
            }
        }

        free((void *) obj->array);
        free((void *) obj);

    }

    void indexes_printf(indexes_obj * obj) {

        unsigned int iSignal;
        unsigned int iIndex;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            printf("(%04u): ",iSignal);

            if (obj->array[iSignal] != NULL) {

                for (iIndex = 0; iIndex < obj->array[iSignal]->nIndexes; iIndex++) {

                    printf("%04u ",obj->array[iSignal]->array[iIndex]);

                }

            }
            else {

                printf("(null)");

            }

            printf("\n");

        }

    }