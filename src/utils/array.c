    
    #include "array.h"

    array_1d * array_1d_malloc(const unsigned int X) {

        array_1d * obj;
        unsigned int x;

        obj = (array_1d *) malloc(sizeof(array_1d));

        obj->X = X;

        obj->ptr = (void **) malloc(sizeof(void *) * obj->X);

        for (x = 0; x < obj->X; x++) {

        	obj->ptr[x] = (void *) NULL;

        }

        return obj;

    }

    array_2d * array_2d_malloc(const unsigned int X, const unsigned int Y) {

        array_2d * obj;
        unsigned int x,y;

        obj = (array_2d *) malloc(sizeof(array_2d));

        obj->X = X;
        obj->Y = Y;

        obj->ptr = (void ***) malloc(sizeof(void **) * obj->X);

        for (x = 0; x < obj->X; x++) {

            obj->ptr[x] = (void **) malloc(sizeof(void *) * obj->Y);

            for (y = 0; y < obj->Y; y++) {

                obj->ptr[x][y] = (void *) NULL;

            }

        }

        return obj;

    }

    array_3d * array_3d_malloc(const unsigned int X, const unsigned int Y, const unsigned int Z) {

        array_3d * obj;
        unsigned int x,y,z;

        obj = (array_3d *) malloc(sizeof(array_3d));

        obj->X = X;
        obj->Y = Y;
        obj->Z = Z;

        obj->ptr = (void ****) malloc(sizeof(void ***) * obj->X);

        for (x = 0; x < obj->X; x++) {

            obj->ptr[x] = (void ***) malloc(sizeof(void **) * obj->Y);

            for (y = 0; y < obj->Y; y++) {

                obj->ptr[x][y] = (void **) malloc(sizeof(void *) * obj->Z);

                for (z = 0; z < obj->Z; z++) {

                    obj->ptr[x][y][z] = (void *) NULL;

                }

            }

        }

        return obj;

    }

    void array_1d_free(array_1d * obj) {

        free((void **) obj->ptr);
        
        free((void *) obj);

    }

    void array_2d_free(array_2d * obj) {

        unsigned int x;

        for (x = 0; x < obj->X; x++) {

            free((void *) obj->ptr[x]);

        }

        free((void *) obj->ptr);

        free((void *) obj);

    }

    void array_3d_free(array_3d * obj) {

        unsigned int x,y;

        for (x = 0; x < obj->X; x++) {

            for (y = 0; y < obj->Y; y++) {

                 free((void *) obj->ptr[x][y]);

            }

            free((void *) obj->ptr[x]);

        }

        free((void *) obj->ptr);

        free((void *) obj);

    }
