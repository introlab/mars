    
    #include "point.h"

    point_obj * point_construct_zero(void) {

        point_obj * obj;

        obj = (point_obj *) malloc(sizeof(point_obj));

        obj->coord = coord_construct_zero();

        return obj;

    }

    point_obj * point_construct_xyz(const float x, const float y, const float z) {

        point_obj * obj;

        obj = (point_obj *) malloc(sizeof(point_obj));

        obj->coord = coord_construct_xyz(x,y,z);

        return obj;

    }

    point_obj * point_construct_point(const point_obj * point) {

        point_obj * obj;

        obj = (point_obj *) malloc(sizeof(point_obj));

        obj->coord = coord_construct_coord(point->coord);

        return obj;

    }

    void point_copy_zero(point_obj * obj) {

        coord_copy_zero(obj->coord);

    }

    void point_copy_xyz(point_obj * obj, const float x, const float y, const float z) {

        coord_copy_xyz(obj->coord, x, y, z);

    }

    void point_copy_point(point_obj * obj, const point_obj * point) {

        coord_copy_coord(obj->coord, point->coord);

    }

    void point_destroy(point_obj * obj) {

        coord_destroy(obj->coord);
        free((void *) obj);

    }

    void point_printf(point_obj * obj) {

        printf("(%+1.4f , %+1.4f , %+1.4f)\n", obj->coord->x, obj->coord->y, obj->coord->z);

    }

    points_obj * points_construct_null(const unsigned int nSignals) {

        points_obj * obj;
        unsigned int iSignal;

        obj = (points_obj *) malloc(sizeof(points_obj));

        obj->nSignals = nSignals;
        obj->array = (point_obj **) malloc(sizeof(point_obj *) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {
        	obj->array[iSignal] = NULL;
        }

        return obj;

    }

    void points_destroy(points_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
        	if (obj->array[iSignal] != NULL) {
                point_destroy(obj->array[iSignal]);
            }
        }

        free((void *) obj->array);
        free((void *) obj);

    }

    void points_printf(points_obj * obj) {

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