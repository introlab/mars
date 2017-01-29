
    #include "mic.h"

    mic_obj * mic_construct_zero(void) {

        mic_obj * obj;

        obj = (mic_obj *) malloc(sizeof(mic_obj));

        obj->coord = coord_construct_zero();

        return obj;

    }

    mic_obj * mic_construct_xyz(const float x, const float y, const float z) {

        mic_obj * obj;

        obj = (mic_obj *) malloc(sizeof(mic_obj));

        obj->coord = coord_construct_xyz(x,y,z);

        return obj;

    }

    mic_obj * mic_construct_mic(const mic_obj * mic) {

        mic_obj * obj;

        obj = (mic_obj *) malloc(sizeof(mic_obj));

        obj->coord = coord_construct_coord(mic->coord);

        return obj;

    }

    void mic_copy_zero(mic_obj * obj) {

        coord_copy_zero(obj->coord);

    }

    void mic_copy_xyz(mic_obj * obj, const float x, const float y, const float z) {

        coord_copy_xyz(obj->coord, x, y, z);

    }

    void mic_copy_mic(mic_obj * obj, const mic_obj * mic) {

        coord_copy_coord(obj->coord, mic->coord);

    }

    void mic_destroy(mic_obj * obj) {

        coord_destroy(obj->coord);
	    free((void *) obj);

    }

    void mic_printf(mic_obj * obj) {

        printf("(%+1.4f , %+1.4f , %+1.4f)\n", obj->coord->x, obj->coord->y, obj->coord->z);

    }    

    mics_obj * mics_construct_null(const unsigned int nSignals) {

        mics_obj * obj;
        unsigned int iSignal;

        obj = (mics_obj *) malloc(sizeof(mics_obj));

        obj->nSignals = nSignals;
        obj->array = (mic_obj **) malloc(sizeof(mic_obj *) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {
            obj->array[iSignal] = NULL;
        }

        return obj;

    }

    mics_obj * mics_construct_zero(const unsigned int nSignals) {

        mics_obj * obj;
        unsigned int iSignal;

        obj = (mics_obj *) malloc(sizeof(mics_obj));

        obj->nSignals = nSignals;
        obj->array = (mic_obj **) malloc(sizeof(mic_obj *) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {
            obj->array[iSignal] = mic_construct_zero();
        }

        return obj;

    }

    mics_obj * mics_construct_mics(const mics_obj * mics) {

        mics_obj * obj;
        unsigned int iSignal;

        obj = (mics_obj *) malloc(sizeof(mics_obj));

        obj->nSignals = mics->nSignals;
        obj->array = (mic_obj **) malloc(sizeof(mic_obj *) * mics->nSignals);

        for (iSignal = 0; iSignal < mics->nSignals; iSignal++) {
            obj->array[iSignal] = mic_construct_mic(mics->array[iSignal]);

        }

        return obj;

    }

    void mics_copy_zero(mics_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            mic_copy_zero(obj->array[iSignal]);
        }

    }

    void mics_copy_mics(mics_obj * obj, const mics_obj * mics) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            mic_copy_mic(obj->array[iSignal],mics->array[iSignal]);
        }

    }

    void mics_destroy(mics_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            if (obj->array[iSignal] != NULL) {
        	    mic_destroy(obj->array[iSignal]);
            }
        }

        free((void *) obj->array);
        free((void *) obj);

    }

    void mics_printf(mics_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            if (obj->array[iSignal] != NULL) {
                printf("%03u: (%+1.4f , %+1.4f , %+1.4f)\n", iSignal, obj->array[iSignal]->coord->x, obj->array[iSignal]->coord->y, obj->array[iSignal]->coord->z);    
            }
            else {
                printf("%03u: (null)\n",iSignal);
            }
        }        

    }    