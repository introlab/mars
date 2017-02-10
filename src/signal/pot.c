    
    #include "pot.h"
    
    pots_obj * pots_construct_zero(const unsigned int nPots) {

        pots_obj * obj;

        obj = (pots_obj *) malloc(sizeof(pots_obj));

        obj->nPots = nPots;
        obj->array = (float *) malloc(sizeof(float) * 4 * nPots);
        memset(obj->array, 0x00, sizeof(float) * 4 * nPots);

        return obj;

    }

    void pots_destroy(pots_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void pots_printf(const pots_obj * obj) {

        unsigned int iPot;

        for (iPot = 0; iPot < obj->nPots; iPot++) {

            printf("(%02u): %+1.3f %+1.3f %+1.3f > %+1.3f\n",
                   iPot,
                   obj->array[iPot * 4 + 0],
                   obj->array[iPot * 4 + 1],
                   obj->array[iPot * 4 + 2],
                   obj->array[iPot * 4 + 3]);
            
        }

    }