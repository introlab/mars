    
    #include "assignation.h"

    assignation_obj * assignation_construct_zero(const unsigned int nPots) {

        assignation_obj * obj;
        unsigned int iPot;

        obj = (assignation_obj *) malloc(sizeof(assignation_obj));

        obj->nPots = nPots;
        obj->array = (signed int *) malloc(sizeof(signed int) * nPots);

        for (iPot = 0; iPot < nPots; iPot++) {
        	obj->array[iPot] = 0;
        }

        return obj;

    }

    assignation_obj * assignation_construct_assignation(const assignation_obj * assignation) {

        assignation_obj * obj;
        unsigned int iPot;

        obj = (assignation_obj *) malloc(sizeof(assignation_obj));

        obj->nPots = assignation->nPots;
        obj->array = (signed int *) malloc(sizeof(signed int) * assignation->nPots);

        for (iPot = 0; iPot < assignation->nPots; iPot++) {
            obj->array[iPot] = assignation->array[iPot];
        }
        
        return obj;

    }

    void assignation_destroy(assignation_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void assignation_printf(const assignation_obj * obj) {

        unsigned int iPot;

        for (iPot = 0; iPot < obj->nPots; iPot++) {
        	printf("%+02d ",obj->array[iPot]);
        }

        printf("\n");

    }

    assignations_obj * assignations_construct_null(const unsigned int nSignals) {

    	assignations_obj * obj;
    	unsigned int iSignal;

        obj = (assignations_obj *) malloc(sizeof(assignations_obj));

        obj->nSignals = nSignals;
        obj->array = (assignation_obj **) malloc(sizeof(assignation_obj *) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {
        	obj->array[iSignal] = NULL;
        }

    	return obj;

    }

    void assignations_destroy(assignations_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            if (obj->array[iSignal] != NULL) {
            	assignation_destroy(obj->array[iSignal]);
            }

        }

        free((void *) obj->array);
        free((void *) obj);

    }

    void assignations_printf(const assignations_obj * obj) {

        unsigned int iSignal;
        unsigned int iPot;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            printf("(%03u): ",iSignal);

            if (obj->array[iSignal] != NULL) {

                for (iPot = 0; iPot < obj->array[iSignal]->nPots; iPot++) {
                    printf("%+02d ",obj->array[iSignal]->array[iPot]);
                }

            }
            else {

                printf("(null)");

            }


            printf("\n");            

        }

    }