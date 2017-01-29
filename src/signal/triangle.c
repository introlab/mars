    
    #include "triangle.h"

    triangle_obj * triangle_construct_zero(void) {

        triangle_obj * obj;

        obj = (triangle_obj *) malloc(sizeof(triangle_obj));

        obj->pointA = point_construct_zero();
        obj->pointB = point_construct_zero();
        obj->pointC = point_construct_zero();

        return obj;

    }

    triangle_obj * triangle_construct_point(const point_obj * pointA, const point_obj * pointB, const point_obj * pointC) {

        triangle_obj * obj;

        obj = (triangle_obj *) malloc(sizeof(triangle_obj));

        obj->pointA = point_construct_point(pointA);
        obj->pointB = point_construct_point(pointB);
        obj->pointC = point_construct_point(pointC);

        return obj;

    }

    triangle_obj * triangle_construct_triangle(const triangle_obj * triangle) {

        triangle_obj * obj;

        obj = (triangle_obj *) malloc(sizeof(triangle_obj));

        obj->pointA = point_construct_point(triangle->pointA);
        obj->pointB = point_construct_point(triangle->pointB);
        obj->pointC = point_construct_point(triangle->pointC);

        return obj;

    }

    void triangle_copy_zero(triangle_obj * obj) {

        point_copy_zero(obj->pointA);
        point_copy_zero(obj->pointB);
        point_copy_zero(obj->pointC);

    }

    void triangle_copy_point(triangle_obj * obj, const point_obj * pointA, const point_obj * pointB, const point_obj * pointC) {

        point_copy_point(obj->pointA, pointA);
        point_copy_point(obj->pointB, pointB);
        point_copy_point(obj->pointC, pointC);

    }

    void triangle_copy_triangle(triangle_obj * obj, const triangle_obj * triangle) {

        point_copy_point(obj->pointA, triangle->pointA);
        point_copy_point(obj->pointB, triangle->pointB);
        point_copy_point(obj->pointC, triangle->pointC);

    }

    void triangle_destroy(triangle_obj * obj) {

        point_destroy(obj->pointA);
        point_destroy(obj->pointB);
        point_destroy(obj->pointC);

        free((void *) obj);

    }

    void triangle_printf(triangle_obj * obj) {

        printf("(%+1.4f , %+1.4f , %+1.4f) - (%+1.4f , %+1.4f , %+1.4f) - (%+1.4f , %+1.4f , %+1.4f)\n", obj->pointA->coord->x, obj->pointA->coord->y, obj->pointA->coord->z, obj->pointB->coord->x, obj->pointB->coord->y, obj->pointB->coord->z, obj->pointC->coord->x, obj->pointC->coord->y, obj->pointC->coord->z);

    }

    triangles_obj * triangles_construct_null(const unsigned int nSignals) {

        triangles_obj * obj;
        unsigned int iSignal;

        obj = (triangles_obj *) malloc(sizeof(triangles_obj));

        obj->nSignals = nSignals;
        obj->array = (triangle_obj **) malloc(sizeof(triangle_obj *) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {
        	obj->array[iSignal] = NULL;
        }

        return obj;

    }

    void triangles_destroy(triangles_obj * obj) {

        unsigned int iSignal;

    	for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
    		if (obj->array[iSignal] != NULL) {
                triangle_destroy(obj->array[iSignal]);    
            }
    	}

    	free((void *) obj->array);
    	free((void *) obj);
    	
    }

    void triangles_printf(triangles_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            if (obj->array[iSignal] != NULL) {
                printf("%03u: (%+1.4f , %+1.4f , %+1.4f) - (%+1.4f , %+1.4f , %+1.4f) - (%+1.4f , %+1.4f , %+1.4f)\n", iSignal, obj->array[iSignal]->pointA->coord->x, obj->array[iSignal]->pointA->coord->y, obj->array[iSignal]->pointA->coord->z, obj->array[iSignal]->pointB->coord->x, obj->array[iSignal]->pointB->coord->y, obj->array[iSignal]->pointB->coord->z, obj->array[iSignal]->pointC->coord->x, obj->array[iSignal]->pointC->coord->y, obj->array[iSignal]->pointC->coord->z);
            }
            else {
                printf("%03u: (null)\n",iSignal);
            }
        }    

    }