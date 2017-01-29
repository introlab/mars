    
    #include "coord.h"

    coord_obj * coord_construct_zero(void) {

        coord_obj * obj;

        obj = (coord_obj *) malloc(sizeof(coord_obj));

        obj->x = 0.0f;
        obj->y = 0.0f;
        obj->z = 0.0f;

        return obj;

    }

    coord_obj * coord_construct_xyz(const float x, const float y, const float z) {

        coord_obj * obj;

        obj = (coord_obj *) malloc(sizeof(coord_obj));
        
        obj->x = x;
        obj->y = y;
        obj->z = z;

        return obj;

    }

    coord_obj * coord_construct_coord(const coord_obj * coord) {

        coord_obj * obj;

        obj = (coord_obj *) malloc(sizeof(coord_obj));
        
        obj->x = coord->x;
        obj->y = coord->y;
        obj->z = coord->z;

        return obj;

    }

    void coord_copy_zero(coord_obj * obj) {

        obj->x = 0.0f;
        obj->y = 0.0f;
        obj->z = 0.0f;

    }

    void coord_copy_xyz(coord_obj * obj, const float x, const float y, const float z) {

        obj->x = x;
        obj->y = y;
        obj->z = z;

    }

    void coord_copy_coord(coord_obj * obj, const coord_obj * coord) {

        obj->x = coord->x;
        obj->y = coord->y;
        obj->z = coord->z;

    }

    void coord_destroy(coord_obj * obj) {

        free((void *) obj);

    }