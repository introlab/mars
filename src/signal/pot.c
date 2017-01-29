    
    #include "pot.h"

    pot_obj * pot_construct_zero(void) {

        pot_obj * obj;

        obj = (pot_obj *) malloc(sizeof(pot_obj));

        obj->coord = coord_construct_zero();
        obj->E = 0.0f;

        return obj;

    }

    pot_obj * pot_construct_xyzE(const float x, const float y, const float z, const float E) {

        pot_obj * obj;

        obj = (pot_obj *) malloc(sizeof(pot_obj));

        obj->coord = coord_construct_xyz(x,y,z);
        obj->E = E;

        return obj;        

    }

    pot_obj * pot_construct_pot(const pot_obj * pot) {

        pot_obj * obj;

        obj = (pot_obj *) malloc(sizeof(pot_obj));

        obj->coord = coord_construct_coord(pot->coord);
        obj->E = pot->E;

        return obj;

    }

    void pot_copy_zero(pot_obj * obj) {

        coord_copy_zero(obj->coord);
        obj->E = 0.0f;
    }

    void pot_copy_xyzE(pot_obj * obj, const float x, const float y, const float z, const float E) {

        coord_copy_xyz(obj->coord, x, y, z);
        obj->E = E;

    }

    void pot_copy_pot(pot_obj * obj, const pot_obj * pot) {

        coord_copy_coord(obj->coord, pot->coord);
        obj->E = pot->E;

    }

    void pot_destroy(pot_obj * obj) {

        free((void *) obj);

    }

    void pot_printf(pot_obj * obj) {

        printf("(%+1.4f , %+1.4f , %+1.4f) > %+1.4f\n", obj->coord->x, obj->coord->y, obj->coord->z,obj->E);

    }

    pots_obj * pots_construct_zero(const unsigned int nSignals) {

        pots_obj * obj;
        unsigned int iSignal;

        obj = (pots_obj *) malloc(sizeof(pots_obj));

        obj->nSignals = nSignals;
        obj->array = (pot_obj **) malloc(sizeof(pot_obj **) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {
            obj->array[iSignal] = pot_construct_zero();
        }

        return obj;

    }

    void pots_copy_pots(pots_obj * obj, const pots_obj * pots) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            pot_copy_pot(obj->array[iSignal],pots->array[iSignal]);
        }

    }

    void pots_destroy(pots_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            if (obj->array[iSignal] != NULL) {
                pot_destroy(obj->array[iSignal]);
            }

        }

        free((void *) obj->array);
        free((void *) obj);

    }

    void pots_printf(pots_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            if (obj->array[iSignal] != NULL) {
                printf("%03u: (%+1.4f , %+1.4f , %+1.4f) > %1.4f\n", iSignal, obj->array[iSignal]->coord->x, obj->array[iSignal]->coord->y, obj->array[iSignal]->coord->z, obj->array[iSignal]->E);    
            }
            else {
                printf("%03u: (null)\n",iSignal);
            }
        }   

    }